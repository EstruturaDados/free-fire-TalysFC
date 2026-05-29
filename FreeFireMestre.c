#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//structs
struct componente{
    char nome[30];
    char tipo[20];
    int prioridade;
};

struct componente* mochila;

// Variáveis globais
int capacidade = 20;
int totalComponentes = 0;
int statusOrdenacaoPorNome = 0;
int opcao;
int opcaoOrdem;
char opcaoTexto[30];

// Protótipo das funções básicas
void mostrarMenu();
void mostrarMenuOrdenar();

//Protótipo das funções da mochila
void iniciarMochila();
void adicionarComponente();
void removerComponente();
void mostrarComponentes();


// Protótipo das funções para ordenação
void selectionSortPrioridade(struct componente[], int capacidade);
void insertionSortTipo(struct componente[], int capacidade);
void bubbleSortNome(struct componente[], int capacidade);


// Protótipo das funções extras
void buscaBinariaPorNome(struct componente[], int capacidade, char nome[]);
void medirTempo();

// Código principal
int main(){
    iniciarMochila();
    do{
        mostrarMenu();
        switch(opcao){
            case 1:
            adicionarComponente();
            break;
            case 2:
            removerComponente();
            break;
            case 3:
            mostrarComponentes();
            break;
            case 4:
            mostrarMenuOrdenar();
            switch(opcaoOrdem){
                case 1:
                bubbleSortNome(mochila, totalComponentes);
                mostrarComponentes();
                break;
                case 2:
                insertionSortTipo(mochila, totalComponentes);
                mostrarComponentes();
                break;
                case 3:
                selectionSortPrioridade(mochila, totalComponentes);
                mostrarComponentes();
                break;
                case 4:
                printf("Voltando... \n");
                break;
                default:
                printf("Opção inválida. \n");
            }
            break;
            case 5:
            if(statusOrdenacaoPorNome == 0){
                printf("A busca binária só pode ser utilizada após os componentes estarem ordenados pelo nome. \n");
            } else{
                printf("Digite o nome do componente-chave: \n");
                scanf("%s", opcaoTexto);
                buscaBinariaPorNome(mochila, totalComponentes, opcaoTexto);
            }
            break;
            case 6:
            printf("Saindo do jogo... \n");
            break;
            default:
            printf("Opção inválida. \n");
        }
    } while (opcao != 6);
    free(mochila);
    return 0;
}

//Implementação das funções
// Função responsável por mostrar o menu principal
void mostrarMenu(){
    printf("\n-- Bem-vindo ao jogo! --\n");
    printf("1- Inserir componente \n");
    printf("2- Remover componente \n");
    printf("3- Mostrar componente \n");
    printf("4- Ordenar componentes \n");
    printf("5- Busca binária por Componente-Chave (por nome) \n");
    printf("6- Sair do jogo \n");
    printf("Escolha uma opção: \n");
    scanf("%d", &opcao);
}

// Função responsável por mostrar o menu de ordenação
void mostrarMenuOrdenar(){
    printf("Como deseja ordenar sua mochila? \n");
    printf("1- Ordenar por nome \n");
    printf("2- Ordenar por tipo \n");
    printf("3- Ordenar por prioridade \n");
    printf("4- Voltar... \n");
    scanf("%d", &opcaoOrdem);
}

