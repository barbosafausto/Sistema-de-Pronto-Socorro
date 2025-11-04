//Esse arquivo serve para testar o TAD

#include "procedimento.h"
#include <stdio.h>

int main() {

    PROCED* proced = proced_criar("Implante");
    //Printando, o output precisa ser "Implante"
    printf("%s\n", proced_get_proced(proced));


    proced_set_proced(proced, "Cirurgia");
    //Printando, o output precisa ser "Cirurgia"
    printf("%s\n", proced_get_proced(proced));


    proced_set_proced(proced, "Operação");
    //Printando, o output precisa ser "Operação"
    printf("%s\n", proced_get_proced(proced));

    proced_apagar(&proced);
    if (proced == NULL) printf("Missão cumprida!\n");
    
    return 0;
}

