#include "filaPreferencial.h"


PFILA criarFila(){
  PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
  res->inicioFila = NULL;
  res->fimFila = NULL; 
  res->preferencial = NULL;  
  return res;
}


bool exibirLog(PFILA f){
  int numElementos = tamanho(f);
  printf("Log fila [elementos: %i]\n", numElementos);
  PONT atual = f->inicioFila;
  while (atual){
    printf("%p[%i;%i;%p]%p ", atual->antFila, atual->id, atual->idade, atual, atual->proxFila);
    atual = atual->proxFila;
  }
  printf("\nLog preferencial [elementos: %i]\n", numElementos);
  atual = f->preferencial;
  while (atual){
    printf("%p[%i;%i;%p]%p ", atual->antIdade, atual->id, atual->idade, atual, atual->proxIdade);
    atual = atual->proxIdade;
  }
  printf("\n\n");
}


bool consultarIdade(PFILA f, int id, int* resposta){
  PONT pos = f->inicioFila;
  while (pos != NULL){
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
  PONT end = f->inicioFila;
  while (end != NULL){
    tam++;
    end = end->proxFila;
  }
  return tam;
}


bool buscaId(PFILA f, int id){
  PONT pos = f->inicioFila;
  while (pos != NULL){
    if (pos->id == id){
      return true;
    }
    pos = pos->proxFila;
  }
  return false;
}


void insereFilaNormal(PFILA f, int id, int idade, PONT novo){
  novo-> antFila = f->fimFila;
  novo->id = id;
  novo->proxFila = NULL;
  novo->idade = idade;

  if (f->inicioFila == NULL){
    f->inicioFila = novo;
  } else {
    f->fimFila->proxFila = novo;
  }
  f->fimFila = novo;
}


void insereFilaPref(PFILA f, int idade, PONT novo){
  if (f->preferencial == NULL){
    novo->proxIdade = NULL;
    novo->antIdade = NULL;
    f->preferencial = novo;
  } else {
    PONT pos = f->preferencial;
    PONT ant = NULL;

    while(pos != NULL && pos->idade >= idade){
      ant = pos;
      pos = pos->proxIdade;
    }

    novo->proxIdade = pos;
    novo->antIdade = ant;
    if (pos){
      pos->antIdade = novo;  
    }
    if (ant){
      ant->proxIdade = novo;  
    } else {
      f->preferencial = novo;
    }
  }
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
  PONT elementoRemovido = f->preferencial;
  if (elementoRemovido){
    // ajustando ponteiros da fila preferencial
    f->preferencial = elementoRemovido->proxIdade;
    if (f->preferencial){
      f->preferencial->antIdade = NULL;  
    }
    elementoRemovido->proxIdade = NULL;

    // se nao for o primeiro da fila comum
    if (elementoRemovido->antFila != NULL){
      elementoRemovido->antFila->proxFila = elementoRemovido->proxFila;
    } else {
      f->inicioFila = elementoRemovido->proxFila;
    }
    // se nao for o ultimo da fila comum
    if (elementoRemovido->proxFila != NULL){
      elementoRemovido->proxFila->antFila = elementoRemovido->antFila;
    } else {
      f->fimFila = elementoRemovido->antFila;
    }
    elementoRemovido->proxFila = NULL;
    elementoRemovido->antFila = NULL;
    return elementoRemovido;
  }
  return NULL;
}


PONT removerElementoFila(PFILA f){
  PONT elementoRemovido = f->inicioFila;
  if (elementoRemovido){
    // ajustando ponteiros da fila normal
    f->inicioFila = elementoRemovido->proxFila;
    if (f->inicioFila){
      f->inicioFila->antFila = NULL;
    } else {
      f->fimFila = NULL;
    }
    elementoRemovido->proxFila = NULL;
    elementoRemovido->antFila = NULL;

    // ajustando da fila pref
    if (elementoRemovido->antIdade != NULL){
      elementoRemovido->antIdade->proxIdade = elementoRemovido->proxIdade;
    } else {
      f->preferencial = elementoRemovido->proxIdade;
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
