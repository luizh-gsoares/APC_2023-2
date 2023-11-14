/*
 * OBJETIVO: Converter o nome no formato UltimoSobrenome/Nome, conforme padrão de empresas de companhia aerea.
 * ENTRADA: Nome completo.
 * SAÍDA: Exibe o nome no formato UltimoSobrenome/Nome.
 * S.O : UBUNTU 22.04 LTS (Alguns comandos podem não funcionar e necessitam ser adaptados para Windows).
 */

#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>

int main() {
    char nome[100];
    char primeiroNome[50];
    char ultimoSobrenome[50];

    printf("Digite o nome completo: ");
    fgets(nome, sizeof(nome), stdin);

    int tamanho = strlen(nome);
    int i = tamanho - 1;
    int ultimoEspaco = -1;

    // Encontrar a posição do último espaço (separador entre último sobrenome e primeiro nome)
    while (i >= 0) {
        if (nome[i] == ' ') {
            ultimoEspaco = i;
            break;
        }
        i--;
    }

    if (ultimoEspaco != -1) {
        // Extrair o último sobrenome
        strncpy(ultimoSobrenome, nome + ultimoEspaco + 1, tamanho - ultimoEspaco - 1);
        ultimoSobrenome[tamanho - ultimoEspaco - 1] = '\0';

        // Extrair o primeiro nome
        strncpy(primeiroNome, nome, ultimoEspaco);
        primeiroNome[ultimoEspaco] = '\0';

        // Formatar o nome de acordo com o padrão da companhia aérea
        printf("Nome formatado: %s/%s\n", ultimoSobrenome, primeiroNome);
    } else {
        printf("Nome inválido!\n");
    }

    return 0;
}


