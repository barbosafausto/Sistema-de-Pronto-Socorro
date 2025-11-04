#include "cliente.h"
#include <stdlib.h>
#include <stdio.h>

REGISTRO* carregar_registro() {

    REGISTRO* r = registro_carregar();

    if (!r) 
        fputs("Erro ao carregar o registro do disco.\n", stderr);

    return r;
}

FILA* carregar_fila() {

    FILA* f = fila_carregar();

    if (!f) 
        fputs("Erro ao carregar a fila do disco.\n", stderr);

    return f;
}

bool registrar_paciente(REGISTRO* r, FILA* f, char* paciente, int id) {

	PACIENTE* p_fila;
	PACIENTE* p_reg;
	HISTOR *h;
	bool registrado = false;
	if ((p_reg = registro_buscar_paciente(r, id)) == NULL) {

		p_reg = paciente_criar(paciente, id); //Um paciente é criado com os dados passados pela função, e caso exista outro paciente com o mesmo ID uma mensagem de erro é exibida.
		h = histor_criar();
		if ((registrado = registro_inserir(r, p_reg, h)) == false) {

			paciente_apagar(&p_reg);
			histor_apagar(&h);
			printf("Erro no registro do paciente.\n");
		}
	}

	else if (fila_buscar(f, id)) {
		printf("Paciente já está na fila");
	}

	else {
		registrado = true;
	}
	//Colocando na fila
	if (registrado) {
		p_fila = paciente_criar(paciente, id); 
		if (fila_inserir(f, p_fila) == true) {

				printf("Um novo registro foi criado e o paciente entrou na fila de espera!\n");
				return(true);
		}
		else {
			
			paciente_apagar(&p_fila);
			printf("Um novo registro foi criado, mas houve um erro na inserção do paciente na fila.\n");
			return(false);
		}
	}

	return false;
}

bool registrar_obito(REGISTRO* r, int id) {

    //A função registro_apagar() já faz todas as verificações de segurança.
    int flag = registro_apagar(r, id);

    if (flag) return true;

    fputs("Erro ao apagar paciente do registro.\n", stderr);
    return false;


}

void sair(REGISTRO** r, FILA** f) {

    //Salvando o registro e a fila em arquivo
    fila_salvar(f);
    registro_salvar(r);

    //Saindo do sistema
    exit(0);

}

void mostrar_fila(FILA* f) {
	if (f != NULL) {
		if (fila_vazia(f) == false) {//fila_vazia checa se a fila existe, mas está em um && com uma checagem do tamanho da fila.
		

			printf("-----FILA DE ESPERA-----\n");
			for (int i = 0; i < fila_tamanho(f); i++) 
			{
				printf("%dº paciente\n\nID: %d\nNome: %s\n-----\n", (1+i), paciente_get_id(fila_frente(f)), paciente_get_nome(fila_frente(f)));
				fila_inserir(f, fila_remover(f));
			}
		}
		else
		{
			printf("A fila está vazia!\n");
			return;
		}
	}
	else
	{
		printf("Esta fila não existe!\n");
		return;
	}
}

int chamar_paciente(FILA* f) {
	
		if (fila_vazia(f) == false) { //fila_remover checa se a fila está vazia, mas está em um && com uma checagem se a fila existe.
			
			PACIENTE *p = fila_remover(f);
			int id = paciente_get_id(p);

			//Precisamos desalocar, porque agora o paciente não está mais na fila
			free(p);
			p = NULL;

			return(id);
		}
		else {
			printf("A fila está vazia!\n");
			return(-1);
		}
}

bool adicionar_procedimento(REGISTRO *r, int id, char* proced){

	HISTOR *h = registro_buscar_histor(r, id);
	PROCED *proc;
	
	if(h != NULL){

		proc = proced_criar(proced);
		if(proc == NULL) {
			fputs("Desculpe, houve um erro ao criar o procedimento", stderr);
			return false;
		}

		if(histor_inserir(h, proc) == false){
			fputs("Desculpe, houve um erro ao inserir um procedimento", stderr);
			return false;
		}

	}
	else fputs("Erro CLIENTE - ponteiro inválido de histórico", stderr);
	return false;
}

bool desfazer_procedimento(REGISTRO* r, int id) {

	HISTOR *h = registro_buscar_histor(r, id);
	PROCED *proc;

	if(h != NULL){

		proc = histor_remover(h);
		if(proc == NULL){

			fputs("Desculpe, houve um erro ao remover o procedimento", stderr);
			return false;
		}
		proced_apagar(&proc);
		return true;
	}
	return false;
}


void mostrar_historico(REGISTRO* r, int id) {

	HISTOR *h = registro_buscar_histor(r, id);
	PACIENTE *p = registro_buscar_paciente(r, id);

	printf("ID: %d\n",id);
	printf("Nome: %s\n", paciente_get_nome(p));
	printf("Procedimentos:\n");
	histor_consultar(h);
}
