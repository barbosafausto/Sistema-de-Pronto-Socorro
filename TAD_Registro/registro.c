#include "registro.h"
#include <stdio.h>
#include <stdlib.h>

//Cada nó do registro guarda um paciente e seu histórico
//A lista é encadeada porque o limite da lista é a quantidade de memória do servidor
struct no {
    HISTOR* h;    
    PACIENTE* p;
    NO* prox;
    NO* ant; //Fizemos um encadeamento duplo porque achamos essa implementação elegante
};

struct registro {
    
    NO* inicio;
    NO* fim;
    int tam;
};

REGISTRO* registro_criar() {

    REGISTRO* r = (REGISTRO*) malloc(sizeof(REGISTRO));    

    if (r != NULL) { 

        //Inicialização
        r->inicio = NULL;
        r->fim = NULL;
        r->tam = 0;

        return r;
    }
    
    else fputs("Erro na alocação do registro\n", stderr);
    return r; //Se der errado a alocação, vai retornar NULL

}

bool registro_vazio(REGISTRO* r) {

    if (r != NULL) { //Se for válido
        return (r->tam == 0);
    }
    
    fputs("Ponteiro de registro inválido.\n", stderr);
    return false; //Consideramos que uma lista inexistente não está nem vazia nem cheia
}

bool registro_cheio(REGISTRO* r) {

    NO* node = (NO*) malloc(sizeof(NO));

    if (node) { //Se consegue alocar, não está cheio

        free(node);
        node = NULL;

        return false;
    }

    fputs("Desculpe! Não há espaço para criar novos registros.\n", stderr);
    return true;
}
    

bool registro_inserir(REGISTRO* r, PACIENTE* p, HISTOR* h) {
    
    if (registro_cheio(r)) return false; 

    if (r != NULL && p != NULL && h != NULL) { //Se os argumentos forem válidos

        NO* node = (NO*) malloc(sizeof(NO)); //A função registro_cheio já verificou se tem espaço

        node->h = h;
        node->p = p;
        node->prox = NULL;
        node->ant = r->fim;

        //Se lista for vazia
        if (registro_vazio(r)) {

            r->inicio = node;
        }
        else { //Senão, só precisamos mexer no antigo último 
               
            r->fim->prox = node;
        }
        
        r->fim = node;
        r->tam++;

        return true;
    }

    else fputs("Ponteiro inválido.\n", stderr);
    return false;
}

bool registro_apagar(REGISTRO* r, int id, bool salvar) {

    //Essa função apaga o histoŕio e o paciente (através de outras funções), depois apaga o nó em si
    if (r != NULL) {

        NO* node = r->inicio;
        PACIENTE* p_atual;

        while (node != NULL) { //Enquanto não chegamos ao fim

            p_atual = node->p;
            if (paciente_get_id(p_atual) == id) { //Se achamos o paciente, vamos remover o registro
               
                //Se eu não estiver no primeiro nó
                if (node->ant != NULL)
                    node->ant->prox = node->prox; //O anterior pula o nó atual e aponta para o próximo

                //Se eu estiver no primeiro nó
                else {

                    r->inicio = node->prox; //Basta ajustar o inicio para o próximo

                    if (r->inicio) //Se o próximo não for NULL
                        r->inicio->ant = NULL; //Não tem ninguém atrás dele mais, pois o nó atual foi removido
                }

                //Se eu estiver no último no
                if (node->prox == NULL) r->fim = node->ant; //Ajusto o fim para o anterior
                
                int file_num = paciente_get_id(node->p);
                //Desalocando paciente
                paciente_apagar(&node->p);

                //Desalocando o histórico do paciente
                histor_apagar(&node->h);

                //Se não estamos salvando, vamos remover o arquivo do paciente
                if (!salvar) {

                    char file[50];
                    sprintf(file, "../TAD_Historico/proceds/%d.txt", file_num) ;
                    remove(file);
                }
                
                //Desalocando o nó atual
                node->ant = NULL;
                node->prox = NULL;
                free(node);
                node = NULL;

                r->tam--;

                return true;
            }

            node = node->prox;
        }

        printf("Paciente não encontrado no registro. Por favor, verifique se a ID informada está correta.\n"); 
        return false;
    }

    else fputs("Ponteiro de registro inválido.\n", stderr);
    return false;
}

