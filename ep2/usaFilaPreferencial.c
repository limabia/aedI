#include "filaPreferencial.c"

int main() {
  PFILA f = criarFila();
  PONT prioritario;
  int idade;
  int id;
  exibirLog(f);
  if(inserirElemento(f, 20, 21)) printf("ok\n");
  else printf("nok (1)\n");
  exibirLog(f);
  if(inserirElemento(f, 30, 23)) printf("ok\n");
  else printf("nok (2)\n");
  exibirLog(f);
  if(inserirElemento(f, 22, 22)) printf("ok\n");
  else printf("nok (3)\n");
  exibirLog(f);
  if(inserirElemento(f, 5, 20)) printf("ok\n");
  else printf("nok (4)\n");
  exibirLog(f);
  if(inserirElemento(f, 50, 25)) printf("ok\n");
  else printf("nok (5)\n");
  exibirLog(f);
  if(inserirElemento(f, 50, 25)) printf("ok\n");
  else printf("ok (6) - registro repetido\n");
  exibirLog(f);
  if(inserirElemento(f, 5, 20)) printf("ok\n");
  else printf("ok (7) - registro repetido\n");
  exibirLog(f);
  if(inserirElemento(f, 20, 21)) printf("ok\n");
  else printf("ok (8) - registro repetido\n");
  exibirLog(f);
  printf("################# REMOVENDO #######################\n");

  prioritario = removerElementoFila(f);
  if (prioritario) printf("Primeiro: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (1)\n");
  exibirLog(f);
  prioritario = removerElementoFila(f);
  if (prioritario) printf("Primeiro: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (2)\n");
  exibirLog(f);
  prioritario = removerElementoFila(f);
  if (prioritario) printf("Primeiro: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (3)\n");
  exibirLog(f);
  prioritario = removerElementoFila(f);
  if (prioritario) printf("Primeiro: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (4)\n");
  exibirLog(f);
  prioritario = removerElementoFila(f);
  if (prioritario) printf("Primeiro: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (5)\n");
  exibirLog(f);
  prioritario = removerElementoFila(f);
  if (prioritario) printf("Primeiro: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (6)\n");
  exibirLog(f);
  prioritario = removerElementoIdade(f);


  printf("################# INSERINDO NOVAMENTE #############\n");

  if(inserirElemento(f, 6, 1)) printf("ok\n");
  else printf("nok (9)\n");
  exibirLog(f);
  if(inserirElemento(f, 8, 3)) printf("ok\n");
  else printf("nok (10)\n");
  exibirLog(f);
  if(inserirElemento(f, 7, 2)) printf("ok\n");
  else printf("nok (11)\n");
  exibirLog(f);
  if(inserirElemento(f, 5, 1)) printf("ok\n");
  else printf("nok (12)\n");
  exibirLog(f);
  if(inserirElemento(f, 10, 5)) printf("ok\n");
  else printf("nok (13)\n");
  exibirLog(f);
  if(inserirElemento(f, 10, 5)) printf("nok - nao deveria inserir repetido\n");
  else printf("ok (14) - registro repetido\n");
  exibirLog(f);

  printf("################# REMOVENDO NOVAMENTE #############\n");

  prioritario = removerElementoIdade(f);
  if (prioritario) printf("Prioritario: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (7)\n");
  exibirLog(f);
  prioritario = removerElementoIdade(f);
  if (prioritario) printf("Prioritario: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (8)\n");
  exibirLog(f);
  prioritario = removerElementoIdade(f);
  if (prioritario) printf("Prioritario: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (9)\n");
  exibirLog(f);
  prioritario = removerElementoIdade(f);
  if (prioritario) printf("Prioritario: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (10)\n");
  exibirLog(f);
  prioritario = removerElementoIdade(f);
  if (prioritario) printf("Prioritario: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (11)\n");
  exibirLog(f);
  prioritario = removerElementoIdade(f);
  if (prioritario) printf("Prioritario: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (12)\n");
  exibirLog(f);
  prioritario = removerElementoIdade(f);
  if (prioritario) printf("Prioritario: %i, %i\n", prioritario->id, prioritario->idade);
  else printf("Fila vazia (13)\n");
  exibirLog(f);

  printf("################# OUTROS TESTES ###################\n");

  if(inserirElemento(f, 50, 20)) printf("ok\n");
  else printf("nok (15)\n");
  exibirLog(f);
  if(inserirElemento(f, 60, 60)) printf("ok\n");
  else printf("nok (10)\n");
  exibirLog(f);
  if(inserirElemento(f, 70, 15)) printf("ok\n");
  else printf("nok (11)\n");
  exibirLog(f);
  if(inserirElemento(f, 80, 70)) printf("ok\n");
  else printf("nok (11)\n");
  exibirLog(f);

  id = 50;
  if (consultarIdade(f,id,&idade)) printf("Elemento encontrado: %i, %i\n", id, idade);
  else printf("Elemento com identificador: %i nao encontrado\n", id);
  id = 40;
  if (consultarIdade(f,id,&idade)) printf("Elemento encontrado: %i, %i\n", id, idade);
  else printf("ok Elemento com identificador: %i nao encontrado\n", id);
  id = 80;
  if (consultarIdade(f,id,&idade)) printf("Elemento encontrado: %i, %i\n", id, idade);
  else printf("Elemento com identificador: %i nao encontrado\n", id);

  printf("\n");
  if (abandonarFila(f,88)) printf("nok - Excluiu elemento inexistente: id=88\n");
  else printf("ok - Elemento nao existente id=88\n");
  exibirLog(f);
  if (abandonarFila(f,60)) printf("ok - Excluiu elemento: id=60\n");
  else printf("nok - Elemento nao existente id=60\n");
  exibirLog(f);
  if (abandonarFila(f,80)) printf("ok - Excluiu elemento: id=80\n");
  else printf("nok - Elemento nao existente id=80\n");
  exibirLog(f);
  if (abandonarFila(f,50)) printf("ok - Excluiu elemento: id=50\n");
  else printf("nok - Elemento nao existente id=50\n");
  exibirLog(f);
  if (abandonarFila(f,70)) printf("ok - Excluiu elemento: id=70\n");
  else printf("nok - Elemento nao existente id=70\n");
  exibirLog(f);


  return 0;
}