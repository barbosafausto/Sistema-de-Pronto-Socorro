#ifndef REGISTRO_H
    #define REGISTRO_H

    #include <stdbool.h>

    #include "../TAD_Paciente/paciente.h"
    #include "../TAD_Historico/historico.h"

    typedef struct no NO;
    typedef struct registro REGISTRO;

    REGISTRO* registro_criar(void); //Cria registro

    bool registro_vazio(REGISTRO* r); //Verifica se está vazio
    bool registro_cheio(REGISTRO* r); //Verifica se está cheio

    bool registro_inserir(REGISTRO* r, PACIENTE* p, HISTOR *h); //Insere um nó
    bool registro_apagar(REGISTRO* r, int id, bool salvar); //Apaga um nó

    void registro_listar(REGISTRO* r); //Printa todos os pacientes

    PACIENTE* registro_buscar_paciente(REGISTRO* r, int id); //Retorna false se não achar
    HISTOR* registro_buscar_histor(REGISTRO* r, int id); //Retorna false se não achar

    bool registro_salvar(REGISTRO** r); //Salvar registro em arquivo
    REGISTRO* registro_carregar(void); //Carrega registro de arquivo


#endif