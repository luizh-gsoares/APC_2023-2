// SINTESE
// OBJETIVO :   Calcular a média de três notas de um aluno.
// ENTRADA :    Não há entradas, os valores são definidos em variáveis conforme enunciado.
// SAÍDA :      A saída é a média dos valores definidos.

#include <stdio.h>

int main()
{
    // Variáveis
    const int QUANTIDADE_NOTAS = 3;
    double nota1, nota2, nota3, media;
    nota1 = 5.5;
    nota2 = 7.2;
    nota3 = 8.3;

    media = (nota1 + nota2 + nota3) / QUANTIDADE_NOTAS;

    printf("MÉDIA: %.2f\n", media);

    return 0;
}
