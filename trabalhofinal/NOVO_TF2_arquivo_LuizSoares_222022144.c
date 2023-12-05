// ========== Trabalho Final -  TEMA 2 - CURSOS PROFISSIONALIZANTES  ==========
// Aluno : Luiz Henrique Guimarães Soares - 222022144
// Realizado no Sistema Operacional Ubuntu 22.04 LTS (Linux) - Compilador GCC

// Objetivo: Gerenciar cursos profissionalizantes oferecidos a jovens carentes no Distrito Federal,
// permitindo o cadastro, edição, listagem, pesquisa por modalidade e exclusão de cursos.

// Entrada:
// - Dados para cadastrar um curso: Código de Identificação do Curso (CIC), Nome Completo do Curso,
// - Sigla da Escola e Modalidade do Curso.
// - Opções do menu escolhidas pelo usuário.

// Saída:
// - Relatórios tabelares ordenados alfabeticamente (CRES OU DESC) com informações dos cursos.

// ============================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <windows.h>


#define MAXIMO 5
#define MINIMO 5
#define MINCIC 10
#define MAXNOME 50

// Struct para armazenar os dados de cada curso
typedef struct
{
    int cic;                    // Código de Identificação do Curso
    char nomeCompleto[MAXNOME]; // Nome completo do curso
    char siglaEscola[MAXIMO];   // Sigla da escola
    char modalidadeCurso;       // Modalidade do curso com char
} curso;

// ========== PROTÓTIPOS  ==========

// Protótipos das funções do sistema
void menu();
void menuListarCursos();
void limpaTela();
void limparBuffer();
void pausar();
int continuar();
void dormir(int segundos);
void localizacao();

// Protótipos das funções de validação
int validaCic(int cic, FILE *arquivo);
int validaNomeCompleto(char *nomeCompleto);
int validaSiglaEscola(char *siglaEscola);
int validaModalidadeCurso(char modalidadeCurso);

// Protótipos das funções de leitura de dados
void lerCic(int *cic, FILE *arquivo);
void lerNomeCompleto(char *nomeCompleto);
void lerSiglaEscola(char *siglaEscola);
void lerModalidadeCurso(char *modalidadeCurso);

// Protótipos das funções de cadastro
curso cadastrarCurso(FILE *arquivo);

// Protótipos das funções de listagem
void listarCursos(FILE *arquivo);
void ordenarCursosCrescente(FILE *arquivo);
void ordenarCursosDecrescente(FILE *arquivo);
void exibirTabela(curso *vetorCursos, int tamanhoVetor);
char *verificaModalidadeCurso(char modalidadeCurso);


// Protótipos das funções de arquivo
void criarArquivo();

// ==========================
// ========== MAIN ==========
// ==========================
int main()
{
    int opcao;               // Opção do menu
    FILE *arquivo;           // Arquivo binário
    localizacao();

    // Verifica se o arquivo existe
    arquivo = fopen("cursos.bin", "rb");
    if (arquivo != NULL)
    {
        // Se o arquivo existir, fecha o arquivo
        fclose(arquivo);
    }
    else
    {
        // Se o arquivo não existir, cria o arquivo
        printf("Arquivo nao existe! Aguarde um instante . . .\n");
        dormir(2);
        criarArquivo();
    }

    // Se o arquivo existir, abre o arquivo para leitura e escrita
    arquivo = fopen("cursos.bin", "rb+");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }


    do
    {
        limpaTela();
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        // Cadastrar um curso
            limparBuffer();
            do
            {
                limpaTela();
                arquivo = fopen("cursos.bin", "ab");

                // Cadastrar um curso
                curso novoCurso = cadastrarCurso(arquivo);

                // Grava o curso no arquivo
                fwrite(&novoCurso, sizeof(curso), 1, arquivo);
                fclose(arquivo);
                printf("Curso cadastrado com sucesso!\n");
            }
            while (continuar());
            break;
        case 2:
            break;

        case 3:
            // Listar cursos
            listarCursos(arquivo);
            break;
        case 5:
            // Excluir um curso
            limparBuffer();

            if (apagarArquivo())
            {
                criarArquivo();
                printf("Criando o arquivo...\n");
                dormir(1);
                arquivo = fopen("cursos.bin", "rb+");
            }
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    }
    while (opcao != 0);

    return 0;
}

// ====================================
// ========== SUBALGORITMOS  ==========
// ====================================

// ========== INICIO CADASTRO ==========