void registro_listar(REGISTRO* r) {

    if (r == NULL) { 
        
        fputs("Ponteiro de registro inválido.\n", stderr);
        return;
    }

    printf("----PACIENTES REGISTRADOS----\n");
    
    if (registro_vazio(r)) return; //Se estiver vazio, para aqui

    NO* node = r->inicio;
    while (true) {

        PACIENTE* p = node->p;

        printf("%d\n", paciente_get_id(p));
        printf("%s\n", paciente_get_nome(p));

        node = node->prox;

        if (node == NULL) break;

        printf("\n"); //Quebra de linha se ainda não for o último nó
    }
    printf("---------\n");
}

PACIENTE* registro_buscar_paciente(REGISTRO* r, int id) {

    if (r == NULL) {

        fputs("Ponteiro de registro e/ou paciente inválido.\n", stderr);
        return NULL;
    }

    NO* node = r->inicio;
    PACIENTE* atual;

    while (node != NULL) {

        atual = node->p; 

        if (paciente_get_id(atual) == id) {
            return atual;
        }
        
        node = node->prox;
    }

    printf("O paciente não está registrado.\n");
    return NULL; //Retorna NULL se não encontrar o paciente
}

HISTOR* registro_buscar_histor(REGISTRO* r, int id) { //Busca o histórico de um paciente

    if (r == NULL) {

        fputs("Ponteiro de registro e/ou histórico inválido.\n", stderr);
        return NULL;
    }

    NO* node = r->inicio;

    while (node != NULL) {

        if (paciente_get_id(node->p) == id) {
            return node->h; //Única diferença: retorna o ponteiro para o histórico
        }
        
        node = node->prox;
    }

    printf("O paciente não está registrado.\n");
    return NULL;
}

bool registro_salvar(REGISTRO** r) {

    if (r == NULL || *r == NULL) {

        fputs("Ponteiro de registro inválido.\n", stderr);
        return false;
    }

    //Vamos abrir o arquivo em modo de escrita
    FILE* file = fopen("../TAD_Registro/registro.txt", "w"); 
    if (file == NULL) {

        fputs("Erro na abertura do arquivo.\n", stderr);
        return false;
    }

    NO* node = (*r)->inicio;
    PACIENTE* p;
    HISTOR* h;

    while (node != NULL) {

        p = node->p;

        fprintf(file, "%d\n", paciente_get_id(p));
        fprintf(file, "%s\n", paciente_get_nome(p));
        fprintf(file, "\n");

        histor_salvar(&node->h, p); //Estamos salvando o histórico com a função responsável
        //A função histor_salvar vai fazer com que node->h = NULL, o que é essencial

        node = node->prox;

        registro_apagar(*r, paciente_get_id(p), true); //Agora sim: apagamos o registro (pacientes e nós)
        //A função registro_apagar vai tentar apagar oo históricos, mas como node->h = NULL, não teremos problemas

        //Nós fizemos dessa forma porque, em caso de óbito, vamos precisar fazer com que a função registro_apagar apague o histórico sem salvar
    }
    fclose(file);
    file = NULL;

    free(*r);
    *r = NULL;

    return true;
}

REGISTRO* registro_carregar(void) {

    //Abrindo arquivo em modo de leitura
    FILE* file = fopen("../TAD_Registro/registro.txt", "r");

    if (file == NULL) {

        fputs("Erro na abertura do arquivo.\n", stderr);
        return NULL;
    }

    REGISTRO* r = registro_criar(); //Alocando espaço para o registro
    PACIENTE* p;
    HISTOR* h;

    if (r == NULL) {

        fputs("Erro ao tentar alocar espaço para o registro.\n", stderr);
        return NULL;
    }

    char nome[100]; //Estimative segura: ninguém tem um nome de 100 caracteres
    int id, c;
    while (true) {

        //A nossa ideia é ler até achar a id do paciente. Após isso, temos certeza que a próxima linha contém o seu nome
        while((c = fscanf(file,"%d", &id)) == 0) {

            c = fgetc(file); //Consome caractere 

            if (c == -1) break; //Se for EOF, encerra
             
        }
        
        if (c == -1) { //Se for EOF, encerra
            break;
        }

        //Se não foi EOF, foi um número inteiro
        fscanf(file, " %[^\n]", nome); //Pedimos o nome

        p = paciente_criar(nome, id);
        h = histor_criar();
        
        //Todos pacientes registrados têm historico
        histor_carregar(h, p); //Carregando o histórico do paciente
        registro_inserir(r, p, h); //Inserindo o nó na lista
    }

    fclose(file);
    file = NULL;

    return r;
}