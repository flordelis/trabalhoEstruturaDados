#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

 struct lista {
    Cliente *cliente;
    struct lista *prox;
};

int inserirLista (Lista **inicio, Cliente **cliente) {
    Lista *novo; 
    Lista *aux;
    Lista *ant;
    Lista *busca = *inicio;
    novo= malloc(sizeof(Lista));
    novo->cliente = *cliente;
    if(*inicio == NULL) {
        novo->prox = *inicio;
        *inicio = novo;
    } else {
       while  (busca !=NULL) {
          if (busca->cliente->matricula > novo->cliente->matricula) {
             break;
          }
          ant = busca;
          busca = busca->prox;
       }
       aux = ant->prox;
       ant->prox = novo;
       novo->prox = aux;
    }
    free(aux);
}

int removerLista (Lista **inicio, int matricula) {
    Lista * anterior; 
    Lista * atual; 
    anterior = NULL;
    atual=*inicio;
    while (atual != NULL) {
          if (atual->cliente->matricula == matricula) {
             if (anterior == NULL) {
                *inicio = atual->prox;          
                }
             else {
                  anterior->prox = atual->prox;
                  }
             free(atual);
             break;
             }
          anterior=atual;
          atual=atual->prox;
    }
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