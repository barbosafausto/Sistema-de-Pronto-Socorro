# Introdução

### Grupo
* 15512767 - José Fausto Vital Barbosa
* 16862551 - Eduardo Benedini Bueno
* 16816271 - João Pedro Conde Gomes Alves

### Sobre o README

Esse README é dividivido em 2 partes:
* Parte 1 - *Descrição do Sistema*: explicação geral de como o sistema é estruturado
    * TADs que compõem o sistema;
    * Como os TADs se relacionam; e
    * Como o Cliente usa o sistema

* Parte 2 - *Funções do cliente.c*: explicação mais profunda do workflow de cada uma das funções.
    * Como as funções funcionam; e
    * Funções que são chamadas por baixo dos panos

<span style="color: ORANGE">
Professor: a parte 1 é suficiente para te explicar bem o sistema, todavia, em caso de dúvidas, a parte 2 pode te ajudar.
</span>

#
# Descrição do Sistema

Antes de qualquer coisa, é necessário entender a *Estrutura* dos TADs.

## TADs

### TAD Procedimento

O TAD *Procedimento* define um tipo de dado que será armazenado, posteriormente, no *Histórico* do paciente. Cada paciente tem um *Histórico* composto por *Procedimentos*.

```C
struct procedimento {
    char* p;
};
```

### TAD Paciente

O TAD *Paciente* tem uma natureza análoga ao TAD *Procedimento*. Ele será usado na *Fila*. 

```C
struct paciente {
    char* nome;
    int id;
};
```

Em outras palavras:
*  A *Fila* possui um conjunto de *Pacientes*; e
* O *Histórico* possui um conjunto de *Procedimentos*;

### TAD Fila

O TAD *Fila* é, de fato, uma fila, a qual implementa o método FIFO (Fist-In First-Out). Como a capacidade do hospital é limitada e não é muito grande, nós implementamos uma *fila sequencial estática circular*, visto que a implementação é mais simples.

```C
struct fila {
	PACIENTE* cadastro[20];  
	int frente;
	int fundo;
	int tamanho;
};
```

Note que, de fato, a fila é um array de *pacientes*, com ponteiros para a frente e para o fundo, além de tamanho.

### TAD Histórico

O TAD *Histórico* é uma *pilha sequencial estática*, a qual implementa o método LIFO (Last-In First-Out), devido à simplicidade da sua implementação em casos em que o tamanho máximo da pilha está definido e é pequeno, que é o nosso caso. O limite da pilha é de 10 procedimentos por paciente.

Desse modo, o *Histórico* de um paciente é definido por uma struct que possui dois campos. O primeiro campo é um array de procedimentos, enquanto o segundo é o tamanho da pilha, o qual usamos para acessar o seu topo e para verificar se ela está cheia ou vazia.

```C
struct histor {
    PROCED *proceds[10];  
    int tam;
};
```

### TAD Registro

O TAD *Registro* é uma **lista encadeada dinâmica**, visto que o limite do registro do hospital é a capacidade de memória do seu servidor.

Segue a estrutura de um nó do *Registro*:
```C
struct no {
    HISTOR* h;    
    PACIENTE* p;
    NO* prox;
    NO* ant;
};
```

E também o *Registro* em si:
```C
struct registro {
    
    NO* inicio;
    NO* fim;
    int tam;
};
```

Dessa forma, temos uma **lista duplamente encadeada**, com ponteiros para o próximo nó e para o anterior. Note que cada nó guarda as informações:
* De um paciente (id e nome); e
* O histórico desse paciente.

Visto que memória não necessariamente é escassa no hospital, nós optamos pelo encadeamento duplo por ser mais elegante e simples de implementar.

## Sobre o cliente.h

No arquivo `cliente.h` estão definidas as funções que o cliente usa diretamente através da nossa interface. A seguir, temos uma breve descrição de como a interface funciona

### MENU

O nosso sistema é feito de modo a usar a funções automaticamente: o cliente só precisa digitar digitar qual operação deseja fazer. É possível notar isso com detalhes no arquivo `/Cliente/main.c`.

