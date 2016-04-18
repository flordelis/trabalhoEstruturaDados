#include "lista.h" #include <stdio.h> #include <stdlib.h>

 struct lista {
    Cliente *cliente;
    struct lista *prox;
};

void inserirLista (Lista **inicio, Cliente **cliente) {
    Lista *novo; 
    Lista *ant = NULL;
    Lista *busca = *inicio;
    novo = malloc(sizeof(Lista));
    if(!novo) {
	  printf("Não foi possivel realizar a operaçao");
	}
    novo->cliente = *cliente;
    novo->prox = NULL;
    while  (busca !=NULL  && (busca->cliente->matricula < novo->cliente->matricula)) {
          	ant = busca;
          	busca = busca->prox;
    }
    if(ant == NULL) {
	    novo->prox = *inicio;
        *inicio = novo;
	} else {
       novo->prox = ant->prox;
       ant->prox = novo;       
	}
}

int removerLista (Lista **inicio, int matricula) {
    Lista * anterior; 
    Lista * atual =  *inicio;
    anterior = NULL;
    
    while (atual != NULL) {
          if (atual->cliente->matricula == matricula) {
             if (anterior == NULL) {
                *inicio = atual->prox;          
                }
             else {
                  anterior->prox = atual->prox;
                  }
             free(atual);
             return 1;
             break;
             }
          anterior=atual;
          atual=atual->prox;
    }
    return 0;
}

Cliente* buscarLista (Lista *inicio, int matricula) {
    Lista * busca;    
    busca=inicio;
    while (busca != NULL) {
          if (busca->cliente->matricula == matricula) {
              return busca->cliente;
             }
          busca=busca->prox;
          }
    return NULL;
}
