
// Síntese
//  Objetivo: Solicitar a letra inicial para identificar o sexo de uma pessoa e determinar o sexo correspondente (Masculino ou Feminino), usando o operador condicional ternário.
//  Entrada : Letra inicial (M/m ou F/f) para identificar o sexo.
//  Saída   : Exibir o sexo correspondente (Masculino, Feminino) ou "Sexo inválido!".
#include <stdio.h>

int main() {
    char letra;

    printf("Digite a letra inicial (M/m ou F/f) para identificar o sexo: ");
    scanf(" %c", &letra);

    (letra == 'M' || letra == 'm') ? printf("Masculino\n") :
    (letra == 'F' || letra == 'f') ? printf("Feminino\n") :
    printf("Sexo inválido!\n");

    return 0;
}

//algoritmo definitSexo;
// Síntese
//  Objetivo: Solicitar a letra inicial para identificar o sexo de uma pessoa e determinar o sexo correspondente (Masculino ou Feminino), usando o operador condicional.
//  Entrada : Letra inicial (M/m ou F/f) para identificar o sexo.
//  Saída   : Exibir o sexo correspondente (Masculino, Feminino) ou "Sexo inválido!".



//principal
// Declarações
//caracter letra;

// Instruções
//escreval("Digite a letra inicial (M/m ou F/f) para identificar o sexo: ");
//leiaCaracter(letra);
//
//se ((letra == 'M') ou (letra == 'm')) entao
//escreval("Masculino");
//senao
//se (letra == 'F' ou letra == 'f') entao
//escreval("Feminino");
//senao
//escreval("Sexo inválido!");
//fimSe
//        fimSe
//
//
//fimPrincipal
