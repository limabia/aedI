/*Pergunta 4. Definimos deque como uma estrutura duplamente ligada (sem nós cabeças), 
onde é possível inserir ou remover os elementos do qualquer uma de suas entradas 
(acessíveis pelos endereços inicio1 e inicio2, que terão valor NULL [ambos]
 caso o deque esteja vazio). Utilizamos as definições abaixo:*/

typedef int TIPOCHAVE;

typedef struct tempRegistro{
  TIPOCHAVE chave;
  struct tempRegistro *prox;
  struct tempRegistro *ant;
} REGISTRO;

typedef REGISTRO* PONT;

typedef struct {
  PONT inicio1;
  PONT inicio2; 
} DEQUE;

/* Inserção no deque, entrada 1 */
bool inserirDeque1(REGISTRO reg, DEQUE *l) {

}

/* Exclusão do primeiro elemento, entrada 2 do deque e colocar o valor da chave do elemento
 na memoria apontada por ch*/
bool excluirElemDeque2(DEQUE *l, TIPOCHAVE * ch){
	
}