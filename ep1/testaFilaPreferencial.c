#include "filaPreferencial.c"

PONT ponteiros[20];
int pontPos = 0;

char nomes[20][100] = {"Maria","João", "Carlos", "(ง ͠° ͟ل͜ ͡°)ง", "Mario", "Fernando", "Fábio", "Pedro", "Ana", "Paula", 
		      "Robervaldo", "Gil", "Lucas", "( ͡° ͜ʖ ͡°)", "( ͡^ ͜ʖ ͡^)", "Dilma", "Metheus", "Lula", "Caio", "k"}; 

int idIdade[20][2] = { {5, 23}, {10, 20}, {15, 30}, {20, 42}, {25, 99}, {30, 55}, {35, 54}, {40, 100}, {45, 52}, {50, 51}, 
		        {55, 20}, {60, 11}, {65, 3}, {70, 23}, {75, 24}, {80, 24}, {85, 87}, {90, 51}, {95, 34}, {100, 65}};

/*
  Dado um id retorna o endereço do REGISTRO
*/
PONT pegaEndereco(PFILA f, int id) {
	PONT aux = f->inicioFila;
	while(aux != NULL && aux->id != id) aux = aux->proxFila;
	if(aux->id == id) return aux;
	return NULL; 
}

/*
  Dado o endereço do ponteiro, verifica qual é o índice desse ponteiro no vetor
  "ponteiros" e retorna o nome do vetor "nomes" de mesmo índice que o ponteiro
*/
char * pegaNome(PONT p) {
	if(!p) return NULL;
	int i;
	for(i = 0; i < sizeof(ponteiros) / sizeof(PONT); i++) if(p == ponteiros[i]) return nomes[i];
	return NULL;
}

void imprimeFilaComum(PFILA f) {
	PONT aux = f->inicioFila;

	printf("\tFILA COMUM - Quantidade: [%d]\n\t", tamanho(f));
	while(aux != NULL) {
		printf(" %s <-[(%d){%d}-%s]-> %s  ", pegaNome(aux->antFila), aux->id, aux->idade, pegaNome(aux), pegaNome(aux->proxFila));
		aux = aux->proxFila;
	}
	printf("\n\n");
}

bool procuraElementoFila(PFILA f, PONT procurado) {
	PONT aux = f->inicioFila;
	while(aux != NULL) {
		if(aux == procurado) return true;
		aux = aux->proxFila;
	}
	return false;
}

bool procuraElementoPreferencial(PFILA f, PONT procurado) {
	PONT aux = f->preferencial;
	while(aux != NULL) {
		if(aux == procurado) return true;
		aux = aux->proxIdade;
	}
	return false;
}

void imprimeFilaPreferencial(PFILA f) {
	PONT aux = f->preferencial;

	printf("\tFILA PREFERENCIAL - Quantidade: [%d]\n\t", tamanho(f));
	while(aux != NULL) {
		printf(" %s <-[(%d){%d}-%s]-> %s  ", pegaNome(aux->antIdade), aux->id, aux->idade, pegaNome(aux), pegaNome(aux->proxIdade));
		aux = aux->proxIdade;
	}
	printf("\n\n");
}

/*
  ##################################################################
  ######################## FUNÇÕES DE TESTE ########################
  ##################################################################
*/

int testaInsercao(PFILA f, int comeco, int fim) {
	int i, erro;
	erro = 0;
	
	printf("#######################################################\n");
	printf("################## TESTE DE INSERÇÃO ##################\n");
	printf("#######################################################\n\n");

	printf("[!] Inserindo %d elementos\nPadrão: NOME, ID - IDADE\n\n", (fim - comeco));
	for(i = comeco; i < fim; i++) {
		printf("%s, %d - %d   ", nomes[i], idIdade[i][0], idIdade[i][1]);
		if(inserirElemento(f, idIdade[i][0], idIdade[i][1])) {
			ponteiros[pontPos] = pegaEndereco(f, idIdade[i][0]);
			pontPos++;
			printf("Status: OK {\n\n");

			imprimeFilaComum(f);
			imprimeFilaPreferencial(f);
		} else {
			erro++;
			printf("Status: ERRO {\n");
		}
		printf("}\n\n");
	}

	printf("\n\n[!] Teste de registro repetido:\n\n\n");
	for(i = comeco; i < fim; i+=2) {
		printf("%s, %d - %d\n", nomes[i], idIdade[i][0], idIdade[i][1]);
		printf("Tamanho da fila antes: %d\n", tamanho(f));
		if(inserirElemento(f, idIdade[i][0], idIdade[i][1])) {
			erro++;
			printf("Tamanho da fila depois: %d\n", tamanho(f));
			printf("Status: ERRO\n\n");
		} else {
			printf("Tamanho da fila depois: %d\n", tamanho(f));
			printf("Status: OK\n\n");
		}
	}
	
	return erro;
}

