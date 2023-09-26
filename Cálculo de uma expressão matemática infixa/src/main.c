/*
Programa: Cálculo de uma expressão matemática
Descrição: O programa desenvolvido tem como objetivo realizar o cálculo de uma expressão matemática infixa, respeitando as ordens de precedência
de um cálculo matemático.
Programador: Gabriela Marculino
RGM: 41431
Data da última modificação: 25/09/2023 às 23:00
*/

/*
linha de comando para compilar: gcc main.c pilha.h pilha.c -o main.exe -Wall -pedantic -Wextra -Werror 
*/

#include <ctype.h> /*isdigit()*/
#include <math.h> /*pow()*/
#include "pilha.h"
#include <stdbool.h> /*true/false*/
#include <stdlib.h> /*system()*/
#include <string.h> /*strlen()*/
#include <stdio.h> /*printf()*/


int main(int argc, char *argv[]) 
{
    argc = argc;
	argv = argv;
    
    char expressao[100];
    printf("Digite a expressao infixa: ");
    fgets(expressao, sizeof(expressao), stdin);

    /*remover o caractere de nova linha da entrada*/
    size_t tamanho = strlen(expressao);
    if (tamanho > 0 && expressao[tamanho - 1] == '\n') 
    {
        expressao[tamanho - 1] = '\0';
    }

    float resultado = calculaExpressaoInfixa(expressao);
    printf("Resultado da expressao infixa: %.2f\n", resultado);

    return 0;
}