// Função: cadastrarCurso
// Objetivo: Cadastrar um curso
// Parâmetros: Arquivo binário
// Saída: Novo curso cadastrado (struct) com os dados validados
curso cadastrarCurso(FILE *arquivo)
{
    curso novoCurso; // Novo curso a ser cadastrado

    limpaTela();

    printf("=======================================\n");
    printf("========== CADASTRO DE CURSO ==========\n");
    printf("=======================================\n");

    // CIC
    printf("Digite o CIC do curso (Valor acima de %d): ", MINCIC);
    lerCic(&novoCurso.cic, arquivo);

    // NOME COMPLETO
    printf("Digite o nome completo do curso (min %d max %d caracteres): ", MINIMO, MAXNOME);
    lerNomeCompleto(novoCurso.nomeCompleto);

    // SIGLA DA ESCOLA
    printf("Digite a sigla da escola (max %d caracteres): ", MAXIMO);
    lerSiglaEscola(novoCurso.siglaEscola);

    // MODALIDADE DO CURSO
    printf("Digite a modalidade do curso (P - Presencial, S - Semipresencial, D - Distância):");
    lerModalidadeCurso(&novoCurso.modalidadeCurso);

    return novoCurso;
}
// ============ FIM CADASTRO =============

// ============ INICIO LER ============

// Função: lerCic
// Objetivo: Ler o CIC do curso
// Parâmetros: Ponteiro para armazenar o CIC do curso e arquivo binário
// Saída: Nenhuma
void lerCic(int *cic, FILE *arquivo)
{
    do
    {
        limparBuffer();
        scanf("%d", cic);
    }
    while (validaCic(*cic, arquivo));
}

// Função: lerNomeCompleto
// Objetivo: Ler o nome completo do curso
// Parâmetros: Ponteiro para armazenar o nome completo do curso
// Saída: Nenhuma
void lerNomeCompleto(char *nomeCompleto)
{
    do
    {
        limparBuffer();
        scanf("%[^\n]s", nomeCompleto);
    }
    while (validaNomeCompleto(nomeCompleto));
}

// Função: lerSiglaEscola
// Objetivo: Ler a sigla da escola
// Parâmetros: Ponteiro para armazenar a sigla da escola
// Saída: Nenhuma
void lerSiglaEscola(char *siglaEscola)
{
    do
    {
        limparBuffer();
        scanf("%[^\n]s", siglaEscola);
    }
    while (validaSiglaEscola(siglaEscola));
}

// Função: lerModalidadeCurso
// Objetivo: Ler a modalidade do curso
// Parâmetros: Ponteiro para armazenar a modalidade do curso
// Saída: Nenhuma
void lerModalidadeCurso(char *modalidadeCurso)
{
    do
    {
        limparBuffer();
        scanf(" %c", modalidadeCurso);

        // transforma a modalidade do curso em maiúscula
        *modalidadeCurso = toupper(*modalidadeCurso);

    }
    while (validaModalidadeCurso(*modalidadeCurso));
}

// ============= FIM LER =============

// ========== INICIO VALIDA ==========

// Função       : validaCic
// Objetivo     : Validar o CIC do curso
// Parâmetros   : CIC do curso e arquivo binário
// Saída        : 0 para válido e 1 para inválido
int validaCic(int cic, FILE *arquivo)
{
    // Abre o arquivo para leitura
    arquivo = fopen("cursos.bin", "rb");
    // vai para o início do arquivo
    rewind(arquivo);

    // Verifica se o CIC já existe no arquivo, iterando sobre as linhas do arquivo
    curso cursoLido;
    while (fread(&cursoLido, sizeof(curso), 1, arquivo))
    {
        if (cursoLido.cic == cic)
        {
            printf("CIC ja existe! Digite novamente:");
            return 1;
        }
    }

    // Verifica se o CIC é menor que o mínimo
    if (cic < MINCIC)
    {
        printf("CIC inválido! (Digite apenas um valor acima de %d) Digite novamente:", MINCIC);
        return 1;
    }

    // Se chegar ao final da função, o CIC é válido
    return 0;
}

// Função       : validaNomeCompleto
// Objetivo     : Validar o nome completo do curso
// Parâmetros   : Nome completo do curso
// Saída        : 0 para válido e 1 para inválido
int validaNomeCompleto(char *nomeCompleto)
{

    if ((strlen(nomeCompleto) - 1) > MAXNOME)
    {
        printf("Nome completo do curso excede a quantidade permitida! Digite novamente:");
        return 1;
    }
    else if (nomeCompleto[0] == '\n' || nomeCompleto[0] == '\0' || nomeCompleto[0] == ' ')
    {
        printf("Nome completo do curso vazio! Digite novamente:\n");
        return 1;
    }
    else if (strlen(nomeCompleto) - 1 < MINIMO)
    {
        printf("Nome completo do curso menor que %d caracteres! Digite novamente:", MINIMO);
        return 1;
    }

    // Se chegar ao final da função, o nome completo do curso é válido
    return 0;
}

