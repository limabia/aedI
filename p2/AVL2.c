#include <malloc.h>
#include <stdio.h>

#define INVALIDO '*'
#define true 1
#define false 0

typedef char TIPOCHAVE;
typedef int bool;

typedef struct aux {
	TIPOCHAVE chave;
	struct aux *esq, *dir;
	int bal;
} NO, * PONT;

PONT criarNo(TIPOCHAVE chave) {
	PONT novo = (PONT) malloc(sizeof(NO));
	novo->chave = chave;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->bal = 0;
	return novo;
}

void inicializar(PONT * raiz, TIPOCHAVE chave) {
	*raiz = criarNo(chave);
}

void rotacaoL(PONT * p) {
	PONT u, v;

	u = (*p)->esq;

	if(u->bal == 1) {
		// LL
		(*p)->esq = u->dir;
		u->dir = *p;
		*p = u;
		(*p)->dir->bal = 0;
	} else {
		// LR
		v = u->dir;
		(*p)->esq = v->dir;
		v->dir = (*p);
		u->dir = v->esq;
		v->esq = u;

		if(v->bal == -1) (*p)->bal = 1;
		else (*p)->bal = 0;

		if(v->bal == 1) u->bal = -1;
		else u->bal = 0;

		*p = v;
	}
	(*p)->bal = 0;
}

void rotacaoR(PONT * p) {
	PONT u, v;

	u = (*p)->dir;

	if(u->bal == -1) {
		// RR
		(*p)->dir = u->esq;
		u->esq = *p;
		*p = u;
		(*p)->esq->bal = 0;
	} else {
		v = u->esq;
		(*p)->dir = v->dir;
		v->dir = *p;
		u->esq = v->esq;
		v->esq = u;

		if(v->bal == -1) (*p)->bal = -1;
		else (*p)->bal = 0;

		if(v->bal == 1) u->bal = 1;
		else u->bal = 0;

		*p = v;
	}
	(*p)->bal = 0;
}

void inserirAVL(PONT * raiz, TIPOCHAVE chave, bool * alterou) {
	PONT p = *raiz;
	if(!p) {
		*raiz = criarNo(chave);
		*alterou = true;		
	} else {
		if(chave <= p->chave) {
			inserirAVL(&(p->esq), chave, alterou);
			if(*alterou) switch(p->bal) {
				case 1:
					rotacaoL(raiz);
					*alterou = false;
					break;

				case 0:
					p->bal = 1;
					//*alterou = false;
					break;

				case -1:
					p->bal = 0;
					*alterou = false;
					break;
			}
		} else {
			inserirAVL(&(p->dir), chave, alterou);
			if(*alterou) switch(p->bal) {
				case 1:
					p->bal = 0;
					*alterou = false;
					break;

				case 0:
					p->bal = -1;
					//*alterou = false;
					break;

				case -1:
					rotacaoR(raiz);
					*alterou = false;
					break;
			}
		}
	}
}

int altura(PONT raiz) {
	if(!raiz) return -1;
	int temp = -1;
	int max = 0;

	temp = altura(raiz->esq);
	if(temp > max) max = temp;
	temp = altura(raiz->dir);
	if(temp > max) max = temp; 

	return max + 1;
}

void imprimirComum(PONT raiz) {
	if(!raiz) return;

	printf("%c ", raiz->chave);

	printf("(");
	imprimirComum(raiz->esq);
	printf("|");
	imprimirComum(raiz->dir);
	printf(")");
}

/*
   #############################

       Minhas implementações

   #############################
*/

int potencia(int pot) {
	if(pot < 0) return -1;
	if(pot == 0) return 1;

	int resultado = 1;
	int i;
	for(i = 0; i < pot; i++) resultado *= 2;
	return resultado;
}

void preencheVetor(PONT raiz, TIPOCHAVE * vetor, int i, int tamanho) {
	if(i >= tamanho) return;

	if(raiz) {
		vetor[i] = raiz->chave;
		preencheVetor(raiz->esq, vetor, 2*i + 1, tamanho);
		preencheVetor(raiz->dir, vetor, 2*i + 2, tamanho);
	} else {
		vetor[i] = INVALIDO;
		preencheVetor(NULL, vetor, 2*i + 1, tamanho);
		preencheVetor(NULL, vetor, 2*i + 2, tamanho);
	}
}

TIPOCHAVE * arvoreVetor(PONT raiz) {
	if(!raiz) return NULL;

	int tamanho = potencia(altura(raiz) + 1) - 1; // 2^(h + 1) - 1
	TIPOCHAVE * vetor = (TIPOCHAVE *) malloc(sizeof(TIPOCHAVE) * tamanho);

	preencheVetor(raiz, vetor, 0, tamanho);
	return vetor;
}

void imprimir(PONT raiz) {
	if(!raiz) return;

	TIPOCHAVE * vetor = arvoreVetor(raiz);

	int k = 0;
	int alt = altura(raiz);
	int i, j, imprime, cont;

	for(i = 0; i <= alt; i++) {
		if(i != 0) {
			cont = 0;
			imprime = potencia(alt - i - 1);
			for(j = 0; j <= potencia(alt); j++) {
				if(j == imprime) {
					printf((cont % 2 == 0 ? "/" : "\\"));
					cont++;
					imprime += potencia(alt - i);
				} else printf(" ");
			}
			printf("\n");
		}

		
		imprime = potencia(alt - i - 1);
		for(j = 0; j <= potencia(alt); j++) {
			if(j == imprime) {
				printf("%c", vetor[k]);
				k++;
				imprime += potencia(alt - i);
			} else printf(" ");
		}
		printf("\n");
	}
}

int main() {

	PONT raiz;
	inicializar(&raiz, '5');

	int escolha = 0;
	TIPOCHAVE chave = INVALIDO;
	bool alterou = false;

	imprimir(raiz);

	/*
	  Atenção: este trecho de código contem altas gambiarras.
	*/
	do {
		printf(" 0. Sair\n 1. Inserir\n-> ");
		scanf("%d", &escolha);

		if(escolha == 1) {
			printf("Digite a chave\n-> ");
			scanf("%c", &chave);
			scanf("%c", &chave);
			inserirAVL(&raiz, chave, &alterou);
			imprimir(raiz);
		}

		if(escolha != 1) break;
	} while(true);

	return 0;
}
