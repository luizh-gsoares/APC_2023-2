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

#define MAXIMO 5
#define MINIMO 5
#define MINCIC 10
#define MAXCURSOS 100
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
void inicializarVetor(curso *cursos);
void limpaTela();
void limparBuffer();
void pausar();

// Protótipos das funções de validação
int validaCic(int cic, curso *cursos, int cont);
int validaNomeCompleto(char *nomeCompleto);
int validaSiglaEscola(char *siglaEscola);
int validaModalidadeCurso(char modalidadeCurso);

// Protótipos das funções de leitura de dados
void lerCic(int *cic, curso *cursos, int cont);
void lerNomeCompleto(char *nomeCompleto);
void lerSiglaEscola(char *siglaEscola);
void lerModalidadeCurso(char *modalidadeCurso);

// Protótipos das funções de cadastro
curso cadastrarCurso(curso *cursos, int *cont);

// Protótipos das funções de edição
void editarCurso(curso *cursos, int cont);
int verificaPosicaoCic(int cic, curso *cursos);

// Protótipos das funções de listagem
void listarCursos(curso *cursos, int cont);
void exibirCursosCrescente(curso *cursos, int cont);
void exibirCursosDecrescente(curso *cursos, int cont);
void exibirTabela(curso *cursos, int cont);
char *verificaModalidadeCurso(char modalidadeCurso);

// ==========================
// ========== MAIN ==========
// ==========================
int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    curso cursos[MAXCURSOS]; // Array de cursos
    int opcao;               // Opção do menu
    int cont = 0;            // Contador de cursos cadastrados

    inicializarVetor(cursos);

    do
    {
        limpaTela();
        menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // Loop para cadastrar cursos enquanto o usuário quiser
            do
            {
                limparBuffer();
                cursos[cont] = cadastrarCurso(cursos, &cont);
                cont++;
            } while (continuar());
            break;
        case 2:
            limparBuffer();

            if (verificaContadorZero(cont))
                editarCurso(cursos, cont);
            else
                printf("Nao ha cursos cadastrados!\n");

            pausar();
            break;
        case 3:
            limparBuffer();

            if (verificaContadorZero(cont))
                listarCursos(cursos, cont);
            else
                printf("Nao ha cursos cadastrados!\n");

            pausar();
            break;
        case 4:
            limparBuffer();

            if (verificaContadorZero(cont))
                pesquisarCursoModalidade(cursos, cont);
            else
                printf("Nao ha cursos cadastrados!\n");

            pausar();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}

// ====================================
// ========== SUBALGORITMOS  ==========
// ====================================

// ========== INICIO CADASTRO ==========

