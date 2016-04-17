#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "arvore.h"

struct arvore{
	Cliente *cliente;	
	struct arvore *esq;
	struct arvore *dir;
	int balanceamento;
};

void criarArvore(Arvore **pRaiz){
    *pRaiz = NULL;
}

Arvore* criarNo() {
    Arvore *aux = malloc(sizeof (Arvore));
    aux->balanceamento = 0;
    aux->esq = NULL;
    aux->dir = NULL;
    aux->cliente = NULL;
		
    return aux;
}


Cliente* buscarArvore(Arvore *pRaiz, int matricula){	
	if(pRaiz == NULL)
		return NULL;	
	if(matricula ==  pRaiz ->  cliente -> matricula)
		return  pRaiz -> cliente;
	if(matricula >  pRaiz -> cliente -> matricula)
		return(buscarArvore(pRaiz -> dir, matricula));
	else
		return(buscarArvore(pRaiz -> esq, matricula));
}


void exibirEmOrdem(Arvore *pRaiz){
    if(pRaiz != NULL){
        exibirEmOrdem(pRaiz->esq);
        imprimirCliente(*pRaiz->cliente);
        exibirEmOrdem(pRaiz->dir);
    }
}

void exibirPreOrdem(Arvore *pRaiz){
    if(pRaiz != NULL){
        imprimirCliente(*pRaiz->cliente);
        exibirPreOrdem(pRaiz->esq);
        exibirPreOrdem(pRaiz->dir);
    }
}

void exibirPosOrdem(Arvore *pRaiz){
    if(pRaiz != NULL){
        exibirPosOrdem(pRaiz->esq);
        exibirPosOrdem(pRaiz->dir);
      	imprimirCliente(*pRaiz->cliente);
    }
}

int contarNos(Arvore *pRaiz){
   if(pRaiz == NULL)
        return 0;
   else
        return 1 + contarNos(pRaiz->esq) + contarNos(pRaiz->dir);
}

float somarIdadeClientes(Arvore *pRaiz) {
	 if (pRaiz == NULL)
        return 0;
    else {
        int somaEsq = somarIdadeClientes(pRaiz->esq);
        int somaDir = somarIdadeClientes(pRaiz->dir);

        return calcularIdadeCliente(pRaiz->cliente->dataNascimento) + somaEsq + somaDir;
    }
}

float calcularMediaIdade(Arvore *pRaiz) {
    if(pRaiz!=NULL){
	return  somarIdadeClientes(pRaiz) / contarNos(pRaiz);
}
    return 0;
}

int contarFolhas(Arvore *pRaiz){
   if(pRaiz == NULL)
        return 0;
   if(pRaiz->esq == NULL && pRaiz->dir == NULL)
        return 1;
   return contarFolhas(pRaiz->esq) + contarFolhas(pRaiz->dir);
}

int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

int calcularAlturaArvore(Arvore *pRaiz){
   if((pRaiz == NULL))
       return -1;
   else
       return 1 + maior(calcularAlturaArvore(pRaiz->esq), calcularAlturaArvore(pRaiz->dir));
}

int calcularBalanceamento(Arvore *pRaiz) {
    if (pRaiz == NULL) {
        return 0;
    } else {
        int altLeft = calcularAlturaArvore(pRaiz->esq);
        int altRight = calcularAlturaArvore(pRaiz->dir);
        (*pRaiz).balanceamento = altLeft - altRight;
        return (*pRaiz).balanceamento;
    }
}


Arvore* rotacaoEsq(Arvore **no) {
    Arvore *noRotac = (*no)->dir;
    if (noRotac->esq) {
        (*no)->dir = noRotac->esq;
    } else {
        (*no)->dir = NULL;
    }
    noRotac->esq = *no;

    return noRotac;
}

Arvore* rotacaoDir(Arvore **no) {
    Arvore *noRotac = (*no)->esq;
    if (noRotac->dir) {
        (*no)->esq = noRotac->dir;
    } else {
        (*no)->esq = NULL;
    }
    noRotac->dir = *no;

    return noRotac;
}

