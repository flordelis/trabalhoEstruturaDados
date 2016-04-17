/* 
 * File:   cliente.c
 * Author: helis
 *
 * Created on 16 de Abril de 2016, 19:56
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cliente.h"

struct tm *DataAtual; //estrutura para armazenar data e hora.
time_t Segundos;

int ObtemAno(void){
    time(&Segundos); //obtém a hora em segundos.
    DataAtual = localtime(&Segundos); //converte horas em segundos para estrutura tm
    return 1900 + (DataAtual->tm_year); //retorna o ano atual.
}

int calcularIdadeCliente(Data dataNascimento) {
    return ObtemAno() - dataNascimento.ano;
}

void imprimirCliente(Cliente c) {
    printf("\n---- Cliente ----\n");
    printf("Matricula: %d\n", c.matricula);
    printf("Nome: ");
    puts(c.nome);
    printf("Endereco: ");
    puts(c.endereco);
    printf("Telefone: ");
    puts(c.telefone);
    printf("E-mail: ");
    puts(c.email);
    printf("Data de Nascimento: %d/%d/%d\n", c.dataNascimento.dia, c.dataNascimento.mes, c.dataNascimento.ano);
    printf("Idade: %d anos\n", calcularIdadeCliente(c.dataNascimento));
 }