```C
void menu(){
	puts("=-=-=-=-=-HOSPITAL-=-=-=-=-=\n\n");
	puts("Operações: \n");
	puts(" [1] Registrar Paciente\n");
	puts(" [2] Registrar Óbito de Paciente\n");
	puts(" [3] Adicionar Procedimento ao Histórico Médico\n");
	puts(" [4] Desfazer Procedimento ao Histórico Médico\n");
	puts(" [5] Chamar Paciente para Atendimento\n");
	puts(" [6] Mostrar Fila de Espera\n");
	puts(" [7] Mostrar Histórico do Paciente\n");
	puts(" [8] Sair\n");
	puts("Selecione uma: ");
}
```

### Carregando Dados
* `REGISTRO* carregar_registro();`

    * Antes de o *menu* ser carregado, o nosso sistema chama essa função para criar um registro e carregar os dados do arquivo `/TAD_Registro/registro.txt`.


* `FILA* carregar_fila();`

    * Também antes de o *menu* ser carregado, o nosso sistema chama essa função para criar uma fila e carregar os dados do arquivo `/TAD_FILA/fila.txt`.


### Gerenciando registros
*  `bool registrar_paciente(REGISTRO* r, FILA* f, char* paciente, int id);`
    * Essa função insere um paciente na fila de espera e o registra, caso ele não tenha registro. Nós tratamos IDs de paciente como os CPFs deles, então não pode haver IDs repetidos.

* `bool registrar_obito(REGISTRO* r, int id);`

    * Essa função remove o paciente do registro, incluindo o seu histórico de procedimentos.

### Gerenciando procedimentos
* `bool adicionar_procedimento(REGISTRO* r, int id, char* proced);`

    * Adiciona um procedimento na pilha de procedimentos do paciente.

* `bool desfazer_procedimento(REGISTRO* r, int id);`
    
    * Desfaz o procedimento do topo da pilha de procedimentos do paciente.

### Gerenciando a fila
*  `int chamar_paciente(FILA* f);`
    * Chama o primeiro paciente da fila.

* `void mostrar_fila(FILA* f);`
    * Mostra todos os pacientes da fila.
    
### Saindo do sistema
* `void sair(REGISTRO** r, FILA** f);`
    * Salva as informações relevantes em arquivo e encerra a execução o sistema.

# Funções cliente.c

Aqui, começa a parte 2 do README: falaremos de modo aprofundado sobre as funções do `cliente.h`

A nossa ideia foi fazer uma interface para o cliente com funções que usam os TADs *por baixo dos panos*. A seguir, vamos explicar o funcionamento dessas funções.

### Entrando no Sistema

Sempre que o cliente for usar o sistema, é necessário carregar os dados da memória. Para realizar isso, o nosso sistema executa as funções `REGISTRO* carregar_registro();` e `FILA* carregar_fila();` que retornam, respectivamente, um ponteiro de registro e fila.

Nesse processo, também é recuperado o **Histórico de Procedimentos** de cada paciente.

> **Essas funções carregam os dados salvos na memória.**
* O registro está salvo em `/TAD_Registro/registro.txt`;
* A fila está salva em `/TAD_Fila/fila.txt`;
* A histórico está salvo em `/TAD_Historico/proceds/`
    * O nome de cada histórico é um número: o ID do paciente.

<span style="color:orange; font-weight:bold">
Importante: cada TAD possui a sua própria função de carregamento de dados.
</span> Essas funções são acessadas por baixo dos panos, através das funções que o cliente usa diretamente.

### Registrando Paciente

Quando chega um novo paciente ao hospital, precisamos registrá-lo no sistema para que possamos gerenciar corretamente os seus dados. Com essa necessidade, desenvolvemos a função:
* `bool registrar_paciente(REGISTRO* r, FILA* f, char* paciente, int id)`. 

Sempre que um paciente novo é registrado, supomos que ele deseja entrar na fila de espera para ser devidamente atendido. A função retorna `true` se a inserção ocorreu com sucesso, e `false` caso contrário.

