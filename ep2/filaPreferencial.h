#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0

typedef int bool;

typedef struct aux {
  int id;
  int idade;
  struct aux* antFila;
  struct aux* proxFila;
  struct aux* antIdade;
  struct aux* proxIdade;
} REGISTRO, * PONT;

typedef struct {
  PONT cabeca;
} FILAPREFERENCIAL, * PFILA;

PFILA criarFila();

int tamanho(PFILA f);

bool inserirElemento(PFILA f, int id, int idade);

PONT removerElementoFila(PFILA f);

PONT removerElementoIdade(PFILA f);

bool abandonarFila(PFILA f, int id);

bool consultarIdade(PFILA f, int id, int* resposta);