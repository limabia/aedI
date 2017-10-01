#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0

typedef int bool;

typedef struct aux {
  int id; // identificador inteiro do elemento
  int idade; // número inteiro com a idade do elemento
  struct aux* antFila;// ponteiro para o elemento anterior, isto é, aquele que chegou antes na fila
  struct aux* proxFila; // ponteiro para o elemento posterior, isto é, aquele que chegou depois na fila
  struct aux* antIdade; // ponteiro para o que possui idade imediatamente maior do que a do elemento atual
  struct aux* proxIdade; // ponteiro para o que possui idade imediatamente menor do que a do elemento atual
} REGISTRO, * PONT;

typedef struct {
  PONT inicioFila;
  PONT fimFila;
  PONT preferencial;
} FILAPREFERENCIAL, * PFILA;

PFILA criarFila();

int tamanho(PFILA f);

bool inserirElemento(PFILA f, int id, int idade);

PONT removerElementoFila(PFILA f);

PONT removerElementoIdade(PFILA f);

bool consultarIdade(PFILA f, int id, int* resposta);


//inicioFila é um ponteiro para elementos do tipo
//REGISTRO e corresponde ao ponteiro para o primeiro elemento da lista duplamente ligada e ordenada de registros,
//ordenados pela ordem de chegada (esta lista de elementos não possuirá nó-cabeça e não será circular); fimFila é
//um ponteiro para elementos do tipo REGISTRO e corresponde ao ponteiro para o último elemento da lista
//duplamente ligada (ordenada por ordem de chegada); e preferencial é um ponteiro para elementos do tipo
//REGISTRO e corresponde ao ponteiro para o primeiro elemento da lista duplamente ligada e ordenada de registros,
//ordenados pela idade de maneira decrescente (esta lista de elementos não possuirá nó-cabeça e não será circular);