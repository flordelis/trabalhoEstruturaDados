/* 
 * File:   lista.h
 * Author: helis
 *
 * Created on 17 de Abril de 2016, 07:46
 */

#ifndef LISTA_H
#define	LISTA_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "cliente.h"
typedef struct lista Lista;

int inserirLista (Lista **inicio, Cliente **cliente);
int removerLista (Lista **inicio, int matricula);
Cliente* buscarLista (Lista *inicio, int matricula);
#ifdef	__cplusplus
}
#endif

#endif	/* LISTA_H */

