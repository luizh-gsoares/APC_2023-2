// SINTESE
// Algoritmo MediaAnos
// Objetivo :   Realizar média de anos de uma matriz 3x3.
// Entrada :    Valores de ano válidos.
// Saída :      Média dos anos digitados.

// OBS : Este código foi criado no sistema operacional Ubuntu 22.04 LTS,
// Logo, alguns comandos podem ser diferentes do Windows Ex: system("cls").
// Created by luizh-gsoares on 14/11/2023

#include <stdlib.h>
#include <stdio.h>

#define ANO_ATUAL   2023
#define ANO_INICIAL 1900
#define TAMANHO     3

// FUNÇÃO : fazMedia
// OBJETIVO : Realizar média de anos de uma matriz 3x3.
// PARÂMETROS : Matriz 3x3.
// SAÍDA : Média dos anos digitados.
float fazMedia(int matriz[TAMANHO][TAMANHO])
{
    int soma = 0; int contador = 0;

    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            if (!(i == 1 && j == 1)) // IGNORA O CENTRO DA MATRIZ
            {
                soma += matriz[i][j];
                contador++;
            }
        }
    }

    return (float)soma / contador;
};

// FUNÇÃO : validaAno
// OBJETIVO : Validar se o ano digitado é válido.
// PARÂMETROS : Ano digitado.
// SAÍDA : 0 se o ano for válido, 1 se for inválido.
int validaAno(int ano)
{
    if (ano > ANO_INICIAL && ano <= ANO_ATUAL)
    {
        return 0;
    }
    else
    {
    printf("Ano invalido! Digite novamente: ");
    return 1;
    }

};

// FUNÇÃO : lerAno
// OBJETIVO : Ler o ano digitado.
// PARÂMETROS : Nenhum.
// SAÍDA : Ano digitado.
int lerAno()
{
    int ano;

    do
    {
        fflush(stdin);
        scanf("%d", &ano);
    } while(validaAno(ano));

    return ano;
};

// FUNÇÃO : exibeMatriz
// OBJETIVO : Exibir a matriz 3x3.
// PARÂMETROS : Matriz 3x3.
// SAÍDA : Nenhuma.
void exibeMatriz(int matriz[TAMANHO][TAMANHO])
{
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
};


int main()
{
    int matriz[TAMANHO][TAMANHO] = {0};

    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            if (!(i == 1 && j == 1)) // IGNORA O CENTRO DA MATRIZ
            {
            printf("Digite o ano da posicao [%d][%d]: ", i + 1, j + 1);           
            matriz[i][j] = lerAno();
            }
        }
        system("cls");
    }
    
    printf("MEDIA:\n");
    fazMedia(matriz);

    
    return 0;
}
