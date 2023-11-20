// ========== Trabalho Final -  TEMA 2 - CURSOS PROFISSIONALIZANTES  ==========
// Aluno : Luiz Henrique Guimarães Soares - 222022144
// Realizado no Sistema Operacional Ubuntu 22.04 LTS

// Objetivo: Gerenciar cursos profissionalizantes oferecidos a jovens carentes no Distrito Federal,
// permitindo o cadastro, edição, listagem, pesquisa por modalidade e exclusão de cursos,
// com armazenamento em um arquivo binário.

// Entrada:
// - Dados para cadastrar um curso: Código de Identificação do Curso (CIC), Nome Completo do Curso,
// - Sigla da Escola e Modalidade do Curso.
// - Opções do menu escolhidas pelo usuário.

// Saída:
// - Relatórios tabelares ordenados alfabeticamente com informações dos cursos.
// - Mensagens de confirmação, cancelamento ou erro.
// - Atualização do arquivo binário (cursos.bin) ao encerrar o programa.

// ============================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXIMO 5
#define MINIMO 5
#define MINCIC 10
#define MAXCURSOS 100
#define MAXNOME 150

// Struct para armazenar os dados de cada curso
typedef struct
{
    int cic;                        // Código de Identificação do Curso
    char nomeCompleto[MAXNOME];         // Nome completo do curso
    char siglaEscola[MAXIMO];       // Sigla da escola
    char modalidadeCurso;           // Modalidade do curso com char
} curso;

// ========== PROTÓTIPOS  ==========
int validaCic(int cic);
int validaNomeCompleto(char *nomeCompleto);
int validaSiglaEscola(char *siglaEscola);
int validaModalidadeCurso(char modalidadeCurso);

// ========== SUBALGORITMOS  ==========

// ========== INICIO LEITURA ==========

// Função       : lerCic
// Objetivo     : Ler o CIC do curso
// Parâmetros   : Nenhum
// Saída        : CIC do curso
int lerCic()
{
    int cic;    // Código de Identificação do Curso
    do
    {
        fflush(stdin);
        scanf("%d", &cic);
    }
    while (validaCic(cic));

    return cic;
}

// Função       : lerNomeCompleto
// Objetivo     : Ler o nome completo do curso
// Parâmetros   : Nenhum
// Saída        : Nome completo do curso
char* lerNomeCompleto()
{
    char nomeCompleto[MAXNOME];    // Nome completo do curso

    do
    {
        fflush(stdin);
        fgets(nomeCompleto, MAXNOME, stdin);
    }
    while (validaNomeCompleto(nomeCompleto));

    return nomeCompleto;
}

// Função       : lerSiglaEscola
// Objetivo     : Ler a sigla da escola
// Parâmetros   : Nenhum
// Saída        : Sigla da escola
char* lerSiglaEscola()
{
    char siglaEscola[MAXIMO];    // Sigla da escola
    do
    {
        fflush(stdin);
        scanf("%s", siglaEscola);
    }
    while (validaSiglaEscola(siglaEscola));

    return siglaEscola;
}


// Função       : lerModalidadeCurso
// Objetivo     : Ler a modalidade do curso
// Parâmetros   : Nenhum
// Saída        : Modalidade do curso
char lerModalidadeCurso()
{
    char modalidadeCurso;    // Modalidade do curso

    do
    {
        fflush(stdin);
        scanf("%c", &modalidadeCurso);
    }
    while (validaModalidadeCurso(modalidadeCurso));

    return modalidadeCurso;
}

// ========== FIM LEITURA ==========

// ========== INICIO VALIDAÇÃO ==========

// Função       : validaCic
// Objetivo     : Validar o CIC do curso
// Parâmetros   : CIC do curso
// Saída        : 0 para válido e 1 para inválido
int validaCic(int cic)
{
    return (cic < MINCIC) ? 1 : 0;
}

// Função       : validaNomeCompleto
// Objetivo     : Validar o nome completo do curso
// Parâmetros   : Nome completo do curso
// Saída        : 0 para válido e 1 para inválido
int validaNomeCompleto(char *nomeCompleto)
{
    return (strlen(nomeCompleto) < MINIMO || strlen(nomeCompleto) > MAXNOME || nomeCompleto[0] == '\n') ? 1 : 0;
}

// Função       : validaSiglaEscola
// Objetivo     : Validar a sigla da escola
// Parâmetros   : Sigla da escola
// Saída        : 0 para válido e 1 para inválido
int validaSiglaEscola(char *siglaEscola)
{

    return (strlen(siglaEscola) > MAXIMO || siglaEscola[0] == '\n') ? 1 : 0;
}

// Função       : validaModalidadeCurso
// Objetivo     : Validar a modalidade do curso
// Parâmetros   : Modalidade do curso
// Saída        : 0 para válido e 1 para inválido
int validaModalidadeCurso(char modalidadeCurso) {
    return (modalidadeCurso != 'P' && modalidadeCurso != 'T' && modalidadeCurso != 'E') ? 1 : 0;
}

// ========== FIM VALIDAÇÃO ==========


// ========== INICIO CADASTRO ==========

// Função       : cadastrarCurso
// Objetivo     : Cadastrar um curso
// Parâmetros   : Nenhum
// Saída        : Nenhuma
curso cadastrarCurso()
{
    curso novoCurso;    // Array de cursos

    // ========== CIC ==========
    printf("Digite o CIC do curso: ");
    novoCurso.cic = lerCic();

    // ========== NOME COMPLETO ==========
    printf("Digite o nome completo do curso: ");
    novoCurso.nomeCompleto[MAXNOME] = lerNomeCompleto();

    // ========== SIGLA DA ESCOLA ==========
    printf("Digite a sigla da escola: ");
    novoCurso.siglaEscola[MAXIMO] = lerSiglaEscola();

    // ========== MODALIDADE DO CURSO ==========
    printf("Digite a modalidade do curso: ");
    novoCurso.modalidadeCurso = lerModalidadeCurso();

    return novoCurso;
}

// ========== FIM CADASTRO ==========


// ========== MAIN ==========
int main()
{
    curso cursos[MAXCURSOS];            // Array de cursos
    int opcao;                          // Opção do menu
    int numCurso = 0;                   // Número de cursos cadastrados

    do
    {
        // ========== MENU ==========
        printf("1 - Cadastrar curso\n");
        printf("2 - Editar curso\n");
        printf("3 - Listar cursos\n");
        printf("4 - Pesquisar curso por modalidade\n");
        printf("5 - Excluir curso\n");
        printf("0 - Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        // ========== SWITCH ==========
        switch (opcao)
        {
        case 1:
            cursos[numCurso] = cadastrarCurso();
            numCurso++;
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
        fflush(stdin);
    }
    while (opcao != 0);

    return 0;
}