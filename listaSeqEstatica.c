(/******************************************************************************
// Este programa gerencia listas lineares sequenciais.
// As listas gerenciadas podem ter MAX elementos (posicoes de 0 a MAX-1 no
//   arranjo A). Alocamos MAX+1 posicoes no arranjo para possibilitar a 
//   criacao de um elemento sentinela.
******************************************************************************/
#include <stdio.h>
#define MAX 50
#define ERRO -1
#define true 1
#define false 0

typedef int bool;

typedef int TIPOCHAVE;

typedef struct{
  TIPOCHAVE chave;
} REGISTRO;

typedef struct {
  REGISTRO A[MAX+1];
  int nroElem;
} LISTA;

void inicializar(LISTA* l){
	l->nroElem = 0;
}


void exibirLista(LISTA* l){
	int i; 
	printf("Elemento lista:");
	for (i=0; i< l->nroElem; i++){
		printf("%i", l->A[i].chave);
	}
	printf("\n");
}

int tamanho(LISTA* l){
	int i;
	int tam = 0;
	for (i=0; i< l->nroElem; i++){
		tam+1;
	}
	return tam;
}

int tamanhoEmBytes(LISTA* l){
	return sizeof(l);
}

bool inserirElemLista(LISTA* l, REGISTRO reg, int i){
	if(l->nroElem == MAX || i<0 || i>l->nroElem){
		return false;
	}
	int j;
	for (j = l->nroElem; j > i; j--) {
		l->A[j] = l->A[j-1];
	}
  	l->A[i] = reg;
  	l->nroElem++;
  	return true;

}

int buscaSequencial(LISTA* l, TIPOCHAVE chave){
	int x = 0;
	while(x<l->nroElem){
		if(l->A[x].chave == chave){
			return x;
		}
		x++;
	}  
	return ERRO;
}

int main(){
  LISTA lista;
  inicializar(&lista);
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i\n",tamanho(&lista));
  printf("Tamanho da lista (em bytes): %i\n",tamanhoEmBytes(&lista));
  REGISTRO reg;
  reg.chave = 9;
  inserirElemLista(&lista,reg,0);
  exibirLista(&lista);
  reg.chave=3;
  inserirElemLista(&lista,reg,1);
  reg.chave=4;
  inserirElemLista(&lista,reg,2);
  reg.chave=1;
  inserirElemLista(&lista,reg,3);
  reg.chave=12;
  inserirElemLista(&lista,reg,2);
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
  printf("Tamanho da lista (em bytes): %i.\n",tamanhoEmBytes(&lista));
  printf("Chave 4 encontrada na posicao: %i do arranjo A.\n",buscaSequencial(&lista,4));
  /*printf("Chave 4 encontrada na posicao: %i do arranjo A.\n",buscaSentinela(&lista,4));
  if (excluirElemLista(&lista,4)) printf("Exclusao bem sucedida: 4.\n");
  if (excluirElemLista(&lista,8)) printf("Exclusao bem sucedida: 8.\n");
  if (excluirElemLista(&lista,9)) printf("Exclusao bem sucedida: 9.\n");
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
  printf("Tamanho da lista (em bytes): %i.\n",tamanhoEmBytes(&lista));
  reinicializarLista(&lista);
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
  printf("Tamanho da lista (em bytes): %i.\n",tamanhoEmBytes(&lista));*/
  return 0;
}