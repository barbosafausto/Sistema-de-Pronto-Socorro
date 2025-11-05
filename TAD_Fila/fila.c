#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

struct fila {
	PACIENTE* cadastro[LIM];  //Cada paciente da fila é um ponteiro guardado no vetor. "LIM" é a capacidade máxima de atendimento do hospital, e portanto, o tamanho máximo da fila.
	int frente;
	int fundo;
	int tamanho;
	/*
	"Tamanho" é a quantidade de pacientes atualmente na fila.
	"Frente" é o índice da posição no vetor "Cadastro" que contém o ponteiro para o paciente na frente da fila, ou seja, o próximo paciente a ser removido.
	"Fundo" é o índice da posição no vetor "Cadastro" que contém o ponteiro para o paciente mais recentemente adicionado na fila.
	*/
};

FILA* fila_criar(void) {

	//Alocação de espaço p/ struct.
	FILA* fila = (FILA*) malloc(sizeof(FILA)); 
	if (fila != NULL) {
		
		//Inicialização dos parâmetros.
		fila->tamanho = 0;
		fila->frente = 0;
		fila->fundo = 0;
		return(fila);
	}

	return(NULL);
}

bool fila_inserir(FILA* fila, PACIENTE* paciente) {
	if (fila != NULL && !fila_cheia(fila)) {

		//Colocando paciente na fila
		fila->cadastro[fila->fundo] = paciente;

		//Atualizando tamanho e posição do ponteiro 
		fila->tamanho++;
		fila->fundo = (fila->fundo + 1) % LIM;
		/*
		"fila->fundo" recebe + 1, tornando-se o índice da próxima posição do vetor.
		Como "LIM" é o tamanho máximo do vetor, caso "fila->fundo + 1" seja igual a "LIM" o índice estaria marcando uma posição inválida.
		Portanto, além de aumentar "fila->fundo" por 1, também obtém-se o resto de sua divisão por "LIM".
		Caso "fila->fundo + 1" for menor que "LIM", o resto mantém-se como "fila->fundo + 1". Caso "fila->fundo" for igual a "LIM", o resto será 0, a primeira posição do vetor, resultando em uma fila circular.
		*/
		return(true);
	}

	return(false);
}

PACIENTE* fila_remover(FILA* fila) {

	if (fila != NULL && !fila_vazia(fila)) {

		PACIENTE* aux;
		aux = fila->cadastro[fila->frente]; //Cria-se um novo ponteiro para paciente e o faz apontar para o paciente na frente da fila.

		fila->cadastro[fila->frente] = NULL; //O ponteiro antigo é removido.
		fila->frente = (fila->frente + 1) % LIM; //Mesma lógica que "fila->fundo = (fila->fundo + 1) % LIM;" na função "bool fila_inserir(FILA* fila, PACIENTE* paciente)".

		fila->tamanho--;

		return(aux); //Não é necessário desalocar "fila->cadastro[fila->frente]" pois o vetor contém apenas um ponteiro para o paciente, não o paciente em si.
	}

	return(NULL);
}

PACIENTE* fila_frente(FILA* fila) {

	if (fila != NULL && !fila_vazia(fila)) { 
		return(fila->cadastro[fila->frente]); //Retorna o paciente na frente da fila sem removê-lo.
	}

	return(NULL);
}

bool fila_cheia(FILA* fila) {

	if (fila != NULL && fila->tamanho == LIM) {
		return(true);
	}

	return(false);
}
	
bool fila_vazia(FILA* fila) {
	if (fila != NULL && fila->tamanho == 0) {
			return(true);
	}
	
	return(false);
}

int fila_tamanho(FILA* fila) {
	if (fila != NULL) {
		return(fila->tamanho);
	}

	return(0);
}

bool fila_salvar(FILA** fila) {

	/*
	Nessa função, não ficamos responsáveios por desalocar os pacientes.
	Apenas lidamos com a desalocação da fila e deixamos os pacientes com o cliente.
	*/

	if (fila != NULL && *fila != NULL) {

		FILE* arquivo;

		//Abertura em modo de escrita, se arquivo já existir, sobrescreve.
		arquivo = fopen("../TAD_Fila/fila.txt", "w"); 
		if (arquivo == NULL) {
			
			fputs("Erro ao salvar a fila.\n", stderr);
			return(false);
		}
		

		/*Vamos seguir um padrão:
		Linha vazia
		ID 
		Nome
		Linha vazia
		ID
		Nome
		*/
		while(!fila_vazia(*fila)) { 

		    fputc('\n', arquivo);

			PACIENTE *p = fila_remover(*fila);
			fprintf(arquivo, "%d\n", paciente_get_id(p));
			fprintf(arquivo, "%s\n", paciente_get_nome(p));
			
			paciente_apagar(&p);
		}
		//Fechamento do arquivo.
		fclose(arquivo);

		//Desalocação da fila.
		free(*fila);
		*fila = NULL;

		return(true);
	}

	return(false);
}


FILA* fila_carregar(void) {

	FILA* fila = fila_criar();
	if (fila == NULL) {
		
		return(NULL);
	}

	FILE* arquivo;

	//Abertura em modo de leitura.
	arquivo = fopen("../TAD_Fila/fila.txt", "r");
	//Como o hospital possui apenas uma única fila, não é necessário um sistema para poder salvar filas diferentes.
	if (arquivo  == NULL) {

		return fila; //Se o ponteiro para arquivo for nulo, então não existe um arquivo de backup (fila vazia)
	}

	
	int id, c;
	char nome[100]; //Assumimos que ninguém tem 99 caracteres no próprio nome.
	while(true) {
		
		while ((c = fscanf(arquivo, "%d", &id)) == 0) { //Enquanto o scanf não encontrar um inteiro...

			//...vamos mover o cursor.
			c = fgetc(arquivo);

			if (c == -1) break;
		}
		
		//Se o fscanf retornou EOF, encerramos também.
		if (c == -1) {
			break;
		}

		//Se não é EOF e saiu do loop, é inteiro. Seguimos para o nome do paciente:
		fscanf(arquivo, " %[^\n]", nome);
		fila_inserir(fila, paciente_criar(nome, id)); //Missão cumprida para o paciente atual.
	}

	//Fechamento do arquivo.
	fclose(arquivo);
	
	return(fila);
}

bool fila_buscar(FILA *fila, int id){
	bool flag = false;
	if(fila != NULL){
		int pos = fila->frente;
		int i = 0;
		while(i < fila->tamanho){
			if(paciente_get_id(fila->cadastro[pos]) == id){
				flag = true;
				break;
			}
			pos += (pos + 1)%LIM;
			i++;
		}
	}
	return flag;
}