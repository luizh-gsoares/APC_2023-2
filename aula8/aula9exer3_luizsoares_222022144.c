// Algoritmo ConverterCaractere.

// SINTESE
// Objetivo :   Apresentar um caractere como decimal, octal e hexadecimal.
// Entrada :    Caractere.
// Saída :      Caractere digitado, decimal, octal e hexadecimal.

// OBS : Este algoritmo foi criado no sistema operacional Ubuntu 22.04 LTS.
// Logo, alguns comandos podem ser diferentes para Windows (system("clear")).

#include <stdio.h>

int main() {
    // Declarações
    char character;

    // Instruções
    // Solicita ao usuário que insira um caractere
    printf("INSIRA UM CARACTERE: ");
    scanf(" %c", &character);

    // Limpa a tela - Linux
    system("clear");

    // Apresenta o caractere de diferentes formas
    printf("Caractere:      %c\n", character);
    printf("Decimal:        %d\n", character);
    printf("Octal:          %o\n", character);
    printf("Hexadecimal:    0x%x\n", character);

    return 0;
}