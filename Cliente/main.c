#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#define TAM_MAX 101

void menu(){
	puts("=-=-=-=-=-HOSPITAL-=-=-=-=-=\n\n");
	puts("Operações: \n");
	puts(" [1] Registrar Paciente\n");
	puts(" [2] Registrar Óbito de Paciente\n");
	puts(" [3] Adicionar Procedimento ao Histórico Médico\n");
	puts(" [4] Desfazer Procedimento ao Histórico Médico\n");
	puts(" [5] Chamar Paciente para Atendimento\n");
	puts(" [6] Mostrar Fila de Espera\n");
	puts(" [7] Mostrar Histórico do Paciente\n");
	puts(" [8] Sair\n");
	puts("Selecione uma: ");
}

void inicializar(REGISTRO **r, FILA **f){
	*r = carregar_registro();
	*f = carregar_fila();
}

int main() {
	int op = 0, id;
	char nome[TAM_MAX];

	REGISTRO *r;
	FILA *f;
	PACIENTE *p;
	inicializar(&r, &f);

	while(1){
		system("clear");
		menu();
		
		if (!scanf(" %d", &op)) op = 0;
		printf("\n");
		switch(op){
			case 1:
				puts("--- Registro de Paciente ---\n");
				puts("ID do novo paciente: ");

				while(!scanf(" %d", &id) || id < 1) {
					
					getchar();
				}

				puts("Nome do paciente: ");
				scanf(" %100[^\n]", nome);

				registrar_paciente(r, f, nome, id);
				break;
			case 2:
				puts("--- Registrador Óbito de Paciente ---\n");
				puts("ID do paciente falecido: ");

				while(!scanf(" %d", &id) || id < 1) {
					
					getchar();
				}

				registrar_obito(r, f, id);
				break;
			case 3:
				puts("--- Adicionar Procedimento ao Histórico Médico ---\n");

				puts("ID do paciente: ");

				while(!scanf(" %d", &id) || id < 1) {
					
					getchar();
				}

				puts("Insira o novo procedimento: ");
				scanf(" %100[^\n]", nome);
				
				adicionar_procedimento(r, id, nome);
				break;
			case 4:
				puts("--- Desfazer Procedimento ao Histórico Médico ---\n");
				puts("ID do paciente: ");

				while(!scanf(" %d", &id) || id < 1) {
					
					getchar();
				}

				desfazer_procedimento(r, id);
				break;
			case 5:
				puts("--- Chamar Paciente para Atendimento ---\n");

				id = chamar_paciente(f);

				if (id == -1) printf("Nenhum paciente foi chamado.\n");
				else printf("Paciente de id %d foi chamado.\n", id);

				break;
			case 6:
				puts("--- Mostrar Fila de Espera ---\n");
				puts("Fila de Espera: \n");

				mostrar_fila(f);

				break;
			case 7:
				puts("--- Mostrar Histórico do Paciente ---\n");
				puts("ID do paciente: ");
				
				while(!scanf(" %d", &id) || id < 1) {
					
					getchar();
				}

				puts("Histórico: \n");
				mostrar_historico(r, id);

				break;
			case 8:
				sair(&r, &f);
				puts("Registros e Fila salvos!\n");
				break;
			default:
				puts("Operação inválida!\n");
		}

		if(op == 8) break;

		printf("\n\nPressione enter para continuar...");
		getchar(); //pega o enter do scanf
		getchar(); //Pegar o enter do "Pressione enter para continuar..."
	}
	
	return 0;
}