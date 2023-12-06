<<<<<<< Updated upstream
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


=======
#include <stdio.h>

// Protótipos das funções
int lerAnoNascimento();
int lerAnoAtual(int anoNascimento);
int validarAnoNascimento(int anoNascimento);
int validarAnoAtual(int anoAtual, int anoNascimento);
int calculaIdade(int anoNascimento, int anoAtual);
char* verificaNivel(int idade);
void mostraResultado(int idade, char *nivel);
char maiusculoCaracter(char c);
void limpaTela();

int main() {
    // Declarações
    int anoNascimento, anoAtual, idade;
    char continuar, *nivel;

    // Instruções
    do {
        anoNascimento = lerAnoNascimento();

        anoAtual = lerAnoAtual(anoNascimento);

        idade = calculaIdade(anoNascimento, anoAtual);

        nivel = verificaNivel(idade);

        mostraResultado(idade, nivel);

        printf("Pressione S (SIM) para continuar ou qualquer outra tecla para encerrar a análise: ");
        scanf(" %c", &continuar);
        continuar = maiusculoCaracter(continuar);
        limpaTela();
    } while (continuar == 'S');

    return 0;
}

// Implementações das funções
int lerAnoNascimento() {
    int anoNascimento;
    printf("Informe o ano de nascimento (D.C): ");
    scanf("%d", &anoNascimento);
    return validarAnoNascimento(anoNascimento);
}

int lerAnoAtual(int anoNascimento) {
    int anoAtual;
    printf("Informe a data atual: ");
    scanf("%d", &anoAtual);
    return validarAnoAtual(anoAtual, anoNascimento);
}

int validarAnoNascimento(int anoNascimento) {
    while (anoNascimento < 0) {
        printf("Data Inválida! Digite Novamente: ");
        scanf("%d", &anoNascimento);
    }
    return anoNascimento;
}

int validarAnoAtual(int anoAtual, int anoNascimento) {
    while (anoAtual < anoNascimento || anoAtual > anoNascimento + 122) {
        if (anoAtual < anoNascimento) {
            printf("Data Inválida! Não existe viagem no tempo. Digite Novamente: ");
        } else {
            printf("Data Inválida! Nenhuma pessoa no mundo viveu mais do que 122 anos. Digite Novamente: ");
        }
        scanf("%d", &anoAtual);
    }
    return anoAtual;
}

int calculaIdade(int anoNascimento, int anoAtual) {
    return anoAtual - anoNascimento;
}

char* verificaNivel(int idade) {
    if (idade <= 10) {
        return "CRIANÇA";
    } else if (idade < 18) {
        return "ADOLESCENTE";
    } else if (idade < 25) {
        return "JOVEM";
    } else if (idade <= 58) {
        return "ADULTO";
    } else {
        return "IDOSO";
    }
}

void mostraResultado(int idade, char *nivel) {
    limpaTela();
    printf("Idade: %d anos => %s\n", idade, nivel);
}

char maiusculoCaracter(char c) {
    if (c >= 'a' && c <= 'z') {
        c = c - 32; // Convertendo para maiúscula na tabela ASCII
    }
    return c;
}

void limpaTela() {
    // Função para limpar a tela (depende do sistema operacional)
    // Implemente conforme necessário
}
>>>>>>> Stashed changes
