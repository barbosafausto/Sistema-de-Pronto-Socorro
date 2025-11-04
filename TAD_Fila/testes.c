#include "fila.h"
#include <stdio.h>

//Arquivo para testes!

int main() {
	
	
	FILA* Espera = fila_criar(); //Cria uma fila de "Espera", 4 pacientes e os insere na fila.
	PACIENTE* Um = paciente_criar("Joao", 1);
	PACIENTE* Dois = paciente_criar("Maria", 2);
	PACIENTE* Tres = paciente_criar("Regina", 3);
	PACIENTE* Quatro = paciente_criar("Paulo", 4);

	//Inserção agora
	fila_inserir(Espera, Um);
	fila_inserir(Espera, Dois);
	fila_inserir(Espera, Tres);
	fila_inserir(Espera, Quatro);

	//Vamos remover o paciente e imprimi-lo. O output precisa ser "João".
	printf("%s\n", paciente_get_nome(fila_remover(Espera))); 

	//Vamos apagar a fila
	fila_salvar(&Espera);
	
	Espera = fila_carregar(); 
	
	//Após carregar, voltamos aonde estávamos. O nome impresso precisa ser "Maria"
	printf("%s\n", paciente_get_nome(fila_remover(Espera))); 
	
	//Regina e Paulo
	printf("%s\n", paciente_get_nome(fila_remover(Espera))); 
	printf("%s\n", paciente_get_nome(fila_remover(Espera))); 

	//Essa remoção retorna NULL porque a fila precisa estar vazia.
	PACIENTE* p = fila_remover(Espera);
	if (p == NULL) printf("Missão cumprida!\n");

    return 0;
}

