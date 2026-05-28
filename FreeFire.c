//Código nivel aventureiro

// Bibliotecas 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct que representa um item da mochila
struct item{
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Vetor dinâmico da mochila
struct item* mochila;

// Struct do nó da lista encadeada 
struct No{
    struct item dados;
    struct No* proximo;
};

// Ponteiro para o início da lista encadeada
struct No* inicio = NULL;

// Variáveis globais do sistema
int totalItens = 0;
int capacidade = 10;
int opcaoTipoMenu;
int opcaoMenu;
char opcao[30];

// Contadores de comparações das buscas
int comparacaoSequencial = 0;
int comparacaoBinaria = 0;

// Protótipos das funções principais
void iniciarMochila();
void escolhaMenu();
void mostrarMenuVetor();
void mostrarMenuLista();

// Funções do vetor
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void buscarItemVetor();
void ordenarVetor();
void buscaBinariaVetor();

// Funções da lista encadeada
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarItemLista();

int main(){
    iniciarMochila();
    do{
        // Escolha entre vetor ou lista
        escolhaMenu();
        switch(opcaoTipoMenu){
            // Menu do vetor
            case 1:
            mostrarMenuVetor();
            switch(opcaoMenu){
                case 1:
                    inserirItemVetor();
                    break;
                case 2:
                    removerItemVetor();
                    break;
                case 3:
                    listarItensVetor();
                    break;
                case 4:
                    buscarItemVetor();
                    break;
                case 5:
                    ordenarVetor();
                    break;
                case 6: 
                    buscaBinariaVetor();
                    break;
                case 7:
                    printf("Saindo do jogo...\n");
                    break;
                default:
                    printf("Opção inválida.\n");
            }
            break;
            // Menu da lista encadeada
            case 2:
            mostrarMenuLista();
            switch(opcaoMenu){
                case 1:
                    inserirItemLista();
                    break;
                case 2:
                    removerItemLista();
                    break;
                case 3:
                    listarItensLista();
                    break;
                case 4:
                    buscarItemLista();
                    break;
                case 5:
                    printf("Voltando...\n");
                    break;
                default:
                    printf("Opção inválida.\n");
            }
            break;
            // Encerrar programa
            case 3:
            printf("Saindo do jogo...\n");
            break;
            default:
            printf("Opção inválida.");
        }
    } while(opcaoTipoMenu != 3);
    // Libera memória do vetor
    free(mochila);
    // Libera memória da lista encadeada
    struct No* atual = inicio;
    while(atual != NULL){
        struct No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    return 0;
}

// Função responsável por iniciar a mochila
void iniciarMochila(){
    mochila = malloc(capacidade * sizeof(struct item));
    if(mochila == NULL){
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
}

// Função responsável por escolher entre os menus
void escolhaMenu(){
    printf("\n-- Bem-vindo ao jogo! --\n");
    printf("Você deseja usar o menu de Vetores ou o menu de Listas? \n");
    printf("1- Vetor \n");
    printf("2- Lista \n");
    printf("3- Sair do jogo \n");
    printf("Escolha uma opção: \n");
    scanf("%d", &opcaoTipoMenu);
}

// Função responsável por mostrar o menu vetor
void mostrarMenuVetor(){
    printf("\n-- Bem-vindo ao jogo (vetores)! --\n");
    printf("1 - Inserir item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Buscar item\n");
    printf("5 - Ordenar itens\n");
    printf("6 - Busca binária\n");
    printf("7 - Voltar\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcaoMenu);
}

// Função responsável por mostrar o menu lista
void mostrarMenuLista(){
    printf("\n-- Bem-vindo ao jogo (listas)! --\n");
    printf("1 - Inserir item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Buscar item\n");
    printf("5 - Voltar\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcaoMenu);
}

// Função responsável por inserir itens
void inserirItemVetor(){
    if(totalItens == capacidade){
        printf("Não é possível adicionar mais itens. Mochila cheia!\n");
        return;
    }
    printf("Nome do item: ");
    scanf("%s", mochila[totalItens].nome);
    printf("Tipo do item: ");
    scanf("%s", mochila[totalItens].tipo);
    printf("Quantidade do item: ");
    scanf("%d", &mochila[totalItens].quantidade);
    totalItens++;
    listarItensVetor();
}

// Função responsável por remover itens pelo nome
void removerItemVetor(){
    printf("Digite o nome do item que deseja remover: ");
    scanf("%s", opcao);
    for(int i = 0; i < totalItens; i++){
        // Busca sequencial pelo nome do item
        if(strcmp(mochila[i].nome, opcao) == 0){
            // Move os itens para preencher o espaço vazio
            for(int j = i; j < totalItens - 1; j++){
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            listarItensVetor();
            return;
        }
    }
    printf("Item não encontrado.\n");
}

// Função responsável por listar todos os itens
void listarItensVetor(){

    printf("\n-- ITENS DA MOCHILA --\n");
    for(int i = 0; i < totalItens; i++){
        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
    printf("\n");
}

// Função responsável por buscar um item pelo nome
void buscarItemVetor(){
    comparacaoSequencial = 0;
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%s", opcao);
    for(int i = 0; i < totalItens; i++){
        comparacaoSequencial++;
        // Busca sequencial
        if(strcmp(mochila[i].nome, opcao) == 0){
            printf("\nNome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }
    printf("Item não encontrado.\n");
    printf("Comparações: %d\n", comparacaoSequencial);
}

// Função responsável por ordenar itens com bubble sort
void ordenarVetor(){
    struct item temp;
    for(int i = 0; i < totalItens - 1; i++){
        for(int j = 0; j < totalItens - i - 1; j++){
            if(strcmp(mochila[j].nome, mochila[j + 1].nome) > 0){
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados com sucesso!\n");
}

// Função para realizar procurar itens com busca binária
void buscaBinariaVetor(){
    printf("Digite o nome do item: ");
    scanf("%s", opcao);
    ordenarVetor();
    int inicioBusca = 0;
    int fim = totalItens - 1;
    comparacaoBinaria = 0;
    while(inicioBusca <= fim){
        comparacaoBinaria++;
        int meio = (inicioBusca + fim) / 2;
        int resultado = strcmp(mochila[meio].nome, opcao);
        if(resultado == 0){
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Comparações: %d\n", comparacaoBinaria);
            return;
        }
        else if(resultado < 0){
            inicioBusca = meio + 1;
        }
        else{
            fim = meio - 1;
        }
    }
    printf("Item não encontrado.\n");
    printf("Comparações: %d\n", comparacaoBinaria);
}

// Função responsável por inserir itens
void inserirItemLista(){
    struct No* novo = malloc(sizeof(struct No));
    if(novo == NULL){
        printf("Erro de memória.\n");
        return;
    }
    printf("Nome do item: ");
    scanf("%s", novo->dados.nome);
    printf("Tipo do item: ");
    scanf("%s", novo->dados.tipo);
    printf("Quantidade do item: ");
    scanf("%d", &novo->dados.quantidade);
    novo->proximo = NULL;
    
    if(inicio == NULL){
        inicio = novo;
    }
    else{
        struct No* atual = inicio;
        // anda até o último nó
        while(atual->proximo != NULL){
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
    listarItensLista();
}

// Função responsável por remover itens
void removerItemLista(){
    printf("Digite o nome do item que deseja remover: ");
    scanf("%s", opcao);
    struct No* atual = inicio;
    struct No* anterior = NULL;
    while(atual != NULL){
        // Busca sequencial
        if(strcmp(atual->dados.nome, opcao) == 0){
            // Se for o primeiro nó
            if(anterior == NULL){
                inicio = atual->proximo;
            }
            else{
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item removido!\n");
            listarItensLista();
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item não encontrado.\n");
}

// Função responsável por listar itens
void listarItensLista(){
    struct No* atual = inicio;
    printf("\n-- Itens da Lista --\n");
    int contador = 1;
    while(atual != NULL){
        printf("\nItem %d\n", contador);
        printf("Nome: %s\n", atual->dados.nome);
        printf("Tipo: %s\n", atual->dados.tipo);
        printf("Quantidade: %d\n", atual->dados.quantidade);
        atual = atual->proximo;
        contador++;
    }
    printf("\n");
}

// Função responsável por buscar itens
void buscarItemLista(){
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%s", opcao);
    comparacaoSequencial = 0;
    struct No* atual = inicio;
    while(atual != NULL){
        comparacaoSequencial++;
        if(strcmp(atual->dados.nome, opcao) == 0){
            printf("\nNome: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            printf("Comparações: %d\n", comparacaoSequencial);
            return;
        }
        atual = atual->proximo;
    }
    printf("Item não encontrado.\n");
    printf("Comparações: %d\n", comparacaoSequencial);
}