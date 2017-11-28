#include "filaPreferencial.c"
#include <string.h>
#include <time.h>

/* ======================================================================================= */

typedef struct auxPessoa{
	int id;
	int idade;
	char nome[20];
	PONT pont;
	struct auxPessoa * prox;
} PESSOA;

typedef struct {
	PESSOA * inicio;
	int quantidade;
} LISTAPESSOAS;

void inicializarPessoas(LISTAPESSOAS * lp) {
	lp->inicio = NULL;
	lp->quantidade = 0;
}

void inserir(LISTAPESSOAS * lp, PESSOA * p) {
	p->prox = lp->inicio;
	lp->inicio = p;
	lp->quantidade++;
}

void mudaPonteiroPessoa(PESSOA * p, PONT pont) {
	if(p) p->pont = pont;
}

void imprimirListaPessoas(LISTAPESSOAS * lp) {
	printf("\033[37m"); // Muda cor da letra para branca
	PESSOA * atual = lp->inicio;
	int i = 0;
	printf("Lista de Pessoas\n #\tIdade\tId\tNome\n");
	while(atual) {
		if(atual->pont) printf("\033[41m"); // Cor de fundo vermelha
		printf("[%d]\t%d\t%d\t%s", i, atual->idade, atual->id, atual->nome);
		printf("\033[40m");
		printf("\n");
		atual = atual->prox;
		i++;
	}
	printf("\n\033[32m"); // Muda cor da letra para verde
}

// Buca uma pessoa na lista de pessoas pelo seu índice
PESSOA * pegaPessoaIndice(LISTAPESSOAS * lp, int indice) {
	if(!lp->inicio) return NULL;
	int i = 0;
	PESSOA * atual = lp->inicio;
	while(atual != NULL) {
		if(i == indice) return atual;
		i++;
		atual = atual->prox;
	}
	return NULL;
}

// Busca uma pessoa na lista de pessoas pelo ponteiro
PESSOA * pegaPessoaPont(LISTAPESSOAS * lp, PONT pont) {
	PESSOA * atual = lp->inicio;
	while(atual) {
		if(atual->pont == pont) return atual;
		atual = atual->prox;
	}
	return NULL;
}	

