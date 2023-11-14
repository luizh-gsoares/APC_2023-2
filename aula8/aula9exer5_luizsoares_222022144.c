// SINTESE
// Algoritmo Moldura
// Objetivo :   Imprimir uma moldura.
// Entrada :    Não há entrada
// Saída :      Moldura

// OBS : Este código foi criado no sistema operacional Ubuntu 22.04 LTS,
// Logo, alguns comandos podem ser diferentes do Windows Ex: system("cls").
// Created by luizh-gsoares on 24/10/2023


#include <stdio.h>

int main() {
    int i, j;
    const int TAMANHO_HORIZONTAL = 4;
    const int TAMANHO_VERTICAL = 4;

    // Códigos hexadecimais dos caracteres
    char* caracteres[4][4] = {
            { "\xC9", "\xCD", "\xCD", "\xBB" },
            { "\xBA", " ", " ", "\xBA" },
            { "\xBA", " ", " ", "\xBA" },
            { "\xC8", "\xCD", "\xCD", "\xBC" }
    };

    // Imprimir Matriz Multidimensional [4][4]
    for (i = 0; i < TAMANHO_VERTICAL; i++) {
        for (j = 0; j < TAMANHO_HORIZONTAL; j++) {
            printf("%s", caracteres[i][j]);
        }
        printf("\n");
    }



    return 0;
}
