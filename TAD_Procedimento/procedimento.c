#include "procedimento.h"
#include <stdlib.h>
#include <string.h>

struct procedimento {
    char* p;
};

PROCED* proced_criar(char* p) {

    //Alocando espaço p/ struct
    PROCED* proced = (PROCED*) malloc(sizeof(PROCED));

    if (proced != NULL) {
        
        //Alocando o tamanho da string + '\0'
        proced->p = (char*) malloc(sizeof(char) * strlen(p) + 1);
        strcpy(proced->p, p); 

        return proced;
    }

    return NULL;
}

bool proced_apagar(PROCED** proced) {

    if (*proced != NULL) {

        free((*proced)->p); //Liberando a alocação p/ string
        (*proced)->p = NULL;

        free(*proced); //Liberando a alocação p/ struct
        *proced = NULL;

        return true;
    }
    
    return false;
}

char* proced_get_proced(PROCED* proced) {

    if (proced != NULL) {

        return proced->p;
    }

    return NULL;
}

bool proced_set_proced(PROCED* proced, char* p) {

    if (proced != NULL) {

        //Realocando para o tamanho da string nova
        proced->p = (char*) realloc(proced->p, sizeof(char) * strlen(p) + 1);
        strcpy(proced->p, p);

        return true;
    }

    return false;
}