PESSOA * pegaPessoaId(LISTAPESSOAS * lp, int id) {
	PESSOA * atual = lp->inicio;
	while(atual) {
		if(atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

/* ======================================================================================= */

// Busca um elemento na fila pelo seu ID
PONT buscaIdFila(PFILA f, int id) {
	if(f->cabeca->proxFila == f->cabeca) return NULL;
	PONT atual =  f->cabeca->proxFila;
	f->cabeca->id = id;
	while(atual->id != id) atual = atual->proxFila;
	if(atual == f->cabeca) return NULL;
	return atual;
}

// Imprime a fila a comum
void imprimirFilaComum(PFILA f, LISTAPESSOAS * lp) {
	int i = 1;
	PESSOA * pessoa;
	PONT atual = f->cabeca->proxFila;
	printf("\033[37mFila comum (%d) {\n", tamanho(f));
	printf("\t  #\tID\tIdade\tNome\n");
	while(atual != f->cabeca) {
		if(i < 10) printf("\t[0");
		else printf("\t[");
		pessoa = pegaPessoaPont(lp, atual);
		printf("%d]\t%d\t\033[31m%d\033[37m\t\033[33m%s\033[37m\n", i, pessoa->id, pessoa->idade, (pessoa ? pessoa->nome : "???"));
		i++;
		atual = atual->proxFila;
	}
	printf("}\033[32m\n\n");
}

// Imprime a fila preferêncial
void imprimirFilaPreferencial(PFILA f, LISTAPESSOAS * lp) {
	int i = 1;
	PESSOA * pessoa;
	PONT atual = f->cabeca->proxIdade;
	printf("\033[37mFila preferencial (%d) {\n", tamanho(f));
	printf("\t  #\tID\tIdade\tNome\n");
	while(atual != f->cabeca) {
		if(i < 10) printf("\t[0");
		else printf("\t[");
		pessoa = pegaPessoaPont(lp, atual);
		printf("%d]\t%d\t\033[31m%d\033[37m\t\033[33m%s\033[37m\n", i, pessoa->id, pessoa->idade, (pessoa ? pessoa->nome : "???"));
		i++;
		atual = atual->proxIdade;
	}
	printf("}\033[32m\n\n");
}

// Imprime a fila comum com ponteiros
void imprimirFilaComumPonteiros(PFILA f, LISTAPESSOAS * lp) {
	int i = 0;
	PESSOA * pessoa;
	PONT atual = f->cabeca->proxFila;
	printf("\033[37mFila comum (%d) {\n", tamanho(f));
	printf("\t\tID\t\033[31mIdade\t\033[33mNome\033[37m\n\n");
	while(atual != f->cabeca) {

		// Imprime anterior
		printf("\t(");
		if(i%2 == 0) printf("\033[36m");
		else printf("\033[32m");
		if(atual->antFila == f->cabeca) printf("COMEÇO");
		else {
			pessoa = pegaPessoaPont(lp, atual->antFila);
			printf("%s", (pessoa ? pessoa->nome : "???"));
		}
		printf("\033[37m)");

		// Imprime atual
		pessoa = pegaPessoaPont(lp, atual);
		printf(" <-(%d\t\033[31m%d\033[37m\t\033[33m%s\033[37m)-> ", pessoa->id, pessoa->idade, (pessoa ? pessoa->nome : "???"));

		// Imprime próximo
		printf("(");
		if(i%2 == 0) printf("\033[32m");
		else printf("\033[36m");
		if(atual->proxFila == f->cabeca) printf("FIM");
		else {
			pessoa = pegaPessoaPont(lp, atual->proxFila);
			printf("%s", (pessoa ? pessoa->nome : "???"));
		}
		printf("\033[37m)\n");

		i++;
		atual = atual->proxFila;
	}
	printf("}\033[32m\n\n");
}

// Imprime a fila preferencial com ponteiros
void imprimirFilaPreferencialPonteiros(PFILA f, LISTAPESSOAS * lp) {
	int i = 0;
	PESSOA * pessoa;
	PONT atual = f->cabeca->proxIdade;
	printf("\033[37mFila preferencial (%d) {\n", tamanho(f));
	printf("\t\tID\t\033[31mIdade\t\033[33mNome\033[37m\n\n");
	while(atual != f->cabeca) {

		// Imprime anterior
		printf("\t(");
		if(i%2 == 0) printf("\033[36m");
		else printf("\033[32m");
		if(atual->antIdade == f->cabeca) printf("COMEÇO");
		else {
			pessoa = pegaPessoaPont(lp, atual->antIdade);
			printf("%s", (pessoa ? pessoa->nome : "???"));
		}
		printf("\033[37m)");

		// Imprime atual
		pessoa = pegaPessoaPont(lp, atual);
		printf(" <-(%d\t\033[31m%d\033[37m\t\033[33m%s\033[37m)-> ", pessoa->id, pessoa->idade, (pessoa ? pessoa->nome : "???"));

		// Imprime próximo
		printf("(");
		if(i%2 == 0) printf("\033[32m");
		else printf("\033[36m");
		if(atual->proxIdade == f->cabeca) printf("FIM");
		else {
			pessoa = pegaPessoaPont(lp, atual->proxIdade);
			printf("%s", (pessoa ? pessoa->nome : "???"));
		}
		printf("\033[37m)\n");

		i++;
		atual = atual->proxIdade;
	}
	printf("}\033[32m\n\n");
}

void imprimirFilaComumEnderecos(PFILA f) {
	PONT atual = f->cabeca->proxFila;
	printf("\033[37mFila comum:\nCabeça: (\033[33m%p\033[37m)\n", f->cabeca);
	while(atual != f->cabeca) {
		printf("\033[37m(\033[36m%p\033[37m)antFila<-[\033[33m%p\033[37m]->proxFila(\033[36m%p\033[37m)\n", atual->antFila, atual, atual->proxFila);
		atual = atual->proxFila;
	}
	printf("\033[32m\n");
}

void imprimirFilaPreferencialEnderecos(PFILA f) {
	PONT atual = f->cabeca->proxIdade;
	printf("\033[37mFila preferencial:\nCabeça: (\033[33m%p\033[37m)\n", f->cabeca);
	while(atual != f->cabeca) {
		printf("\033[37m(\033[36m%p\033[37m)antIdade<-[\033[33m%p\033[37m]->proxIdade(\033[36m%p\033[37m)\n", atual->antIdade, atual, atual->proxIdade);
		atual = atual->proxIdade;
	}
	printf("\033[32m\n");
}

int main() {
	srand(time(NULL));

	int i, aux, opcao, id, idade;
	int codEnt;

	PONT excluido;
	PESSOA * pessoa;

	/*
	  Cria pessoas para realização de testes
	*/
	PESSOA pessoas[10];

	pessoas[0].id = 15;
	pessoas[0].idade = 60;
	strcpy(pessoas[0].nome, "João");

	pessoas[1].id = 13;
	pessoas[1].idade = 24;
	strcpy(pessoas[1].nome, "Dilma");

	pessoas[2].id = 34;
	pessoas[2].idade = 50;
	strcpy(pessoas[2].nome, "I will");

	pessoas[3].id = 23;
	pessoas[3].idade = 58;
	strcpy(pessoas[3].nome, "Stalin");

	pessoas[4].id = 12;
	pessoas[4].idade = 18;
	strcpy(pessoas[4].nome, "Alberto");

	pessoas[5].id = 65;
	pessoas[5].idade = 20;
	strcpy(pessoas[5].nome, "Kim Jong-un");

	pessoas[6].id = 45;
	pessoas[6].idade = 50;
	strcpy(pessoas[6].nome, "Putin");

	pessoas[7].id = 56;
	pessoas[7].idade = 999;
	strcpy(pessoas[7].nome, "Elizabeth II");

	pessoas[8].id = 59;
	pessoas[8].idade = 48;
	strcpy(pessoas[8].nome, "Adolfo Rifler");

	pessoas[9].id = 23;
	pessoas[9].idade = 74;
	strcpy(pessoas[9].nome, "MousseLine");

	/*
	  Cria lista de pessoas
	*/
	LISTAPESSOAS lp;
	inicializarPessoas(&lp);	
	for(i = 0; i < 10; i++) {
		pessoas[i].pont = NULL;	
		inserir(&lp, &pessoas[i]);
	}

	// Cria a fila
	PFILA f = criarFila();

	printf("\033[32m"); // Muda a cor da letra para verde
	printf("\033[40m"); // Muda o plano de fundo para preto

	do {
		do {
			opcao = 0;
			printf("Escolha um opção:\n");
			printf("  0 - Sair\n");
			printf("  1 - Inserir na Fila\n");
			printf("  2 - Excluir da fila comum\n");
			printf("  3 - Excluir da fila preferencial\n");
			printf("  4 - Ver filas\n");
			printf("  5 - Ver filas com ponteiros\n");
			printf("  6 - Abandonar fila\n");
			printf("  7 - Consultar idade\n");
			printf("  8 - Análise técnica\n");
			printf("  9 - Testes aleatórios\n");
			printf(" 10 - Limpar tela (linux)\n");
			printf("-> \033[33m");
			scanf("%d", &opcao);
			printf("\033[32m\n");
		} while(opcao < 0 || opcao > 10);

		switch(opcao) {
			case 0:
				printf("Saindo...\n");
				break;

			case 1: // Inserir na fila
				imprimirListaPessoas(&lp);
				printf("\033[37m[!] - Escolha uma pessoa: (-1 para cancelar)\n-> \033[33m");
				scanf("%d", &codEnt);
				printf("\033[37m");
				if(codEnt != -1) {
					pessoa = pegaPessoaIndice(&lp, codEnt);

					if(!pessoa) printf("\a\033[31m[!] - ERRO - Pessoa não encontrada.\033[37m\n\n");
					else if(pessoa->pont) {
						printf("\a\033[31m[!] - %s já está na fila!\033[37m\n\n", pessoa->nome);
					} else {
						if(inserirElemento(f, pessoa->id, pessoa->idade)) {
							printf("\033[31m[!] - %s entrou na fila!\033[37m\n\n", pessoa->nome);
							pessoa->pont = buscaIdFila(f, pessoa->id);

							imprimirFilaComum(f, &lp);
							imprimirFilaPreferencial(f, &lp);
						} else
							printf("\a\033[31m[!] - %s NÃO entrou na fila!\033[37m\n\n", pessoa->nome);
					}
				}
				printf("\033[32m\n");
				break;

			case 2: // Excluir da fila comum
				excluido = removerElementoFila(f);

				imprimirFilaComum(f, &lp);
				imprimirFilaPreferencial(f, &lp);

				if(excluido) {
					pessoa = pegaPessoaPont(&lp, excluido);
					printf("\033[31m[!] - %s foi excluído(a) da fila.\033[37m\n", (pessoa ? pessoa->nome : "???"));
					pessoa->pont = NULL;
				} else {
					printf("\a\033[31m[!] - Ninguém foi excluído da fila.\033[37m\n");
				}
				printf("\033[32m\n");
				break;

			case 3: // Excluir da fila preferencial
				excluido = removerElementoIdade(f);

				imprimirFilaComum(f, &lp);
				imprimirFilaPreferencial(f, &lp);

				if(excluido) {
					pessoa = pegaPessoaPont(&lp, excluido);
					printf("\033[31m[!] - %s foi excluído(a) da fila.\033[37m\n", (pessoa ? pessoa->nome : "???"));
					pessoa->pont = NULL;
				} else {
					printf("\a\033[31m[!] - Ninguém foi excluído da fila.\033[37m\n");
				}
				printf("\033[32m\n");
				break;

			case 4: // Ver filas
				imprimirFilaComum(f, &lp);
				imprimirFilaPreferencial(f, &lp);
				break;

			case 5: // Ver filas com ponteiros
				imprimirFilaComumPonteiros(f, &lp);
				imprimirFilaPreferencialPonteiros(f, &lp);
				break;

			case 6: // Abandona fila
				imprimirListaPessoas(&lp);
				printf("\033[37m[!] - Escolha uma pessoa pelo ID: (-1 para cancelar)\n-> \033[33m");
				scanf("%d", &codEnt);
				printf("\033[37m");
				if(codEnt != -1) {
					excluido = buscaIdFila(f, codEnt);
					pessoa = pegaPessoaPont(&lp, excluido);
					if(abandonarFila(f, codEnt)) {
						printf("\033[31m[!] - %s abandonou a fila.\033[37m\n", (pessoa ? pessoa->nome : "???"));
						pessoa->pont = NULL;
					} else printf("\a\033[31m[!] - Ninguém abandonou a fila.\033[37m\n");
				}
				printf("\033[32m\n");
				break;

			case 7: // Consultar idade
				idade = -1;
				imprimirListaPessoas(&lp);
				printf("\033[37m[!] - Escolha uma pessoa pelo ID: (-1 para cancelar)\n-> \033[33m");
				scanf("%d", &id);
				if(id != -1) {
					if(consultarIdade(f, id, &idade)) printf("\033[31m[!] - Idade: \033[33m%d\033[31m ano(s).\033[37m\n", idade);
					else printf("\a\033[31m[!] - Não foi possível consultar a idade.\033[37m\n");
				}
				printf("\033[32m\n");
				break;

			case 8: // Análise técnica

				printf("Análise Técnica:\n");
				printf("\033[37mPonteiro para fila: \033[36m%p\n", f);
				printf("\033[37mPonteiro para o nó cabeça: \033[36m%p\n", f->cabeca);
				printf("\033[37m(\033[36m%p\033[37m)antFila<-Cabeca->proxFila(\033[36m%p\033[37m)\n", f->cabeca->antFila, f->cabeca->proxFila);
				printf("\033[37m(\033[36m%p\033[37m)antIdade<-Cabeca->proxIdade(\033[36m%p\033[37m)\033[32m\n\n", f->cabeca->antIdade, f->cabeca->proxIdade);
				imprimirFilaComumEnderecos(f);
				imprimirFilaPreferencialEnderecos(f);
				break;

			case 9: // Testes aleatórios;

				// Tenta fazer 10 inserções
				for(i = 0; i < 10; i++) {
					pessoa = pegaPessoaIndice(&lp, rand() % lp.quantidade);
					if(!pessoa) printf("\a\033[31m[!] - ERRO - Pessoa não encontrada.\033[37m\n\n");
					else if(pessoa->pont) {
						printf("\a\033[31m[!] - %s já está na fila!\033[37m\n\n", pessoa->nome);
					} else {
						if(inserirElemento(f, pessoa->id, pessoa->idade)) {
							printf("\033[31m[!] - %s entrou na fila!\033[37m\n\n", pessoa->nome);
							pessoa->pont = buscaIdFila(f, pessoa->id);
						} else
							printf("\a\033[31m[!] - %s NÃO entrou na fila!\033[37m\n\n", pessoa->nome);
					}
				}
				imprimirFilaComum(f, &lp);
				imprimirFilaPreferencial(f, &lp);

				// Tenta fazer 10 exclusões
				for(i = 0; i < 10; i++) {
					aux = rand();
					if(aux % 2 == 0) {
						if(aux % 3 == 0) {
							excluido = removerElementoFila(f);
							if(excluido) {
								pessoa = pegaPessoaPont(&lp, excluido);
								printf("\033[31m[!] - %s foi excluído(a) da fila.\033[37m\n", (pessoa ? pessoa->nome : "???"));
								pessoa->pont = NULL;
							} else {
								printf("\a\033[31m[!] - Ninguém foi excluído da fila.\033[37m\n");
							}
							printf("\033[32m\n");
						} else {
							excluido = removerElementoIdade(f);
							if(excluido) {
								pessoa = pegaPessoaPont(&lp, excluido);
								printf("\033[31m[!] - %s foi excluído(a) da fila.\033[37m\n", (pessoa ? pessoa->nome : "???"));
								pessoa->pont = NULL;
							} else {
								printf("\a\033[31m[!] - Ninguém foi excluído da fila.\033[37m\n");
							}
							printf("\033[32m\n");
						}
					} else {
						pessoa = pegaPessoaIndice(&lp, rand()%10);
						if(abandonarFila(f, pessoa->id)) {
							printf("\033[31m[!] - %s abandonou a fila.\033[37m\n", (pessoa ? pessoa->nome : "???"));
							pessoa->pont = NULL;
						} else printf("\a\033[31m[!] - Ninguém abandonou a fila.\033[37m\n");
						printf("\033[32m\n");
					}
				}

				imprimirFilaComumPonteiros(f, &lp);
				imprimirFilaPreferencialPonteiros(f, &lp);

				break;

			case 10: // Limpa a tela (ao menos no ubuntu)
				printf("\033[2J");
				break;

			default:
				printf("\a\033[47m\033[31m[!] - Ocorreu alguma treta maligna inesperada.\033[32m[40m\n");
		}

	} while(opcao);

	return 0;
}