Inicialmente, é necessário verificar se já existe algum paciente com o ID passado como parâmetro, pois, se esse for o caso, o novo paciente não será adicionado, pois o id deve ser único. Para fazer essa verificação, usamos a função:
* `PACIENTE *registro_buscar_paciente(REGISTRO *r, int id)`, definida no TAD Registro;
* Ela retorna `NULL` caso não seja encontrado um paciente com aquele ID. 

Com isso garantido, alocamos memória para o paciente por meio da função:
* `PACIENTE *paciente_criar(char *nome, int id)` definida no TAD Paciente; e alocamos para o seu histórico com a função
*  `HISTOR *histor_criar()` definida no TAD Historico.

Após isso, podemos adicionar o paciente no registro por meio de outra função:
* `bool registro_inserir(REGISTRO *r, PACIENTE *p, HISTOR *r)`

Em caso de retorno `false` desta função, a inserção falhou e, então, desalocamos os itens criados chamando o `free()` para não ocorrer *memory leaks*. Já se o retorno é `true`, dizemos que o paciente foi registrado.

Como todo registro leva a uma inserção na fila, utilizamos também o método: 
* `bool fila_inserir(FILA *f, PACIENTE *paciente)`.
* Ele insere o paciente na fila. 

<span style="color:orange; font-weight:bold">
Importante: O espaço alocado para o paciente é independente para o registro e para a fila. Em outras palavras, um paciente do registro tem um endereço diferente do mesmo paciente na fila.
</span> 

São alocações independentes - alocamos "dois pacientes". O motivo disso é um melhor gerenciamento das desalocações posteriormente.

### Registrando Óbito

Quando o cliente precisar (infelizmente) registrar um óbito, ele chamará a função `bool registrar_obito(REGISTRO* r, int id)`. A nossa missão, então, é proteger os dados do falecido: *vamos removê-lo do registro* do hospital.

Para atingir isso, a função `bool registro_apagar(REGISTRO *r, int id)` é chamada. Essa função desalocará o nó do registro correspondente ao paciente que faleceu. Além isso, serão, ainda, chamadas as funções:
*  `bool paciente_apagar(PACIENTE **p)`, que desaloca o nome do paciente e a sua struct;
* `void histor_apagar(HISTOR **h)`, que desaloca a struct do histórico do paciente e tem auxílio da função `bool proced_apagar(PROCED  **proced)`, que desaloca cada procedimento individualmente.

Como estamos considerando que nenhum paciente morre enquanto está na fila, não precisamos nos preocupar em alterar a fila, no caso de um óbito.

### Adicionando Procedimento

Caso seja necessário que o paciente passe por um novo procedimento, é importante adicionar esse procedimento em seu histórico. Para isso, há a função `bool adicionar_procedimento(REGISTRO *r, int id, char *proced)` no cliente.h. Retorna-se `true`, se a adição ocorreu de maneira correta; `false`, senão.

Inicialmente, chama-se a função `HISTOR *registro_buscar_histor(REGISTRO *r, int id)` para receber um ponteiro para o histórico do paciente que irá receber o novo procedimento. Com o ponteiro em mãos, podemos executar `bool histor_inserir(HISTOR *h, PROCED *p)`, adicionando o procedimento, de fato, na pilha de históricos. Claro que antes de inserir, alocamos memória para o procedimento através do método `PROCED *proced_criar(char *proced)` do TAD Procedimento.

Se houver erro ao inserir, desalocamos o proocedimento a fim de não haver memory leak.

<span style = "color: orange; font-weight: bold;"> Importante: essa função pode falhar e retornar false pela falta de espaço no histórico, uma vez que esse tem um tamanho máximo fixo de 10 procedimentos.</span>

### Desfazendo Procedimento

Quando um procedimento foi inserido equivocadamente ou não será mais necessário, torna-se preciso tirá-lo do histórico do paciente. Para tal, o cliente deverá utilizar da função `bool desfazer_procedimento(REGISTRO* r, int id)`. 

Essa função chama, internamente, o método `HISTOR *registro_buscar_histor(REGSITRO *r, int id)` para que tenhamos um ponteiro para o histórico do paciente e possamos manipulá-lo.

