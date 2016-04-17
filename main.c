#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "arvore.h"
#include "cliente.h"
#include "lista.h"
#if defined(_WIN64) ||  defined(_WIN32)
#include <conio.h>
#endif
#define TIPOARVORE  1
#define TIPOLISTA 2
#define INORDEM 1
#define PREORDEM 2
#define POSORDEM 3

Cliente*  cadastrarCliente(void);
int menu(void);
void remover(Arvore **raiz, Lista **inicio, int tipo);
void inserir(Arvore **raiz, Lista **inicio,int tipo);
void buscar(Arvore *raiz, Lista *inicio, int tipo);
void exibir(Arvore *raiz,int tipoExibicao);
void clrscr(void);
int pedirMatricula(void);
void pausarExibicao();

int main(int argc, char **argv) {

    setlocale(LC_ALL, "PT_BR.UTF-8");

    int opcao, altura;
    float mediaIdade = 0.0;
    Arvore *raiz = NULL;
    Lista *inicio = NULL;

    do {
        clrscr();
        opcao = menu();
        switch (opcao) {
            case 0:
                break;
            case 1:
                inserir(&raiz, &inicio, TIPOARVORE);
                break;
            case 2:
                remover(&raiz, &inicio, TIPOARVORE);
                break;           
            case 3:
                buscar(raiz, inicio,  TIPOARVORE);
                break;
            case 4:
                mediaIdade = calcularMediaIdade(raiz);
		printf("\nA media da turma eh %.2f\n",mediaIdade);
                break;
             case 5:
                exibir(raiz, INORDEM);
                break;
             case 6:
                exibir(raiz, PREORDEM);
                break;
             case 7:
                exibir(raiz, POSORDEM);
                break;
             case 8:
                altura = calcularAlturaArvore(raiz);
                printf("A Altura da Arvore eh %d\n", altura);
                break; 
             case 9:
                inserir(&raiz, &inicio,  TIPOLISTA);
                break;
            case 10:
                remover(&raiz, &inicio,  TIPOLISTA);
                break;           
            case 11:
                buscar(raiz, inicio,  TIPOLISTA);
                break;
            default:
            {
                printf("Opcao Invalida\n");
                break;
            }
        }
        pausarExibicao();
    } while (opcao != 0);
    free(inicio);
    free(raiz);
    return 0;
}

void pausarExibicao(){
 printf("\nPressione qualquer tecla para continuar");
 getchar();
 getchar();
}

Cliente* cadastrarCliente() {
    printf("\nCadastro Cliente");
    printf("\n----------------------\n");
    printf("\nInforme a(o):\n");
    Cliente *cliente = malloc(sizeof (Cliente));
    printf("\nMatricula: ");
    scanf("%d", &(*cliente).matricula);
    printf("Nome: ");
    scanf(" %80[a-z A-Z]s", &(*cliente).nome);
    printf("Endereco: ");
    scanf(" %80[^\n]s", &(*cliente).endereco);
    printf("Telefone: ");
    scanf(" %80[0-9 ]s", &(*cliente).telefone);
    printf("E-mail: ");
    scanf(" %80[^\n]s", &(*cliente).email);
    Data *data = malloc(sizeof (Data));
    int dia, mes, ano;
    printf("Data de nascimento: ");
    printf("\nDia:");
    scanf("%d", &dia);
    printf("Mes:");
    scanf("%d", &mes);
    printf("Ano:");
    scanf("%d", &ano);
    data->ano = ano;
    data->mes = mes;
    data->dia = dia;
    (*cliente).dataNascimento = *data;
    return cliente;
}

int menu() {
    int op;
    printf("*** Cadastro de Clientes [Árvore AVL] ***\n");
    printf("1) Inserir Cliente\n");
    printf("2) Remover Cliente\n");
    printf("3) Buscar Cliente\n");
    printf("4) Percorrer a árvore e calcular a média de idade dos clientes.\n");
    printf("5) Imprimir árvore In-Ordem\n");
    printf("6) Imprimir árvore Pre-Ordem\n");
    printf("7) Imprimir árvore Pos-Ordem\n");
    printf("8) Calcular altura da árvore\n");
    printf("\n*** Cadastro de Clientes [Lista Encandeada] ***\n");
    printf("9) Inserir Cliente\n");
    printf("10) Remover Cliente\n");
    printf("11) Buscar Cliente\n\n");
    printf("0) Sair\n\n");
    printf("Selecione uma opção: ");
    scanf("%d", &op);

    return op;
}

void exibir(Arvore *raiz, int tipoExibicao){
    if(raiz == NULL) {
        printf("A arvore está vazia");
        return;
    }
    switch (tipoExibicao) {
        case INORDEM:
            exibirEmOrdem(raiz);break;
        case POSORDEM:
            exibirPosOrdem(raiz);break;
        default:
            exibirPreOrdem(raiz); 
    }
}

void remover(Arvore **raiz, Lista **inicio, int tipo){
    int matricula = pedirMatricula();
    int sucesso = 0;
    switch (tipo) {
      case TIPOARVORE:
            sucesso = removerArvore(raiz, matricula);
      break;
      case TIPOLISTA: 
           sucesso = removerLista(inicio, matricula);
      break;
    }
    if(sucesso == 1){
        printf("Cadastro removido com sucesso");
    } else {
        printf("Cliente não encontrado");
    }
}

void inserir(Arvore **raiz, Lista **inicio, int tipo) {
    Cliente *cliente = cadastrarCliente();
    switch (tipo) {
      case TIPOARVORE:
            inserirArvore(raiz, &cliente);
      break;
      case TIPOLISTA: 
            inserirLista(inicio, &cliente);
      break;
    }
    printf("Cliente inserido com sucesso");
}

void buscar(Arvore *raiz, Lista *inicio, int tipo){
    int matricula = pedirMatricula();
    Cliente *cliente = NULL;
    switch (tipo) {
      case TIPOARVORE:
          cliente = buscarArvore(raiz, matricula);          
      break;
      case TIPOLISTA: 
          cliente = buscarLista(inicio, matricula); 
      break;
    }
    if(cliente == NULL) {
        printf("Cliente não encontrado!");
    } else {
        imprimirCliente(*cliente);
    }
}

int pedirMatricula() {
    int matricula;
    printf("Informe a matricula para remover o cadastro do cliente:") ;
    printf("\nMatricula: ");
    scanf("%d", &matricula);
    return matricula;
}


void clrscr() {
#if defined(__linux__)
    system("clear");
#elif defined(_WIN64) ||  defined(_WIN32)
    system("cls");
#elif defined(__APPLE__) || defined(__MACH__)
    system("clear");
#endif
}