#ifndef CLIENTE_H
    #define CLIENTE_H

    #include "../TAD_Procedimento/procedimento.h"
    #include "../TAD_Paciente/paciente.h"

    #include "../TAD_Historico/historico.h"
    #include "../TAD_Registro/registro.h"
    #include "../TAD_Fila/fila.h"
    

    //O cliente precisa carregar o registro e a fila da memória ao usar o sistema.
    REGISTRO* carregar_registro();
    FILA* carregar_fila();

    //Inserir paciente na fila de espera e registrá-lo (se ele não tiver registro)
    //IMPORTANTE: não pode haver IDs repetidos!
    bool registrar_paciente(REGISTRO* r, FILA* f, char* paciente, int id);

    //Remover paciente do registro
    bool registrar_obito(REGISTRO* r, FILA* f, int id);

    //Adicionar procedimento na pilha de procedimentos do paciente
    bool adicionar_procedimento(REGISTRO* r, int id, char* proced);
    
    //Desfazer procedimento na pilha de procedimentos do paciente
    bool desfazer_procedimento(REGISTRO* r, int id);


    //Vamos retirar o primeiro da fila
    int chamar_paciente(FILA* f);

    //Autoexplicativo
    void mostrar_fila(FILA* f);

    //Autoexplicativo
    void mostrar_historico(REGISTRO *r, int id);

    
    //A função abaixo vai salvar as informações relevantes em arquivo
    //Após isso, ela vai encerrar a execução do sistema
    void sair(REGISTRO** r, FILA** f);
#endif