// Função: cadastrarCurso
// Objetivo: Cadastrar um curso
// Parâmetros: Array de cursos e contador de cursos cadastrados
// Saída: Curso cadastrado
curso cadastrarCurso(curso *cursos, int *cont)
{
    curso novoCurso; // Novo curso a ser cadastrado

    limpaTela();

    printf("=======================================\n");
    printf("========== CADASTRO DE CURSO ==========\n");
    printf("=======================================\n");

    // CIC
    printf("Digite o CIC do curso (Valor acima de %d): ", MINCIC);
    lerCic(&novoCurso.cic, cursos, *cont);

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

// ========== INICIO EDITAR ==========
// Função: editarCurso
// Objetivo: Editar um curso
// Parâmetros: Array de cursos e contador de cursos cadastrados
// Saída: Nenhuma
void editarCurso(curso *cursos, int cont)
{
    int cic;       // CIC do curso a ser editado
    int posicao;   // Posição do curso no array
    int opcao = 1; // Opção do menu

    // Exibir os cursos cadastrados
    limpaTela();
    exibirCursosCrescente(cursos, cont);
    pausar();

    // Ler o CIC do curso a ser editado
    printf("Digite o CIC do curso a ser editado ou 0 para voltar: ");
    scanf("%d", &cic);
    posicao = verificaPosicaoCic(cic, cursos);

    if (posicao != -1 && cic != 0)
    {
        // Menu de opções
        limpaTela();
        printf("=======================================\n");
        printf("Curso encontrado!\n");
        printf("CIC:\t%d\n", cursos[posicao].cic);
        printf("Nome completo:\t%s\n", cursos[posicao].nomeCompleto);
        printf("Sigla da escola:\t%s\n", cursos[posicao].siglaEscola);
        printf("Modalidade do curso:\t%s\n", verificaModalidadeCurso(cursos[posicao].modalidadeCurso));
        printf("=======================================\n");

        menuEditarCurso();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o novo nome completo do curso: ");
            lerNomeCompleto(cursos[posicao].nomeCompleto);
            break;

        case 2:
            printf("Digite a nova sigla da escola: ");
            lerSiglaEscola(cursos[posicao].siglaEscola);
            break;

        case 3:
            printf("Digite a nova modalidade do curso: ");
            lerModalidadeCurso(&cursos[posicao].modalidadeCurso);
            break;

        case 4:
            printf("Você tem certeza que deseja excluir este registro? (S/N): ");
            char opcao;
            scanf(" %c", &opcao);

            if (opcao == 'S' || opcao == 's')
            {
                printf("Excluindo curso...\n");
                sleep(1);

                // Excluir o curso
                cursos[posicao].cic = 0;
                cursos[posicao].nomeCompleto[0] = '\0';
                cursos[posicao].siglaEscola[0] = '\0';
                cursos[posicao].modalidadeCurso = '\0';

                // Diminuir o contador de cursos cadastrados
                cont--;
                break;
            }
            else
            {
                printf("Voltando...\n");
                sleep(1);
                break;
            }
        case 0:
            printf("Voltando...\n");
            sleep(1);
            break;

        default:
            printf("Opcao invalida! Nenhuma alteração será realizada.\n");
            printf("Voltando...\n");
            sleep(2);
            break;
        }
    }
    else
    {
        printf("Curso nao encontrado ou foi pressionado 0 para voltar! Voltando para o menu anterior...\n");
        sleep(2);
    }
}

// Função: verificaPosicaoCic
// Objetivo: Verificar a posição do curso no array
// Parâmetros: CIC do curso e array de cursos
// Saída: Posição do curso no array
int verificaPosicaoCic(int cic, curso *cursos)
{
    for (int i = 0; i < MAXCURSOS - 1; i++)
    {
        if (cursos[i].cic == cic)
        {
            return i;
        }
    }

    printf("CIC do curso nao encontrado!\n");
    return -1;
}

// =========== FIM EDITAR =============

// ========== INICIO PESQUISAR ==========
// Função: pesquisarCurso
// Objetivo: Pesquisar um curso por modalidade
// Parâmetros: Array de cursos e contador de cursos cadastrados
// Saída: Nenhuma
void pesquisarCursoModalidade(curso *cursos, int cont)
{
    char modalidade; // Modalidade do curso
    int encontrou = 0;

    printf("Digite a modalidade do curso (P - Presencial, S - Semipresencial, D - Distância): ");
    lerModalidadeCurso(&modalidade);

    // Exibir os cursos cadastrados
    limpaTela();

    printf("CIC\t\tNome Completo\t\tSigla da Escola\t\tModalidade do Curso\n");
    for (int i = 0; i < cont; i++)
    {
        if (cursos[i].modalidadeCurso == modalidade)
        {
            printf("%d\t\t%s\t\t%s\t\t%s\n", cursos[i].cic, cursos[i].nomeCompleto, cursos[i].siglaEscola, verificaModalidadeCurso(cursos[i].modalidadeCurso));
            encontrou = 1;
        }
    }

    if (!encontrou)
    {
        printf("Nenhum curso encontrado!\n");
    }
}

// =========== FIM PESQUISAR =============

// ========== INICIO LISTAR ===========

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
        return "Modalidade inválida";
    }
}

// TODO : Arrumar exibição em tabela
// Função: exibirTabela
// Objetivo: Exibir os cursos em forma de tabela
// Parâmetros: Array de cursos e contador de cursos cadastrados
// Saída: Nenhuma
void exibirTabela(curso *cursos, int cont)
{
    printf("CIC\t\tNome Completo\t\tSigla da Escola\t\tModalidade do Curso\n");
    for (int i = 0; i < cont; i++)
        printf("%d\t\t%s\t\t%s\t\t%s\n", cursos[i].cic, cursos[i].nomeCompleto, cursos[i].siglaEscola, verificaModalidadeCurso(cursos[i].modalidadeCurso));
}