// Função       : validaSiglaEscola
// Objetivo     : Validar a sigla da escola
// Parâmetros   : Sigla da escola
// Saída        : 0 para válido e 1 para inválido
int validaSiglaEscola(char *siglaEscola)
{
    // Valida se existe algum espaço em branco na sigla da escola
    for (int i = 0; i < strlen(siglaEscola); i++)
    {
        if (siglaEscola[i] == ' ')
        {
            printf("Sigla da escola invalida! Digite novamente:");
            return 1;
        }
    }

    if (siglaEscola[0] == '\n' || siglaEscola[0] == '\0' || siglaEscola[0] == ' ')
    {
        printf("Sigla da escola vazia! Digite novamente:");
        return 1;
    }
    else if (strlen(siglaEscola) > MAXIMO)
    {
        printf("Sigla da escola excede a quantidade permitida! Digite novamente:");
        return 1;
    }

    // Se chegar ao final da função, a sigla da escola é válida
    return 0;
}

// Função       : validaModalidadeCurso
// Objetivo     : Validar a modalidade do curso
// Parâmetros   : Modalidade do curso
// Saída        : 0 para válido e 1 para inválido
int validaModalidadeCurso(char modalidadeCurso)
{
    if (modalidadeCurso != 'P' && modalidadeCurso != 'S' && modalidadeCurso != 'D')
    {
        printf("Modalidade do curso invalida! Digite novamente:");
        return 1;
    }

    // Se chegar ao final da função, a modalidade do curso é válida
    return 0;
}

// ============ FIM VALIDA =============

// ========== INICIO LISTAR ==========
// Função       : listarCursos
// Objetivo     : Listar os cursos
// Parâmetros   : Arquivo binário
// Saída        : Nenhuma
void listarCursos(FILE *arquivo)
{
    char opcao;
    
    do
    {
        menuListarCursos();
        scanf(" %c", &opcao);

        switch (opcao)
        {
            case 'c':
            case 'C':
            // Crescente por nome
            limpaTela();
            ordenarCursosCrescente(vetorCursos);
            limparBuffer();
            pausar();
            break;

            case 'd':
            case 'D':
            // Decrescente por nome
            limpaTela();
            ordenarCursosDecrescente(vetorCursos);
            limparBuffer();
            pausar();
            break;

        case '0':
            printf("Voltando...\n");
        default:
            printf("Opcao invalida!\n");
            break;
        }

        limparBuffer();
    }
    while (opcao != '0');
}

// Função       : criarVetorCursos
// Objetivo     : Criar um vetor com os cursos do arquivo
// Parâmetros   : Vetor de cursos e arquivo binário
// Saída        : Nenhuma
void criarVetorCursos(curso *vetorCursos, FILE *arquivo)
{
    // Abre o arquivo para leitura
    arquivo = fopen("cursos.bin", "rb");
    // vai para o início do arquivo
    rewind(arquivo);

    // Verifica se o arquivo está vazio
    fseek(arquivo, 0, SEEK_END);
    if (ftell(arquivo) == 0)
    {
        printf("Arquivo vazio!\n");
        return;
    }

    // Vai para o início do arquivo
    rewind(arquivo);

    // Lê os cursos do arquivo e armazena no vetor
    int i = 0;
    while (fread(&vetorCursos[i], sizeof(curso), 1, arquivo))
    {
        i++;
    }

    // Fecha o arquivo
    fclose(arquivo);
}


// Função: exibirTabela
// Objetivo: Exibir os cursos em forma de tabela
// Parâmetros: Vetor de cursos e tamanho do vetor
// Saída: Nenhuma
void exibirTabela(curso *vetorCursos, int tamanhoVetor) {
    printf("CIC\t\tNome Completo\t\tSigla Escola\t\tModalidade\n");
    for (int i = 0; i < tamanhoVetor; i++) {
        printf("%d\t\t%s\t\t%s\t\t%s\n", vetorCursos[i].cic, vetorCursos[i].nomeCompleto, vetorCursos[i].siglaEscola, verificaModalidadeCurso(vetorCursos[i].modalidadeCurso));
    }
}

// Função: verificaModalidadeCurso
// Objetivo: Verificar a modalidade do curso (exibir como texto os valores de P, S e D)
// Parâmetros: Modalidade do curso
// Saída: Modalidade do curso
char *verificaModalidadeCurso(char modalidadeCurso)
{
    if (modalidadeCurso == 'P')
    {
        return "Presencial";
    }
    else if (modalidadeCurso == 'S')
    {
        return "Semipresencial";
    }
    else if (modalidadeCurso == 'D')
    {
        return "Distância";
    }
    else
    {
        return "";
    }
}
// ============ FIM LISTAR ============

