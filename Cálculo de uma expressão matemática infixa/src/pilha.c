#include <ctype.h>
#include <math.h>
#include "pilha.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Função que inicializa a pilha*/
void inicializaPilha(Node** top) 
{
    *top = NULL;
}

/* Função que empilha */
void empilhaValor(Node** top, float dado) 
{
    Node* novoNo = (Node*)malloc(sizeof(Node));

    if (novoNo == NULL) 
    {
        printf("Erro ao alocar memória para a pilha.\n");
        exit(1);
    }
    novoNo->dado = dado;
    novoNo->proximo = *top;
    *top = novoNo;
}

/* Função que desempilha */
float desempilhaValor(Node** top) 
{
    if (*top == NULL) 
    {
        printf("Erro: a pilha está vazia.\n");
        exit(1);
    }
    Node* temp = *top;
    float dado = temp->dado;
    *top = temp->proximo;
    free(temp);
    return dado;
}

/* Função para verificar se um caractere é um operador */
bool verificaOperadorValido(char caractere) 
{
    return (caractere == '+' || caractere == '-' || caractere == '*' || caractere == '/' || caractere == '$');
}

/* Função para verificar o balanceamento dos parênteses */
bool verificaBalanceamentoParenteses(char* expressao) {
    Node* pilha; // Pilha para rastrear os parênteses abertos
    inicializaPilha(&pilha);

    int tamanho = strlen(expressao);

    for (int i = 0; i < tamanho; i++) {
        if (expressao[i] == '(') {
            empilhaValor(&pilha, '('); // Empilha um parêntese aberto
        } else if (expressao[i] == ')') {
            if (pilha == NULL || desempilhaValor(&pilha) != '(') {
                // Encontrou um parêntese fechado sem um correspondente aberto
                return false;
            }
        }
    }

    // Verifica se todos os parênteses foram fechados
    return (pilha == NULL);
}

/* Função principal para calcular o resultado de uma expressão infixa */
float calculaExpressaoInfixa(char* expressao) 
{
    Node* operadorPilha;
    Node* valorPilha;

    inicializaPilha(&operadorPilha);
    inicializaPilha(&valorPilha);

    int tamanho = strlen(expressao); /* Calcula o tamanho da expressao infixa */

    for (int i = 0; i < tamanho; i++) 
    {
        if (expressao[i] == ' ') 
        {
            continue; /* Ignora espaços em branco */
        } 
        else
            if (isdigit(expressao[i]) || (expressao[i] == '-' && (i == 0 || !isdigit(expressao[i - 1])))) /* Verifica os valores negativos*/
        {
            float valor = 0;
            int sinal = 1;

            if (expressao[i] == '-') /* Muda o sinal caso seja número negativo*/
            {
                sinal = -1;
                i++;
            }

            while (i < tamanho && (isdigit(expressao[i]) || expressao[i] == '.')) /* Verifica se é ponto flutuante*/
            {
                if (expressao[i] == '.') 
                {
                    float fracao = 0.1;
                    i++;
                    while (i < tamanho && isdigit(expressao[i])) 
                    {
                        valor += (expressao[i] - '0') * fracao;
                        fracao *= 0.1;
                        i++;
                    }
                } 
                else 
                {
                    valor = valor * 10 + (expressao[i] - '0');
                    i++;
                }
            }

            valor *= sinal;
            empilhaValor(&valorPilha, valor);
            i--;
        } 
        else 
            if (verificaOperadorValido(expressao[i])) 
        {
            while (operadorPilha != NULL && verificaOperadorValido(operadorPilha->dado) &&
                   ((expressao[i] == '+' || expressao[i] == '-') &&
                    (operadorPilha->dado == '*' || operadorPilha->dado == '/' || operadorPilha->dado =='$'))) 
            {
                float operadorDois = desempilhaValor(&valorPilha);
                float operadorUm = desempilhaValor(&valorPilha);
                char opcao = desempilhaValor(&operadorPilha);

                switch (opcao) 
                {
                    case '+':
                        empilhaValor(&valorPilha, operadorUm + operadorDois);
                        break;
                    case '-':
                        empilhaValor(&valorPilha, operadorUm - operadorDois);
                        break;
                    case '*':
                        empilhaValor(&valorPilha, operadorUm * operadorDois);
                        break;
                    case '/':
                        if (operadorDois == 0) 
                        {
                            printf("Erro: divisão por zero.\n");
                            exit(1);
                        }
                        empilhaValor(&valorPilha, operadorUm / operadorDois);
                        break;
                    case '$':
                        empilhaValor(&valorPilha, pow(operadorUm, operadorDois));
                        break;
                }
            }

            empilhaValor(&operadorPilha, expressao[i]);
        } 
        else 
            if (expressao[i] == '(') 
        {
            empilhaValor(&operadorPilha, expressao[i]);
        } 
        else 
            if (expressao[i] == ')') 
        {
            while (operadorPilha != NULL && operadorPilha->dado != '(') 
            {
                float operadorDois = desempilhaValor(&valorPilha);
                float operadorUm = desempilhaValor(&valorPilha);
                char opcao = desempilhaValor(&operadorPilha);

                switch (opcao) 
                {
                    case '+':
                        empilhaValor(&valorPilha, operadorUm + operadorDois);
                        break;
                    case '-':
                        empilhaValor(&valorPilha, operadorUm - operadorDois);
                        break;
                    case '*':
                        empilhaValor(&valorPilha, operadorUm * operadorDois);
                        break;
                    case '/':
                        if (operadorDois == 0) 
                        {
                            printf("Erro: divisão por zero.\n");
                            exit(1);
                        }
                        empilhaValor(&valorPilha, operadorUm / operadorDois);
                        break;
                    case '$':
                        empilhaValor(&valorPilha, pow(operadorUm, operadorDois));
                        break;
                }
            }
  if (operadorPilha != NULL && operadorPilha->dado == '(') 
            {
                desempilhaValor(&operadorPilha); // Remove o '(' da pilha
            } 
            else 
            {
                printf("Erro: parênteses desbalanceados.\n");
                exit(1);
            }
        } 
        else 
        {
            printf("Erro: caractere inválido na expressão.\n");
            exit(1);
        }
    }

    while (operadorPilha != NULL) 
    {
        if (operadorPilha->dado == '(') 
        {
            printf("Erro: parênteses desbalanceados.\n");
            exit(1);
        }

        float operadorDois = desempilhaValor(&valorPilha);
        float operadorUm = desempilhaValor(&valorPilha);
        char opcao = desempilhaValor(&operadorPilha);

        switch (opcao) 
        {
            case '+':
                empilhaValor(&valorPilha, operadorUm + operadorDois);
                break;
            case '-':
                empilhaValor(&valorPilha, operadorUm - operadorDois);
                break;
            case '*':
                empilhaValor(&valorPilha, operadorUm * operadorDois);
                break;
            case '/':
                if (operadorDois == 0) 
                {
                    printf("Erro: divisão por zero.\n");
                    exit(1);
                }
                empilhaValor(&valorPilha, operadorUm / operadorDois);
                break;
            case '$':
                empilhaValor(&valorPilha, pow(operadorUm, operadorDois));
                break;
        }
    }

    if (valorPilha == NULL) 
    {
        printf("Erro: a pilha de valores está vazia.\n");
        exit(1);
    }

    return desempilhaValor(&valorPilha);
}
