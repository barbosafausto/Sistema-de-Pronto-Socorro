#include "registro.h"
#include <stdio.h>

//Arquivo somente para testes!
/*
Todos os arquivos de testes estão com memory leaks porque não desalocamos o espaço criado para o testes
Isso é proposital, visto que os arquivos servem apenas como testes
*/

/*int main() {

    REGISTRO* r = registro_criar();

    PACIENTE* fer = paciente_criar("Fernanda", 1);
    PACIENTE* ana = paciente_criar("Ana", 2);
    PACIENTE* carlos = paciente_criar("Carlos", 3);
    PACIENTE* fausto = paciente_criar("Fausto", 4);
    PACIENTE* gleyce = paciente_criar("Gleyce", 5);

    registro_inserir(r, fer);
    registro_inserir(r, ana);
    registro_inserir(r, carlos);

    printf("Lista de registrados:\n");
    registro_listar(r);

    registro_apagar(r, ana);
    printf("\nLista de registrados:\n"); //Sem a Ana
    registro_inserir(r, fausto);
    registro_inserir(r, gleyce);
    registro_listar(r);

    printf("Agora, registro em arquivo!\n");
    registro_salvar(&r);

    printf("Por fim, carregando do arquivo. xD\n");
    REGISTRO* new_r  = registro_carregar();

    printf("Pacientes carregados:\n");
    registro_listar(new_r);

    

    
}*/