Logo, é retirado o último procedimento adicionado, conforme a política LIFO de uma pilha, utilizando a função `PROCED *histor_remover(HISTOR *h)`. Contudo, só com essa chamada não desalocamos o procedimento e, por isso, chamamos ainda `bool proced_apagar(PROCED **proced)`. 

Por fim, retorna-se `true`, se ocorreu corretamente, `false`, senão, como no caso de não ter procedimentos no histórico do paciente.

### Chamando Paciente

Toda vez que uma nova sala de atendimento for liberada, o paciente na frente da fila poderá ser atendido. Para ser possível atualizar a fila para seu novo estado, é necessário chamar a função `int chamar_paciente(FILA* f)`. Ela retorna o ID do paciente removido ao invés de seu nó, já que o cliente não tem acesso a funções que possam interagir com nós.

Para evitar erros caso o cliente tente remover um paciente da fila quando ela estiver vazia, esta função imediatamente chama a função `bool fila_vazia(FILA* fila)`, retornando '-1' (Um ID inválido) caso verdadeiro e imprimindo um aviso na tela.

Caso a fila não esteja vazia, a função `PACIENTE* fila_remover(FILA* fila)` é chamada para atualizar a fila, e então o paciente removido é desalocado, pois não estará mais na fila.

### Mostrando Fila

Caso seja necessário verificar quais pacientes estão na fila em um dado instante, o cliente pode usar a função `void mostrar_fila(FILA* f)`.

Há 3 tipos de mensagem que esta função possa exibir ao cliente. Caso a fila passada como entrada não exista, a mensagem `"Esta fila não existe!"` será mostrada. Caso a fila existir mas estiver vazia, o cliente receberá `"A fila está vazia!"`. Por último, se a fila existir e houver pelo menos 1 paciente nela, a função irá imprimir na tela todos os pacientes dentro dela um a um, iniciando pelo paciente na frente da fila e encerrando com o último.

O método para obter todos os pacientes envolve usar a função `PACIENTE* fila_frente(FILA* fila)` para receber o paciente na frente da fila sem o remover, e então usando as funções `int paciente_get_id(PACIENTE* p)` e `char* paciente_get_nome(PACIENTE* p)` para obter seu ID e nome, respectivamente. Após isso, `bool fila_inserir(FILA* fila, PACIENTE* paciente)` e `PACIENTE* fila_remover(FILA* fila)` são chamadas para remover um paciente da fila e imediatamente o re-inserindo, mantendo a ordem da fila e obtendo acesso ao próximo paciente.

Este processo é então repetido desde a função `PACIENTE* fila_frente(FILA* fila)` para cada outro paciente, retornando a fila a seu estado inicial e exibindo todos os pacientes no meio do caminho.

### Mostrando Histórico

A função `void mostrar_historico(REGISTRO* r, int id);` usa duas funções:
* `HISTOR *h = registro_buscar_histor(r, id);`, para obter o histórico do paciente;*
* `PACIENTE *p = registro_buscar_paciente(r, id);`, para obter o nome do paciente.

Essas funções usam, por baixo dos panos, a função `int paciente_get_id(PACIENTE *p);`.
### Saindo do Sistema

Quando o cliente for encerrar o sistema, ele chamará a função `void sair(REGISTRO** r, FILA** f)`, que é responsável por:
* Salvar a fila em arquivo e desalocá-la:
    * Através da função `bool fila_salvar(FILA **f)`, que desaloca a struct fila e os pacientes.

* Salvar os pacientes do registro e desalocá-los:
    * Atráves da função `bool registro_salvar(REGISTRO **r)`, que salva os pacientes e desaloca o registro, além de chamar duas funções:
    *  A primeira é a `void histor_salvar(HISTOR **h, PACIENTE **p)`, que salva o histórico; e
    * A segunda é a `bool registro_apagar(REGISTRO *r, int id)`, que desaloca os pacientes e os seus nós correspondentes no registro.

<span style = "color: ORANGE; font-weight: bold">
Importante: para isso funcionar, a fila e o registro possuem nós independentes, isto é, um mesmo paciente é representado por nós distintos: um para a fila e um para o registro.
</span>

