/* 
 * File:   arvore.h
 * Author: helis
 *
 * Created on 16 de Abril de 2016, 20:06
 */

#ifndef ARVORE_H
#define	ARVORE_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "cliente.h"
typedef struct arvore Arvore;

void criarArvore(Arvore **pRaiz);
void exibirEmOrdem(Arvore *pRaiz);
void exibirPreOrdem(Arvore *pRaiz);
void exibirPosOrdem(Arvore *pRaiz);
float calcularMediaIdade(Arvore *pRaiz);
Cliente *buscarArvore(Arvore *pRaiz, int matricula);
void inserirArvore(Arvore **pRaiz, Cliente **cliente);
int removerArvore(Arvore **pRaiz, int matricula);


#ifdef	__cplusplus
}
#endif

#endif	/* ARVORE_H */

