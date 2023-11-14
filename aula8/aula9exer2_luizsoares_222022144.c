// SINTESE
// Algoritmo MaiorValor.
// Objetivo :   Encontrar o maior valor dentre 3 números
// Entrada :    Três números inteiros
// Saída :      Maior valor

// OBS : Este código foi criado no sistema operacional Ubuntu 22.04 LTS,
// Logo, alguns comandos podem ser diferentes do Windows Ex: system("cls").
// Created by luizh-gsoares on 24/10/2023.

#include <stdio.h>

int main() {
    // Declarações
    int valor1, valor2, valor3, maior;

    // Instruções

    // Solicita ao usuário que insira os valores
    printf("Informe o primeiro valor:   \n");
    scanf("%d", &valor1);
    printf("Informe o segundo valor:    \n");
    scanf("%d", &valor2);
    printf("Informe o terceiro valor:   \n");
    scanf("%d", &valor3);


    // Limpa a tela - Linux
    system("clear");

    // Compara qual e o maior
    if (valor1 > valor2) {
        if (valor1 > valor3) {
            maior = valor1;
        } else {
            maior = valor3;
        }
    } else {
        if (valor2 > valor3) {
            maior = valor2;
        } else {
            maior = valor3;
        }
    }

    // Imprime o maior número
    printf("MAIOR: %d\n", maior);

    system("PAUSE");

    return 0;
}