// Função: listarCursos
// Objetivo: Listar os cursos
// Parâmetros: Nenhum
// Saída: Nenhuma
void listarCursos(curso *cursos, int cont)
{
    int opcao;

    do
    {
        menuListarCursos();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            limpaTela();
            exibirCursosCrescente(cursos, cont);
            limparBuffer();
            pausar();
            break;

        case 2:
            limpaTela();
            exibirCursosDecrescente(cursos, cont);
            limparBuffer();
            pausar();
            break;

        case 3:
            limpaTela();
            ordenarNomeCrescente(cursos, cont);
            limparBuffer();
            pausar();
            break;

        case 4:
            limpaTela();
            ordenarNomeDecrescente(cursos, cont);
            limparBuffer();
            pausar();
            break;

        case 0:
            printf("Voltando...\n");
            sleep(1);
            break;

        default:
            printf("Opcao invalida!\n");
            limparBuffer();
            break;
        }
    } while (opcao != 0);
}

// ============ FIM LISTAR =============

// ============ INICIO LER ============

// Função: lerCic
// Objetivo: Ler o CIC do curso
// Parâmetros: Ponteiro para armazenar o CIC do curso, array de cursos e contador de cursos cadastrados
// Saída: Nenhuma
void lerCic(int *cic, curso *cursos, int cont)
{
    do
    {
        limparBuffer();
        scanf("%d", cic);
    } while (validaCic(*cic, cursos, cont));
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
        // removerTerminador(nomeCompleto);
    } while (validaNomeCompleto(nomeCompleto));
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
        scanf("%s", siglaEscola);
        // removerTerminador(siglaEscola);
    } while (validaSiglaEscola(siglaEscola));
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

    } while (validaModalidadeCurso(*modalidadeCurso));
}

// ============= FIM LER =============

// ========== INICIO VALIDA ==========