// Função responsável por alocar memória para o vetor
void iniciarMochila(){
    mochila = malloc(capacidade * sizeof(struct componente));
    if(mochila == NULL){
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
}

// Função responsável por adicionar componentes
void adicionarComponente(){
    if(totalComponentes == capacidade){
        printf("Não é possível adicionar mais componentes. Mochila cheia!\n");
        return;
    }
    printf("Nome do componente: ");
    scanf("%s", mochila[totalComponentes].nome);
    printf("Tipo do componente (estrutura, eletronico, energia, controle): ");
    scanf("%s", mochila[totalComponentes].tipo);
    printf("Prioridade do componente (1 a 10): ");
    scanf("%d", &mochila[totalComponentes].prioridade);
    totalComponentes++;
    mostrarComponentes();
}

// Função responsável por remover um componente pelo nome
void removerComponente(){
    printf("Digite o nome do componente que deseja remover: ");
    scanf("%s", opcaoTexto);
    for(int i = 0; i < totalComponentes; i++){
        // Busca sequencial pelo nome do item
        if(strcmp(mochila[i].nome, opcaoTexto) == 0){
            // Move os itens para preencher o espaço vazio
            for(int j = i; j < totalComponentes - 1; j++){
                mochila[j] = mochila[j + 1];
            }
            totalComponentes--;
            mostrarComponentes();
            return;
        }
    }
    printf("Componente não encontrado.\n");
}

// Função responsável por mostrar todos os componentes
void mostrarComponentes(){
    printf("\n-- Componentes da Mochila --\n");
    for(int i = 0; i < totalComponentes; i++){
        printf("\nComponente %d\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Prioridade: %d\n", mochila[i].prioridade);
    }
    printf("\n");
}

// Função Selection Sort para ordenar por prioridade
void selectionSortPrioridade(struct componente vetor[], int capacidade){
    int comparacoes = 0;
    clock_t inicio = clock();
    for(int i = 0; i < capacidade - 1; i++){
        int indiceMenor = i;
        for(int j = i + 1; j < capacidade; j++){
            comparacoes++;
            if(vetor[j].prioridade < vetor[indiceMenor].prioridade){
                indiceMenor = j;
            }
        }
        if(indiceMenor != i){
            struct componente temp = vetor[i];
            vetor[i] = vetor[indiceMenor];
            vetor[indiceMenor] = temp;
        }
    }
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nSelection Sort finalizado.\n");
    printf("Comparações: %d\n", comparacoes);
    printf("Tempo: %f segundos\n", tempo);
    statusOrdenacaoPorNome = 0;
}

// Função Insertion Sort para ordenar por tipo
void insertionSortTipo(struct componente vetor[], int capacidade){
    int comparacoes = 0;
    clock_t inicio = clock();
    for(int i = 1; i < capacidade; i++){
        struct componente chave = vetor[i];
        int j = i - 1;
        while(j >= 0){
            comparacoes++;
            if(strcmp(vetor[j].tipo, chave.tipo) > 0){
                vetor[j + 1] = vetor[j];
                j--;
            }
            else{
                break;
            }
        }
        vetor[j + 1] = chave;
    }
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nInsertion Sort finalizado.\n");
    printf("Comparações: %d\n", comparacoes);
    printf("Tempo: %f segundos\n", tempo);
    statusOrdenacaoPorNome = 0;
}

// Função Bubble Sort para ordenar por nome
void bubbleSortNome(struct componente vetor[], int capacidade){
    int comparacoes = 0;
    clock_t inicio = clock();
    for(int i = 0; i < capacidade - 1; i++){
        for(int j = 0; j < capacidade - 1 - i; j++){
            comparacoes++;
            if(strcmp(vetor[j].nome, vetor[j + 1].nome) > 0){
                struct componente temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nBubble Sort finalizado.\n");
    printf("Comparações: %d\n", comparacoes);
    printf("Tempo: %f segundos\n", tempo);
    statusOrdenacaoPorNome = 1;
}

// Função de busca binária por nome
void buscaBinariaPorNome(struct componente vetor[], int capacidade, char nome[]){
    int inicio = 0;
    int fim = capacidade - 1;
    int comparacoes = 0;
    while(inicio <= fim){
        comparacoes++;
        int meio = (inicio + fim) / 2;
        int resultado = strcmp(vetor[meio].nome, nome);
        if(resultado == 0){
            printf("\nComponente-chave encontrado!\n");
            printf("Nome: %s\n", vetor[meio].nome);
            printf("Tipo: %s\n", vetor[meio].tipo);
            printf("Prioridade: %d\n", vetor[meio].prioridade);
            printf("Comparações: %d\n", comparacoes);
            return;
        }
        else if(resultado < 0){
            inicio = meio + 1;
        }
        else{
            fim = meio - 1;
        }
    }
    printf("Componente não encontrado.\n");
    printf("Comparações: %d\n", comparacoes);
}