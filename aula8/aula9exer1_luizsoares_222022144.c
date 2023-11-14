// SINTESE
// Algoritmo Porcentagem.
// Objetivo :   Realizar o cálculo de porcentagem de um valor, baseado em uma constante.
// Entrada :    Valor percenteual a ser calculado
// Saída :      percentual

// OBS : Este código foi criado no sistema operacional Ubuntu 22.04 LTS,
// Logo, alguns comandos podem ser diferentes do Windows Ex: system("cls").
// Created by luizh-gsoares on 24/10/2023


#include <stdio.h>

int main() {
    // Declarações
    const int constante = 555;
    double percentual, resultado;

    // Instruções
    printf("Informe o valor percentual : ");
    scanf("%lf", &percentual);

    resultado = (percentual / 100.0) * constante;

    // Limpar a tela - Linux
    system("clear");

    // Resultado
    printf("O resultado do calculo percentual eh: %.2lf %% ", resultado);

    return 0;
}