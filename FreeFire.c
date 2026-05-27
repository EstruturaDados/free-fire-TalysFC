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

int totalItens = 0;
int capacidade = 10;
int opcaoMenu;
char opcao[30];

void iniciarMochila();
void mostrarMenu();
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

int main(){
    iniciarMochila();
    do{
        mostrarMenu();
        switch(opcaoMenu){
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while(opcaoMenu != 5);

    free(mochila);

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

// Função responsável por inserir itens
void inserirItem(){
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
    listarItens();
}

// Função responsável por remover itens pelo nome
void removerItem(){
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
            listarItens();
            return;
        }
    }
    printf("Item não encontrado.\n");
}

// Função responsável por listar todos os itens
void listarItens(){

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
void buscarItem(){
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%s", opcao);
    for(int i = 0; i < totalItens; i++){
        // Busca sequencial
        if(strcmp(mochila[i].nome, opcao) == 0){
            printf("\nNome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }
    printf("Item não encontrado.\n");
}

// Função responsável por mostrar o menu
void mostrarMenu(){
    printf("\n-- Bem-vindo ao jogo! --\n");
    printf("1 - Inserir item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Buscar item\n");
    printf("5 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcaoMenu);
}