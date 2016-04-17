/* 
 * File:   cliente.h
 * Author: helis
 *
 * Created on 17 de Abril de 2016, 07:51
 */

#ifndef CLIENTE_H
#define	CLIENTE_H

#ifdef	__cplusplus
extern "C" {
#endif
#define VARCHAR 80
    
typedef struct data {
    int dia;
    int mes;
    int ano;
}Data;

typedef struct cliente{
    int matricula;
    char nome[VARCHAR];
    char endereco[VARCHAR];
    char telefone[VARCHAR];
    char email[VARCHAR];
    Data dataNascimento;	
} Cliente;

int calcularIdadeCliente(Data dataNascimento);
void imprimirCliente(Cliente c);


#ifdef	__cplusplus
}
#endif

#endif	/* CLIENTE_H */

