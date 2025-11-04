#ifndef HISTORICO_H
    #define HISTORICO_H
    
    #include "../TAD_Procedimento/procedimento.h"
    #include "../TAD_Paciente/paciente.h"

    typedef struct histor HISTOR;

    /*
    As funções que retornam ponteiros retornarão NULL se mal-sucedidas,
    as que retornam booleano irão retornar false se mal-sucedidas.
    */

    HISTOR *histor_criar();

    void histor_salvar(HISTOR **h, PACIENTE *p);

    /*Recebe um ponteiro de pilha e o nome do arquivo em que está os dados a serem armazenados na pilha.
    Lê o arquivo até o seu fim, pegando cada linha como string e criando um procedimento com essa string (sem a quebra de linha).
    A pilha final passada como parâmetro terá como primeiro valor o procedimento, cuja string é a última linha, 
    e como topo o procedimento, cuja string é a primeira linha (a mesma ordem da pilha que foi salva).*/
    /*--> OBS1: a função não cria a pilha, somente modifica uma já criada.*/
    void histor_carregar(HISTOR *h, PACIENTE *p);

    /**/
    void histor_apagar(HISTOR **h);
    
    /*Recebe um ponteiro de pilha.
    Verifica se o tamanho é igual ao tamanho máximo, retornando true, se sim; false, senão.*/
    /*--> OBS1: retorna false em caso de ponteiro inválido*/
    bool histor_cheio(HISTOR *h);

    /*Recebe um ponteiro de pilha.
    Verifica se o tamanho é igual a 0, retornando true, se sim; false, senão*/
    /*--> OBS1: retorna true em caso de ponteiro inválido*/
    bool histor_vazio(HISTOR *h);

    /*Recebe um ponteiro de pilha e um ponteiro de procedimento.
    Se a pilha não estiver cheia, faz a próxima posição não ocupada da pilha apontar para
    o procedimento passado como parâmetro. Retorna true, caso consiga fazer a operação; senão, false*/
    bool histor_inserir(HISTOR *h, PROCED *p);

    /*Recebe um ponteiro de pilha.
    Seta para última posição ocupada da pilha (topo) valor NULL, retornando o endereço do procedimento que era apontado por essa posição da pilha.*/
    PROCED *histor_remover(HISTOR *h);

    /*Recebe um ponteiro de pilha.
    Imprime todos as strings dos procedimentos que estão na pilha, separados por quebra de linha.
    A impressão ocorre na ordem de uma pilha (começando pelo topo, terminando pelo primeiro valor inserido)*/
    void histor_consultar(HISTOR *h);

    /*Recebe um ponteiro de pilha.
    Retorna o tamanho (quantidade de valores inseridos) da pilha.*/
    /*--> OBS1: em caso de ponteiro inválido retorna -1*/
    int histor_get_tam(HISTOR *h);
#endif