// ========== INICIO SISTEMA ==========
// Função       : menu
// Objetivo     : Mostrar o menu
// Parâmetros   : Nenhum
// Saída        : Nenhuma
void menu()
{
    printf("========================================\n");
    printf("====== CURSOS PROFISSIONALIZANTES ======\n");
    printf("========================================\n");

    printf("1 - Cadastrar curso\n");
    printf("2 - Editar curso\n");
    printf("3 - Listar cursos\n");
    printf("4 - Pesquisar curso por modalidade\n");
    printf("5 - Excluir curso\n");
    printf("0 - Sair\n");
    printf("Digite a opção desejada: ");
}

// Função: menuListarCursos
// Objetivo: Mostrar o menu de listar cursos
// Parâmetros: Nenhum
// Saída: Nenhuma
void menuListarCursos()
{
    limpaTela();

    printf("========================================\n");
    printf("========== LISTAR CURSOS ===============\n");
    printf("========================================\n");
    printf("C - Crescente por Nome\n");
    printf("D - Decrescente por Nome\n");
    printf("0 - Voltar\n");
    printf("Digite a opção desejada: ");
}

// Função       : menuEditarCurso
// Objetivo     : Mostrar o menu de editar curso
// Parâmetros   : Nenhum
// Saída        : Nenhuma
void menuEditarCurso()
{
    printf("Indique o campo a ser editado:\n");
    printf("1 - Nome do curso.\n");
    printf("2 - Sigla da escola.\n");
    printf("3 - Modalidade do curso.\n");
    printf("4 - Excluir este registro.\n");
    printf("0 - Voltar.\n");
    printf("Digite a opção desejada: ");
}

// Função       : limpaTela
// Objetivo     : Limpar a tela
// Parâmetros   : Nenhum
// Saída        : Nenhuma
void limpaTela()
{
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

// Função : limparBuffer (substitui o fflush(stdin))
// Objetivo : Limpar o buffer do teclado
// Parâmetros : Nenhum
// Saída : Nenhuma
void limparBuffer()
{
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    setbuf(stdin, NULL);
#endif

#if defined(_WIN32) || defined(_WIN64)
    fflush(stdin);
#endif
}

// Função       : pausar
// Objetivo     : Pausar o sistema
// Parâmetros   : Nenhum
// Saída        : Nenhuma
void pausar()
{
    printf("\nPressione qualquer tecla para continuar...\n");
    getchar();
}

// Função       : continuar
// Objetivo     : Perguntar se o usuário quer continuar
// Parâmetros   : Nenhum
// Saída        : 1 para sim e 0 para não
int continuar()
{
    char opcao;

    printf("\nDeseja continuar? (S/N): ");
    scanf(" %c", &opcao);

    if (opcao == 'S' || opcao == 's')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Função       : dormir
// Objetivo     : Pausar o sistema por alguns segundos
// Parâmetros   : Número de segundos
// Saída        : Nenhuma
void dormir(int segundos)
{
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    sleep(segundos);
#endif

#if defined(_WIN32) || defined(_WIN64)

    Sleep(segundos * 1000);
#endif
}

// Função       : localizacao
// Objetivo     : Definir a localização do sistema
// Parâmetros   : Nenhum
// Saída        : Nenhuma
void localizacao()
{
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    setlocale(LC_ALL, "pt_BR.UTF-8");
#endif

#if defined(_WIN32) || defined(_WIN64)
    setlocale(LC_ALL,"");
#endif
}

// ============ FIM SISTEMA ============

// ========== INICIO ARQUIVO ===========

// Função       : criarArquivo
// Objetivo     : Criar o arquivo binário
// Parâmetros   : Nenhum
// Saída        : Nenhuma
void criarArquivo()
{
    FILE *arquivo;

    arquivo = fopen("cursos.bin", "wb");
    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo!\n");
        exit(1);
    }
    fclose(arquivo);
}

// Função: apagarArquivo
// Objetivo: Apagar o arquivo binário
// Parâmetros: Nenhum
// Saída: Nenhuma
int apagarArquivo()
{
    printf("Você tem certeza que deseja apagar o arquivo? Todos os dados serão perdidos!\n");
    if (continuar())
    {
        remove("cursos.bin");
        printf("Removendo . . .\n");
        dormir(1);
        printf("Arquivo apagado com sucesso!\n");
        dormir(1);
        return 1;
    }
    else
    {
        printf("Voltando...\n");
        dormir(1);
        return 0;
    }
}

// ============ FIM ARQUIVO ============