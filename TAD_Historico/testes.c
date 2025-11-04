#include "historico.h"
#include <stdio.h>

//Esse main serve para testes.

int main() {
    
    int t;
    HISTOR *h;
    PROCED *proced1, *proced2, *proced3;
    h = histor_criar();
    
    //Criando nova pilha e apagando dois valores
    proced1 = proced_criar("Implante");
    proced2 = proced_criar("Cirurgia");
    proced3 = proced_criar("Terapia");
    histor_inserir(h, proced1);
    histor_inserir(h, proced2);
    histor_inserir(h, proced3);

    
    proced1 = histor_remover(h);
    printf("%s\n", proced_get_proced(proced1));
    proced_apagar(&proced1);

    proced1 = histor_remover(h);
    printf("%s\n", proced_get_proced(proced1));
    proced_apagar(&proced1);

    
    //Salvando em arquivo como o histórico deu um paciente
    PACIENTE *p = paciente_criar("João", 1);

    histor_salvar(&h, p);
    
    //Recarregando a pilha da memória e adicionando mais um valor
    h = histor_criar();
    histor_carregar(h, p); //Temos que conseguir recuperar o histórico de João

    proced1 = proced_criar("Cirurgia Cardiaca");
    histor_inserir(h, proced1);
    
    printf("\n");
    histor_consultar(h);

    histor_salvar(&h, p);


    //Criando um histórico e paciente diferentes para testar
    HISTOR *h2 = histor_criar();

    PACIENTE *p2 = paciente_criar("Fernanda", 2);
    proced2 = proced_criar("Cirurgia Geral");
    proced3 = proced_criar("Implante");

    histor_inserir(h2, proced2);
    histor_inserir(h2, proced3);

    histor_salvar(&h2, p2);

    
    return 0;
}

