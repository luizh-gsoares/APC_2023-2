//Sintese
// Objetivo: Gerenciar cadastro de cidades e DDDs.
// Entrada: ddd e nome da cidade.
// Saida: cidades, ddd cadastrados, quantidades de cadastros.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cidade {
    int ddd;
    char nome[30];
};

// Protótipos das funções
int criarArquivo(const char *nomeArquivo);
int validarDDD(int ddd);
int validarCidade(char *nome);
void cadastrarCidade(FILE *arquivo);
void apresentarCidades(FILE *arquivo);

int main() {
    // Declaracoes
    int criaArquivo, opcao, qtdRegistros;
    FILE *arquivo;

    // Instrucoes
    if(arquivo = fopen("local.bin", "rb"))
        if(!fclose(arquivo))
            printf("Arquivo ja existe e nao sera criado.\n");
        else
            printf("Arquivo ja existe e NAO fechado com sucesso.\n");
    else {
        printf("Arquivo ainda NAO existe e precisara ser criado.\n");
        do {
            if(!criarArquivo("local.bin")) {
                criaArquivo = 0;
                printf("Falha ao criar o arquivo de dados.\n");
                puts("Digite S para tentar novamente ou outra para terminar");
            } else {
                criaArquivo = 1;
                printf("Arquivo criado com sucesso\n");
            }
        } while ((!criaArquivo) && (toupper(getche()) == 'S'));
    }

    while (opcao != 3) {
        printf("\nMenu:\n");
        printf("1 - Cadastrar cidade\n");
        printf("2 - Apresentar cidades cadastradas\n");
        printf("3 - Sair do programa\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCidade(arquivo);
                break;
            case 2:
                apresentarCidades(arquivo);
                break;
            case 3:
                if((arquivo = fopen("local.bin", "rb")) != NULL){
                   fseek(arquivo, 0, SEEK_END);
                   qtdRegistros = ftell(arquivo) / sizeof(struct Cidade);
                   printf("\nTotal de registros cadastrados: %d\n", qtdRegistros);
                   if(!fclose(arquivo))
                       printf("Arquivo finalizado em seguranca.\n");
                   else
                       printf("Arquivo NAO fechado.\n");
                }
                else
                    printf("Arquivo NAO pode ser aberto para contagem.\n");

                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    fclose(arquivo);
    return 0;
}

// ======= SUBPROGRAMAS =============

//Objetivos: Criar arquivo
//Parametros: Filename
//Retorno: situacao da criacao do arquivo
int criarArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo != NULL) {
        fclose(arquivo);
        return 1;
    } else
        return 0;
}

//Objetivo: validar ddd
//Parametros: ddd
//Retorno: ddd valido
int validarDDD(int ddd) {
    return ddd >= 10 && ddd <= 99;
}

//Objetivo: validar cidade
//Parametros: nome da cidade
//Retorno: cidade valida
int validarCidade(char *nome) {
    return nome && strlen(nome) >= 3;
}

//Objetivo: cadastrar cidade e ddd
//Parametros: ddd e cidade
//Retorno: nenhum
void cadastrarCidade(FILE *arquivo) {
    struct Cidade cidade;

    printf("Digite o DDD da cidade (10-99): ");
    scanf("%d", &cidade.ddd);

    if (!validarDDD(cidade.ddd)) {
        printf("Erro: DDD inválido.\n");
        return;
    }

    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", cidade.nome);

    if (!validarCidade(cidade.nome)) {
        printf("Erro: Nome da cidade invalido.\n");
        return;
    }

    if((arquivo = fopen("local.bin", "ab")) != NULL){
     if(fwrite(&cidade, sizeof(struct Cidade), 1, arquivo)) {
        printf("Cidade cadastrada com sucesso.\n");
        if(!fclose(arquivo))
            printf("Arquivo fechado em seguranca.\n");
        else
            printf("Arquivo NAO fechado.\n");
     }
     else
        printf("Cidade NAO cadastrada.\n");
    }
}

//Objetivo: apresentar as Cidades
//Parametros: nenhum
//Retorno: nenhum
void apresentarCidades(FILE *arquivo) {
    struct Cidade cidade;

    printf("\nDDI\tCIDADE\n");
    printf("-------------------\n");

    if((arquivo = fopen("local.bin", "rb")) != NULL){
        while (fread(&cidade, sizeof(struct Cidade), 1, arquivo) == 1) {
            printf("%d\t%s\n", cidade.ddd, cidade.nome);
        }

        if(!fclose(arquivo))
            printf("Arquivo fechado em seguranca.\n");
        else
            printf("Arquivo NAO fechado.\n");
     }
     else
        printf("Arquivo NAO pode ser aberto.\n");
}
