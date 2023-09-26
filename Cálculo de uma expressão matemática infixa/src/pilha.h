#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include <ctype.h> /*isdigit()*/
#include <math.h> /*pow()*/
#include <stdbool.h> /*true/false*/
#include <stdlib.h> /*system()*/
#include <string.h> /*strlen()*/
#include <stdio.h> /*printf()*/

/* Definição do tipo de dado da pilha */
typedef struct Node {
    float dado;
    struct Node* proximo;
}Node;


/*função para inicializar a pilha*/
void inicializaPilha(Node** top);

/*função para empilhar um valor na pilha*/
void empilhaValor(Node** top, float dado);

/*função para desempilhar um valor da pilha*/
float desempilhaValor(Node** top);

/*função para verificar se um caractere é um operador*/
bool verificaOperadorValido(char caractere);

/*função para verificar o balanceamento dos parenteses*/
bool verificaBalanceamentoParenteses(char* expressao);

/*função principal para calcular o resultado de uma expressão infixa*/
float calculaExpressaoInfixa(char* expressao);

#endif /*PILHA_H_INCLUDED*/