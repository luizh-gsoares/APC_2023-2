// SINTESE
// Algoritmo ComparaCarros
// Objetivo :   Realizar comparações de quais carros digitados são iguais aos modelos pré-definidos.
// Entrada :    Vetor de 10 carros.
// Saída :      Vetor dos 10 carros digitados e quais estão indisponiveis ou não.

// OBS : Este código foi criado no sistema operacional Ubuntu 22.04 LTS,
// Logo, alguns comandos podem ser diferentes do Windows Ex: system("cls").
// Created by luizh-gsoares on 14/11/2023

#include <stdio.h>
#include <string.h>

#define NUM_CARROS 10
#define TAM_TXT_CARROS 20
#define TAM_MAX_MODELO 4

int main() {
    // Vetor carros
    char carros[NUM_CARROS][TAM_TXT_CARROS];
    char *modelos[TAM_MAX_MODELO] = {"Astra", "Omega", "Vectra", "Silverado"}; // caso seja criado novos modelos, alterar o valor da diretiva de substituição.

    // Entrada do nome dos carros
    printf("Informe os nomes de %d carros: \n", NUM_CARROS);
    for (int cont = 0; cont < NUM_CARROS; cont++) {
        printf("%d-", cont + 1);
        scanf("%s", carros[cont]);
        fflush(stdin); // Limpar Buffer de Teclado
    }

    // Mostra a relação final
    printf("\nCARROS SOLICITADOS\t\tRELACAO FINAL\n");

    for (int i = 0; i < NUM_CARROS; i++) {
        int encontrado = 0; // variável para verificar se o modelo foi encontrado

        for (int j = 0; j < TAM_MAX_MODELO; j++) {
            if (strcmpi(carros[i], modelos[j]) == 0) {
                printf("%d- %s\t\t\t%s\n", i + 1, carros[i], modelos[j]);
                encontrado = 1;
                break; // modelo encontrado, sair do loop interno
            }
        }

        if (!encontrado) {
            printf("%d- %s\t\t\tindisponivel\n", i + 1, carros[i]);
        }
    }

    return 0;
}