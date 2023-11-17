// SINTESE
// Algoritmo MediaAnos
// Objetivo :   Realizar média de anos de uma matriz 3x3.
// Entrada :    Valores de ano válidos.
// Saída :      Média dos anos digitados.

// OBS : Este código foi criado no sistema operacional Ubuntu 22.04 LTS.
// Embora eu tenha um pacote instalado que simula comandos do PowerShell e C
// pode ser que alguns comandos sejam diferentes e necessita de adaptações.
// Created by luizh-gsoares on 14/11/2023 - CLion && CodeBlocks

#include <stdlib.h>
#include <stdio.h>

#define ANO_ATUAL   2023
#define ANO_INICIAL 1900
#define TAMANHO     3

// FUNÇÃO : validaAno
// OBJETIVO : Validar se o ano digitado é válido.
// PARÂMETROS : Ano digitado.
// SAÍDA : 0 se o ano for válido, 1 se for inválido.
int validaAno(int ano)
{
    if (ano >= ANO_INICIAL && ano <= ANO_ATUAL)
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

// FUNÇÃO : fazMedia
// OBJETIVO : Realizar média de anos de uma matriz 3x3.
// PARÂMETROS : Matriz 3x3.
// SAÍDA : Média dos anos digitados.
float fazMedia(int matriz[TAMANHO][TAMANHO])
{
    float soma = 0; int contador = 0;

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

    matriz[1][1] = soma; // Define o valor da soma na posição [1][1] conforme enunciado.
    return (float)soma / contador;
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
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
};


int main()
{
    int matriz[TAMANHO][TAMANHO] = {0};
    int continuar = 1;

    while (continuar) {
        system("CLS");

        for (int i = 0; i < TAMANHO; i++) {
            for (int j = 0; j < TAMANHO; j++) {
                if (!(i == 1 && j == 1)) // IGNORA O CENTRO DA MATRIZ
                {
                    printf("Digite o ano da posicao [%d][%d]: ", i + 1, j + 1);
                    matriz[i][j] = lerAno();
                    continue;
                }
                 printf("POSICAO [%d][%d] RESERVADA PARA A SOMA. \n", i + 1, j + 1);
            }
            system("CLS");
        }

        // Exibir dados
        float media = fazMedia(matriz); // Garantir que exibirMedia seja apresentada antes de exibir a média, conforme saída do enunciado.
        exibeMatriz(matriz);
        printf("MEDIA: %.2f \n", media);

        // Continuar
        printf("Deseja sair? (Digite 0 para sair ou qualquer numero para continuar) : ");
        scanf("%d", &continuar);
    };

    return 0;
}
