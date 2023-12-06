// Algoritmo CALCULARAREA
// Síntese
// Objetivo: Calcular a área de uma esfera.
// Entrada : Raio da esfera.
// Saída : Área da esfera com base no raio fornecido.

#include <stdio.h>

#define PI 3.1415
#define ESFERA(raio) (4 * PI * (raio) * (raio))

int main() {
    float raio, area;
    
    printf("Digite o raio da esfera: ");
    scanf("%f", &raio);
    
    area = ESFERA(raio);
    
    printf("A área da esfera com raio %.2f é: %.2f\n", raio, area);
    
    return 0;
}
