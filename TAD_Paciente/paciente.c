#include "paciente.h"
#include <stdlib.h>
#include <string.h>

struct paciente {
    char* nome;
    int id;
};

PACIENTE* paciente_criar(char* nome, int id) {

    //Alocando espaço p/ struct
    PACIENTE* p = (PACIENTE*) malloc(sizeof(PACIENTE));

    if (p != NULL) {

        //Alocando espaço p/ nome + '\0'
        p->nome = (char*) malloc(sizeof(char) * (strlen(nome) + 1));
        strcpy(p->nome, nome);

        p->id = id;

        return p;
    }

    return NULL;
}

bool paciente_apagar(PACIENTE** p) {

    if (*p != NULL) {

        //Liberando alocação do nome
        free((*p)->nome);
        (*p)->nome = NULL;

        //Liberando alocação da struct
        free(*p);
        *p = NULL;

        return true;
    }
    
    return false;
}

char* paciente_get_nome(PACIENTE* p) {

    if (p != NULL) {
        return p->nome;
    }

    return NULL;
}

int paciente_get_id(PACIENTE* p) {

    if (p != NULL) {
        return p->id;
    }

    return -1; //Retorna ID inválido caso o paciente não exista.
}

bool paciente_set_nome(PACIENTE* p, char* nome) {

    if (p != NULL) {

        //Realocando espaço para o novo nome
        p->nome = realloc(p->nome, sizeof(char) * strlen(nome) + 1);
        strcpy(p->nome, nome);

        return true;
    }

    return false;
}

bool paciente_set_id(PACIENTE* p, int id) {

    if (p != NULL) {

        p->id = id;
        return true;
    }

    return false;
}