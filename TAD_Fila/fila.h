#ifndef FILA_H
	#define FILA_H

	#include "../TAD_Paciente/paciente.h"

	#define LIM 20 //Capacidade de atendimento do hospital
	
	typedef struct fila FILA;
	
    /*
    As funções que retornam ponteiros retornarão NULL se mal-sucedidas,
    as que retornam booleano irão retornar false se mal-sucedidas.
    */

	FILA* fila_criar(void); 

	bool fila_inserir(FILA* fila, PACIENTE* paciente); 
	PACIENTE* fila_remover(FILA* fila); 
	PACIENTE* fila_frente(FILA* fila); //Retorna o paciente na frente da fila, mas sem o remover dela.

	//Consideramos que filas inexistentes não ficam cheias ou vazias, mas indefinidas.
	bool fila_cheia(FILA* fila); 
	bool fila_vazia(FILA* fila);
	bool fila_buscar(FILA *fila, int id); //Retorna true se o paciente estiver na fila
	int fila_tamanho(FILA* fila); //Retorna 0 se o ponteiro for inválido.

	bool fila_salvar(FILA** fila); //Salva a fila em um arquivo de texto (apaga a fila)
	FILA* fila_carregar(void); //Carrega uma fila salva em arquivo de texto (cria uma fila)
	
#endif
