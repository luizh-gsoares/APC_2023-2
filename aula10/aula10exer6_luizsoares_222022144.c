// Algoritmo CALCULA_MEDIA
// Síntese
//  Objetivo: Calcular a média aritmética de três valores numéricos validados entre 0 e 100.
//  Entrada : Três valores numéricos (notas).
//  Saída   : Média aritmética dos valores fornecidos.

#include <stdio.h>

    #define VALIDAR_NOTA(nota) ((nota > 0 && nota <= 100) ? 1 : 0)
    #define CALCULA_MEDIA(a, b, c) (((a) + (b) + (c)) / 3.0)

    int main() {
        float nota1, nota2, nota3;
        float media;

        do {
            printf("Digite a primeira nota (de 0 a 100): ");
            scanf("%f", &nota1);
        } while (VALIDAR_NOTA(nota1) == 0);

        do {
            printf("Digite a segunda nota (de 0 a 100): ");
            scanf("%f", &nota2);
        } while (VALIDAR_NOTA(nota2) == 0);

        do {
            printf("Digite a terceira nota (de 0 a 100): ");
            scanf("%f", &nota3);
        } while (VALIDAR_NOTA(nota3) == 0);

        media = CALCULA_MEDIA(nota1, nota2, nota3);

        printf("A média das notas %.2f, %.2f e %.2f é: %.2f\n", nota1, nota2, nota3, media);

        return 0;
    }
