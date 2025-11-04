#ifndef PROCED_H 
    #define PROCED_H

    #include <stdbool.h>

    typedef struct procedimento PROCED;

    /*
    As funções que retornam ponteiros retornarão NULL se mal-sucedidas,
    as que retornam booleano irão retornar false se mal-sucedidas.
    */ 

    /*Recebe a string que indica o procedimento.
    Aloca-se o procedimento na memória e retorna o endereço de sua poisção nela.*/
    PROCED* proced_criar(char* p);
    /*Recebe um ponteiro de procedimento por referência.
    desaloca-se a memória e atribui ao ponteiro NULL.*/
    bool proced_apagar(PROCED** proced);

    /*Recebe um ponteiro de procedimentos.
    Retorna a string do procedimento*/
    char* proced_get_proced(PROCED* proced);
    /*Recebe um ponteiro de procedimentos e a nova string.
    Troca a string armazenada pelo procedimento*/
    bool proced_set_proced(PROCED* proced, char* p);

#endif