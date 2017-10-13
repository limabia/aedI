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
  PONT atual = f->cabeca->proxFila->proxFila;
  while (atual != f->cabeca->proxFila){
    printf("%p[%i;%i;%p]%p ", atual->antFila, atual->id, atual->idade, atual, atual->proxFila);
    atual = atual->proxFila;
  }
  printf("\nLog preferencial [elementos: %i]\n", numElementos);
  atual = f->cabeca->proxFila->proxIdade;
  while (atual != f->cabeca->proxFila){
    printf("%p[%i;%i;%p]%p ", atual->antIdade, atual->id, atual->idade, atual, atual->proxIdade);
    atual = atual->proxIdade;
  }
  printf("\n\n");
}


bool consultarIdade(PFILA f, int id, int* resposta){
  PONT pos = f->cabeca->proxFila;
  while (pos != f->cabeca){
    if (pos->id == id){
      *resposta = pos->idade;
      return true;
    }
    pos = pos->proxFila;
  }
  return false;
}


int tamanho(PFILA f){
  int tam = 0;
  PONT end = f->cabeca->proxFila;
  while (end != f->cabeca){
    tam++;
    end = end->proxFila;
  }
  return tam;
}


bool buscaId(PFILA f, int id){
  PONT pos = f->cabeca->proxFila;
  while (pos != f->cabeca){
    if (pos->id == id){
      return true;
    }
    pos = pos->proxFila;
  }
  return false;
}


void insereFilaNormal(PFILA f, int id, int idade, PONT novo){
  novo-> antFila = f->cabeca->antFila;
  novo->id = id;
  novo->proxFila = f->cabeca;
  novo->idade = idade;

  f->cabeca->antFila->proxFila = novo;
  f->cabeca->antFila = novo;
}


void insereFilaPref(PFILA f, int idade, PONT novo) {
    PONT pos = f->cabeca->proxIdade;
    while (pos != f->cabeca && pos->idade >= idade) {
        pos = pos->proxIdade;
    }
    novo->proxIdade = pos;
    novo->antIdade = pos->antIdade;
    pos->antIdade->proxIdade = novo;
    pos->antIdade = novo;
}


bool inserirElemento(PFILA f, int id, int idade){
  bool achouElemId = buscaId(f, id); 
  if (achouElemId == false){
    PONT novo = (PONT) malloc(sizeof(REGISTRO));
    insereFilaNormal(f, id, idade, novo);
    insereFilaPref(f, idade, novo);
    return true;
  }
  return false;
}


PONT removerElementoIdade(PFILA f){
  PONT elementoRemovido = f->cabeca->proxIdade;
  if (elementoRemovido){
    // ajustando ponteiros da fila preferencial
    f->cabeca->proxIdade = elementoRemovido->proxIdade;
    if (f->cabeca->proxIdade){
      f->cabeca->proxIdade->antIdade = NULL;  
    }
    elementoRemovido->proxIdade = NULL;

    // se nao for o primeiro da fila comum
    if (elementoRemovido->antFila != NULL){
      elementoRemovido->antFila->proxFila = elementoRemovido->proxFila;
    } else {
      f->cabeca->proxFila = elementoRemovido->proxFila;
    }
    // se nao for o ultimo da fila comum
    if (elementoRemovido->proxFila != NULL){
      elementoRemovido->proxFila->antFila = elementoRemovido->antFila;
    } else {
      f->cabeca->antFila = elementoRemovido->antFila;
    }
    elementoRemovido->proxFila = NULL;
    elementoRemovido->antFila = NULL;
    return elementoRemovido;
  }
  return NULL;
}


PONT removerElementoFila(PFILA f){
  PONT elementoRemovido = f->cabeca->proxFila;
  if (elementoRemovido){
    // ajustando ponteiros da fila normal
    f->cabeca->proxFila = elementoRemovido->proxFila;
    if (f->cabeca->proxFila){
      f->cabeca->proxFila->antFila = NULL;
    } else {
      f->cabeca->antFila = NULL;
    }
    elementoRemovido->proxFila = NULL;
    elementoRemovido->antFila = NULL;

    // ajustando da fila pref
    if (elementoRemovido->antIdade != NULL){
      elementoRemovido->antIdade->proxIdade = elementoRemovido->proxIdade;
    } else {
      f->cabeca->proxIdade = elementoRemovido->proxIdade;
    }

    if (elementoRemovido->proxIdade != NULL){
      elementoRemovido->proxIdade->antIdade = elementoRemovido->antIdade;
    }

    elementoRemovido->proxIdade = NULL;
    elementoRemovido->antIdade = NULL;
    return elementoRemovido;
  }
  return NULL;
}


bool abandonarFila(PFILA f, int id){
  bool elemExiste = buscaId(f, id);
  if(elemExiste){
    /* tirar da fila e da fila pref */
  }
  return false;
}