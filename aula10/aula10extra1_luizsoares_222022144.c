#include <stdio.h>
#include <ctype.h>

// Síntese
//  Objetivo: Receber frases do usuário, converter para letras maiúsculas e contar a ocorrência
//            de vogais e espaços na frase.
//  Entrada : Frase inserida pelo usuário.
//  Saída   : A frase em letras maiúsculas, contagem da ocorrência de vogais (A, E, I, O, U) e
//            espaços na frase.
// S.O :      UBUNTU 22.04 LTS (Verifique a possibilidade de rodar no Windows).


// OBJETIVO: Converter a frase para letras maiúsculas
// PARAMETROS: frase - array de caracteres contendo a frase a ser convertida para maiúsculas
// RETORNO: Nenhum (void)
void converterParaMaiusculas(char frase[]) {
    int i = 0;
    while (frase[i] != '\0') {
        frase[i] = toupper(frase[i]);
        i++;
    }
}


// OBJETIVO: Contar a quantidade de cada vogal e espaços na frase
// PARAMETROS: frase - array de caracteres contendo a frase a ser analisada
// RETORNO: Nenhum (void)
void contarVogaisEEspacos(char frase[]) {
    int vogais[5] = {0}; // a, e, i, o, u
    int espacos = 0;
    int i = 0;

    while (frase[i] != '\0') {
        if (frase[i] == 'A') vogais[0]++;
        else if (frase[i] == 'E') vogais[1]++;
        else if (frase[i] == 'I') vogais[2]++;
        else if (frase[i] == 'O') vogais[3]++;
        else if (frase[i] == 'U') vogais[4]++;
        else if (frase[i] == ' ') espacos++;
        i++;
    }

    printf("\nQuantidade de vogais:");
    printf("\nA: %d, E: %d, I: %d, O: %d, U: %d", vogais[0], vogais[1], vogais[2], vogais[3], vogais[4]);
    printf("\nEspacos: %d\n", espacos);
}

int main() {
    char frase[1000];
    char resposta;

    do {
        printf("Digite uma frase: ");
        fgets(frase, sizeof(frase), stdin);

        converterParaMaiusculas(frase);

        printf("\nFrase em maiusculas: %s", frase);

        contarVogaisEEspacos(frase);

        printf("\nDeseja informar outra frase? (S/N): ");
        scanf(" %c", &resposta);

        // USADO PARA LIMPAR BUFFER DE ENTRADA (LINUX E WINDOWS)
        while (getchar() != '\n');

    } while (resposta == 'S' || resposta == 's');

    return 0;
}