int testaRemocaoComum(PFILA f) {
	PONT removido;
	int erro = 0;
		
	printf("#######################################################\n");
	printf("############### TESTE DE REMOÇÃO COMUM ################\n");
	printf("#######################################################\n\n");

	printf("[!] - Teste de Remoção total\n\n");
	printf("------------------------------------------------ Fila antes da remoção ------------------------------------------------\n");
	imprimeFilaComum(f);
	imprimeFilaPreferencial(f);
	printf("-----------------------------------------------------------------------------------------------------------------------\n");

	bool encontradoComum;
	bool encontradoPreferencial;

	do {
		removido = removerElementoFila(f);

		encontradoComum = procuraElementoFila(f, removido);
		encontradoPreferencial = procuraElementoPreferencial(f, removido);

		if(removido) {
			printf("\n\nRemovido: %s, %d - %d   {\n\n", pegaNome(removido), removido->id, removido->idade);
			imprimeFilaComum(f);
			imprimeFilaPreferencial(f);
			if(encontradoComum || encontradoPreferencial) {
				if(encontradoComum) printf("ERRO: elemento encontrado na fila comum\n");
				if(encontradoPreferencial) printf("ERRO: elemento encontrado na fila preferencial\n");
				erro++;
			}
			printf("}\n\n");
		} else printf("Removido: #, # - #   {\n\n\tFila vazia, não há nenhum elemento para remover.\n\n}\n\n");
	} while(removido != NULL);

	return erro;
}

int testaRemocaoIdade(PFILA f) {
	PONT removido;
	int erro = 0;
		
	printf("#######################################################\n");
	printf("############### TESTE DE REMOÇÃO IDADE ################\n");
	printf("#######################################################\n\n");

	printf("[!] - Teste de Remoção total\n\n");
	printf("------------------------------------------------ Fila antes da remoção ------------------------------------------------\n");
	imprimeFilaComum(f);
	imprimeFilaPreferencial(f);
	printf("-----------------------------------------------------------------------------------------------------------------------\n");

	bool encontradoComum;
	bool encontradoPreferencial;

	do {
		removido = removerElementoIdade(f);

		encontradoComum = procuraElementoFila(f, removido);
		encontradoPreferencial = procuraElementoPreferencial(f, removido);

		if(removido) {
			printf("\n\nRemovido: %s, %d - %d   {\n\n", pegaNome(removido), removido->id, removido->idade);
			imprimeFilaComum(f);
			imprimeFilaPreferencial(f);
			if(encontradoComum || encontradoPreferencial) {
				if(encontradoComum) printf("ERRO: elemento encontrado na fila comum\n");
				if(encontradoPreferencial) printf("ERRO: elemento encontrado na fila preferencial\n");
				erro++;
			}
			printf("}\n\n");
		} else printf("Removido: #, # - #   {\n\n\tFila vazia, não há nenhum elemento para remover.\n\n}\n\n");
	} while(removido != NULL);

	return erro;
}

int testaConsultaIdade(PFILA f) {
	int i, id, idade, erro;
	bool busca;
	erro = 0;

	int ids[] =      {2, 6, 75, 90, 86, 78, 55, 70, 86, 85, -1, 0};
	int resultado[] = {0, 0,  1,  1,  0,  0,  1,  1,  0,  1,  0, 0};

	printf("#######################################################\n");
	printf("############### TESTE DE CONSULTA IDADE ###############\n");
	printf("#######################################################\n\n");

	for(i = 0; i < sizeof(ids)/sizeof(int); i++) {
		printf("ID procurado: %d \t", ids[i]);
		busca = consultarIdade(f, ids[i], &idade);

		if(busca) printf("Encontrado - idade: %d\n", idade);
		else printf("Não encontrado\n");

		if(busca && !resultado[i] || !busca && resultado[i]) {
			printf("ERRO\n");
			erro++;
		}

		printf("\n");
	}
}

int main() {
	PFILA f = criarFila();
	testaInsercao(f, 0, 10);
	testaRemocaoComum(f);

	testaInsercao(f, 10, 20);
	testaConsultaIdade(f);
	testaRemocaoIdade(f);

	

	return 0;
}
