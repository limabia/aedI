#include "filaPreferencial.h"

PFILA criarFila(){
  PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
  PONT cab =  (PONT) malloc(sizeof(REGISTRO));
  cab->id = -1;
  cab->idade = -1;
  cab->antFila = cab;
  cab->proxFila = cab;
  cab->antIdade = cab;
  cab->proxIdade = cab;
  res->cabeca = cab;
  return res;
}

bool exibirLog(PFILA f){
  int numElementos = tamanho(f);
  printf("Log fila [elementos: %i]\n", numElementos);
  PONT atual = f->cabeca->proxFila;
  while (atual != f->cabeca){
    printf("%p[%i;%i;%p]%p ", atual->antFila, atual->id, atual->idade, atual, atual->proxFila);
    atual = atual->proxFila;
  }
  printf("\nLog preferencial [elementos: %i]\n", numElementos);
  atual = f->cabeca->proxIdade;
  while (atual != f->cabeca){
    printf("%p[%i;%i;%p]%p ", atual->antIdade, atual->id, atual->idade, atual, atual->proxIdade);
    atual = atual->proxIdade;
  }
  printf("\n\n");
}

bool consultarIdade(PFILA f, int id, int* resposta){

  /* COMPLETAR */

  return false;
}

int tamanho(PFILA f){
  int tam = 0;

  /* COMPLETAR */

  return tam;
}


bool inserirElemento(PFILA f, int id, int idade){

  /* COMPLETAR */

  return false;
}


PONT removerElementoIdade(PFILA f){

  /* COMPLETAR */

  return NULL;
}



PONT removerElementoFila(PFILA f){

  /* COMPLETAR */

  return NULL;
}



bool abandonarFila(PFILA f, int id){

  /* COMPLETAR */

  return false;
}
