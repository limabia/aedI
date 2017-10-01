#include <stdio.h>
#include <malloc.h>

typedef struct tempR{
  int valor;
  struct tempR * ant;
  struct tempR * prox;
} Registro;

Registro * criarRegistro(int val){
   Registro* novo = (Registro*) malloc(sizeof(Registro));
   novo->prox = NULL;
   novo->ant = NULL;
   novo->valor = val;
   return novo;
}

int main(){
  Registro* primeiro = NULL;
  primeiro = criarRegistro(10);
  primeiro->prox = criarRegistro(12);
  primeiro->prox->ant = primeiro; 
  Registro* temp;
  temp = primeiro; 
  primeiro = criarRegistro(15);
  primeiro->prox = temp; // em primeiro pegue o prox e coloque o valor em temp
  primeiro->prox->ant = primeiro; // em primeiro pegue o proc, de prox pegue o ant e coloque o valor em primeiro
    
  printf("(*primeiro).prox->valor: %d\n",(*primeiro).prox->valor);
  printf("primeiro->prox->valor: %d\n",primeiro->prox->valor);
  printf("primeiro->prox->prox->valor: %d\n",primeiro->prox->prox->valor);
  printf("primeiro->valor: %d\n",primeiro->valor);
  printf("primeiro: %d\n", primeiro);  
  printf("primeiro->prox->ant: %d\n",primeiro->prox->ant);
  printf("primeiro->prox->prox: %d\n",primeiro->prox->prox);

  return 0;
}

// Qual é o resultado impresso pelo programa, sabendo-se que: 
// (i) o registro com valor=10 foi gravado no endereço 3528; 
// (ii) o registro com valor=12 foi gravado no endereço 3552;
// (iii) o registro com valor=15 foi gravado no endereço 3576;

                   

(*primeiro).prox->valor: 10
primeiro->prox->valor: 10
primeiro->prox->prox->valor: 12
primeiro->valor: 15
primeiro: 1874243664
primeiro->prox->ant: 1874243664
primeiro->prox->prox: 1874243632