Arvore* rotacaoDuplaEsq(Arvore **no) {
    Arvore *noRotac1 = (*no)->dir;
    Arvore *noRotac2 = noRotac1->esq;

    if (noRotac2->esq) {
        (*no)->dir = noRotac2->esq;
    } else {
        (*no)->dir = NULL;
    }
    if (noRotac2->dir) {
        noRotac1->esq = noRotac2->dir;
    } else {
        noRotac1->esq = NULL;
    }
    noRotac2->esq = (*no);
    noRotac2->dir = noRotac1;

    return noRotac2;
}

Arvore* rotacaoDuplaDir(Arvore **no) {
    Arvore *noRotac1 = (*no)->esq;
    Arvore *noRotac2 = noRotac1->dir;

    if (noRotac2->esq) {
        noRotac1->dir = noRotac2->esq;
    } else {
        noRotac1->dir = NULL;
    }

    if (noRotac2->dir) {
        (*no)->esq = noRotac2->dir;
    } else {
        (*no)->esq = NULL;
    }
    noRotac2->esq = noRotac1;
    noRotac2->dir = (*no);

    return noRotac2;
}

Arvore* balancearArvoreAVL(Arvore **no) {
  if ((*no) != NULL) {
        (*no)->balanceamento = calcularBalanceamento((*no));
        if ((*no)->balanceamento >= 2) {
            (*no)->esq->balanceamento = calcularBalanceamento((*no)->esq);
            if ((*no)->esq->balanceamento > 0) {
                (*no) = rotacaoDir(no);
            } else {
                (*no) = rotacaoDuplaDir(no);
            }
        } else if ((*no)->balanceamento <= -2) {
            (*no)->dir->balanceamento = calcularBalanceamento((*no)->dir);
            if ((*no)->dir->balanceamento < 0) {
                (*no) = rotacaoEsq(no);
            } else {
                (*no) = rotacaoDuplaEsq(no);
            }
        }
        (*no)->esq = balancearArvoreAVL(&((*no)->esq));
        (*no)->dir = balancearArvoreAVL(&((*no)->dir));
    }
    return (*no);
}

Arvore *sucessor(Arvore *pRaiz, Arvore *sus){
	Arvore *aux;
	
	if(sus -> esq == NULL){
		pRaiz->cliente -> matricula = sus -> cliente -> matricula ;
		aux = sus;
		sus = sus -> dir;
		free(aux);
	}
	sus -> esq = sucessor(pRaiz, sus -> esq);
	return sus;
}

Arvore *antecessor(Arvore *pRaiz, Arvore *ant){
	Arvore *aux;
	
	if(ant -> dir == NULL){
		pRaiz ->cliente -> matricula = ant -> cliente -> matricula ;
		aux = ant;
		ant = ant -> esq;
		free(aux);
	}
	ant -> dir = antecessor(pRaiz, ant -> dir);
	return ant;
}

int removerArvore(Arvore **pRaiz, int matricula){    
	Arvore *aux;	
	if(*pRaiz == NULL)
            return 0;	
	if(matricula >  (*pRaiz)->cliente->matricula )
            removerArvore( &((*pRaiz) -> dir), matricula);
	else
            if(matricula <  (*pRaiz) -> cliente -> matricula )
                removerArvore( &((*pRaiz)-> esq), matricula);
        else{
            if( (*pRaiz) ->   esq == NULL){
                aux = *pRaiz;
                *pRaiz =  (*pRaiz)->dir;
                free(aux);
            }
            else
                if( (*pRaiz)-> dir == NULL){
                    aux = *pRaiz;
                    *pRaiz =  (*pRaiz)->esq;
                    free(aux);
                }
                else
                    if( (*pRaiz) -> dir != NULL)
                        (*pRaiz) -> dir = sucessor((*pRaiz), (*pRaiz) -> dir);
                else
                    (*pRaiz) -> dir = antecessor((*pRaiz), (*pRaiz) -> esq);

            }
    balancearArvoreAVL(pRaiz);
    return 1;
}

void inserirArvore(Arvore **pRaiz, Cliente **cliente){
    if(*pRaiz == NULL){
        *pRaiz = criarNo();
        (*pRaiz)->cliente = *cliente;	 
    }else{
        if((*cliente)->matricula < (*pRaiz)->cliente->matricula)
            inserirArvore( &((*pRaiz)-> esq), cliente);
        if((*cliente)->matricula > (*pRaiz)->cliente->matricula)
            inserirArvore( &((*pRaiz)-> dir), cliente);
        *pRaiz = balancearArvoreAVL(pRaiz);
    }
}