// Função       : validaCic
// Objetivo     : Validar o CIC do curso
// Parâmetros   : CIC do curso, array de cursos e contador de cursos cadastrados
// Saída        : 0 para válido e 1 para inválido
int validaCic(int cic, curso *cursos, int cont)
{
    if (cic < MINCIC)
    {
        printf("CIC do curso menor que %d! Digite novamente:", MINCIC);
        return 1;
    }

    // Verifica se o CIC do curso já existe
    for (int i = 0; i < cont; i++)
    {
        if (cursos[i].cic == cic)
        {
            printf("CIC do curso ja existe! Digite novamente:");
            return 1;
        }
    }

    // Se chegar ao final da função, o CIC do curso é válido
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

    // Valida se existe algum espaço em branco na sigla da escola
    for (int i = 0; i < strlen(siglaEscola) - 1; i++)
    {
        if (siglaEscola[i] == ' ')
        {
            printf("Sigla da escola invalida (espaços em branco)! Digite novamente:");
            return 1;
        }
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

    return 0;
}

// Função       : verificaContadorZero
// Objetivo     : Verificar o contador se não há cursos cadastrados
// Parâmetros   : Contador de cursos cadastrados
// Saída        : 0 sem cadastro e 1 com cadastro
int verificaContadorZero(int cont)
{
    return (cont == 0) ? 0 : 1;
}

// ============ FIM VALIDA =============

// ============= ORDENAR ===============

// Função: exibirCursosCrecente
// Objetivo: Exibir os cursos em ordem crescente
// Parâmetros: Array de cursos e contador de cursos cadastrados
// Saída: Nenhuma
void exibirCursosCrescente(curso *cursos, int cont)
{
    // Ordenar os cursos em ordem crescente por CIC (Bubble Sort)
    for (int i = 0; i < cont - 1; i++)
    {
        for (int j = 0; j < cont - i - 1; j++)
        {
            if (cursos[j].cic > cursos[j + 1].cic)
            {
                // Troca de posições
                curso temp = cursos[j];
                cursos[j] = cursos[j + 1];
                cursos[j + 1] = temp;
            }
        }
    }

    // Exibir os cursos ordenados
    printf("Cursos por CIC ASC:\n");
    exibirTabela(cursos, cont);
}

// Função: exibirCursosDecrecente
// Objetivo: Exibir os cursos em ordem decrescente
// Parâmetros: Array de cursos e contador de cursos cadastrados
// Saída: Nenhuma
void exibirCursosDecrescente(curso *cursos, int cont)
{
    // Ordenar os cursos em ordem decrescente por CIC (Bubble Sort)
    for (int i = 0; i < cont - 1; i++)
    {
        for (int j = 0; j < cont - i - 1; j++)
        {
            if (cursos[j].cic < cursos[j + 1].cic)
            {
                // Troca de posições
                curso temp = cursos[j];
                cursos[j] = cursos[j + 1];
                cursos[j + 1] = temp;
            }
        }
    }

    // Exibir os cursos ordenados
    printf("Cursos por CIC DESC:\n");
    exibirTabela(cursos, cont);
}

// Função: ordenarCursosCrecente
// Objetivo: Ordenar os cursos em ordem crescente (A-Z)
// Parâmetros: Array de cursos e contador de cursos cadastrados
// Saída: Nenhuma
void ordenarNomeCrescente(curso *cursos, int cont)
{
    // Ordenar os cursos em ordem crescente por nome completo (Bubble Sort)
    for (int i = 0; i < cont - 1; i++)
    {
        for (int j = 0; j < cont - i - 1; j++)
        {
            if (strcmp(cursos[j].nomeCompleto, cursos[j + 1].nomeCompleto) > 0)
            {
                // Troca de posições
                curso temp = cursos[j];
                cursos[j] = cursos[j + 1];
                cursos[j + 1] = temp;
            }
        }
    }

    // Exibir os cursos ordenados
    printf("Cursos (A-Z) por Nome ASC:\n");
    exibirTabela(cursos, cont);
}

// Função: ordenarCursosDecrecente
// Objetivo: Ordenar os cursos em ordem decrescente (Z-A)
// Parâmetros: Array de cursos e contador de cursos cadastrados
// Saída: Nenhuma
void ordenarNomeDecrescente(curso *cursos, int cont)
{
    // Ordenar os cursos em ordem decrescente por nome completo (Bubble Sort)
    for (int i = 0; i < cont - 1; i++)
    {
        for (int j = 0; j < cont - i - 1; j++)
        {
            if (strcmp(cursos[j].nomeCompleto, cursos[j + 1].nomeCompleto) < 0)
            {
                // Troca de posições
                curso temp = cursos[j];
                cursos[j] = cursos[j + 1];
                cursos[j + 1] = temp;
            }
        }
    }

    // Exibir os cursos ordenados
    printf("Cursos (Z-A) por Nome DESC:\n");
    exibirTabela(cursos, cont);
}

// ============ FIM ORDENAR ============

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

    printf("1 - Crescente por CIC\n");
    printf("2 - Decrescente por CIC\n");
    printf("3 - Crescente por Nome\n");
    printf("4 - Decrescente por Nome\n");
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

// Função       : inicializarVetor
// Objetivo     : Inicializar o vetor
// Parâmetros   : Vetor de cursos
// Saída        : Nenhuma
void inicializarVetor(curso *cursos)
{
    for (int i = 0; i < MAXCURSOS - 1; i++)
    {
        cursos[i].cic = 0;
        cursos[i].nomeCompleto[0] = '\0';
        cursos[i].siglaEscola[0] = '\0';
        cursos[i].modalidadeCurso = '\0';
    }
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

// Função: dormir
// Objetivo: Dormir o sistema por um determinado tempo
// Parâmetros: Tempo em segundos
// Saída: Nenhuma
void dormir(int tempo)
{
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    sleep(tempo);
#endif

#if defined(_WIN32) || defined(_WIN64)
    Sleep(tempo * 1000);
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
// ============ FIM SISTEMA ============
