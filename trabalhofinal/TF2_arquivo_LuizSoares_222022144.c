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

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

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
void localizacao();
void dormir(int segundos);

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

// Protótipos das funções de edição
void editarCurso(FILE *arquivo);

// Protótipos das funções de listagem
void listarCursos(FILE *arquivo);
void ordenarCursosCrescente(FILE *arquivo);
void ordenarCursosDecrescente(FILE *arquivo);
void exibirTabela(curso *vetorCursos, int tamanhoVetor);
char *verificaModalidadeCurso(char modalidadeCurso);
void criarVetorCursos(curso *vetorCursos, int tamanhoVetor, FILE *arquivo);
int definirTamanhoVetor(FILE *arquivo);

// Protótipos das funções de pesquisa
void pesquisarCursoModalidade(FILE *arquivo);

// Protótipos das funções de arquivo
void criarArquivo();

// ==========================
// ========== MAIN ==========
// ==========================
int main()
{
    int opcao;                                  // Opção do menu
    FILE *arquivo;                              // Arquivo binário
    const char *nomeArquivo = "cursos.bin";     // Nome do arquivo binário
    localizacao();                              // Define a localização do sistema (português)

if (!arquivoExiste(nomeArquivo)) 
{
        criarArquivo(nomeArquivo);
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

                // Abre o arquivo para leitura e escrita
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
            // Editar um curso
            limparBuffer();
            limpaTela();

            // abre o arquivo para leitura e escrita
            arquivo = fopen("cursos.bin", "rb+");

            // verifica se o arquivo está vazio
            fseek(arquivo, 0, SEEK_END);
            if (ftell(arquivo) == 0)
            {
                printf("Arquivo vazio!\n");
                dormir(1);
                fclose(arquivo);
                break;
            }

            // editar um curso
            editarCurso(arquivo);

            // fecha o arquivo
            fclose(arquivo);
            break;
        case 3:
            // Listar cursos
            limparBuffer();

            // verifica se o arquivo está vazio
            fseek(arquivo, 0, SEEK_END);
            if (ftell(arquivo) == 0)
            {
                printf("Arquivo vazio!\n");
                dormir(1);
                fclose(arquivo);
                break;
            }
            else
            {
                listarCursos(arquivo);
            }
            break;
        case 4:
            // Pesquisar curso por modalidade
            limparBuffer();

            // verifica se o arquivo está vazio
            fseek(arquivo, 0, SEEK_END);
            if (ftell(arquivo) == 0)
            {
                printf("Arquivo vazio!\n");
                dormir(1);
                fclose(arquivo);
                break;
            }
            else
            {
                pesquisarCursoModalidade(arquivo);
            }
            break;
        case 5:
            // Excluir arquivo e criar um novo
            limparBuffer();
            limpaTela();
            if (apagarArquivo())
            {
                criarArquivo();
            }
            break;
        case 0:
            printf("Saindo...\n");
            dormir(1);
            break;
        default:
            printf("Opcao invalida!\n");
            dormir(1);
            break;
        }

        limparBuffer();
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
    lerNomeCompleto(&novoCurso.nomeCompleto);

    // SIGLA DA ESCOLA
    printf("Digite a sigla da escola (max %d caracteres): ", MAXIMO);
    lerSiglaEscola(&novoCurso.siglaEscola);

    // MODALIDADE DO CURSO
    printf("Digite a modalidade do curso (P - Presencial, S - Semipresencial, D - Distância):");
    lerModalidadeCurso(&novoCurso.modalidadeCurso);

    return novoCurso;
}
// ============ FIM CADASTRO =============

// ========== INICIO EDITAR ==========
// Função: editarCurso
// Objetivo: Editar um curso
// Parâmetros: Arquivo binário
// Saída: Nenhuma
void editarCurso(FILE *arquivo)
{
    int cicProcurado, encontrado = 0;
    curso cursoEditado;

    // Solicita o CIC do curso que será editado
    printf("Digite o CIC do curso que deseja editar: ");
    scanf("%d", &cicProcurado);

    // Abre o arquivo para leitura e escrita
    arquivo = fopen("cursos.bin", "rb+");

    // Verifica se o arquivo existe
    if (arquivo == NULL)
    {
        printf("Arquivo nao encontrado ou vazio!\n");
        return;
    }

    // Procura o curso pelo CIC
    while (fread(&cursoEditado, sizeof(curso), 1, arquivo))
    {
        if (cursoEditado.cic == cicProcurado)
        {
            encontrado = 1;
            break;
        }
    }

    // Caso o curso seja encontrado, exibe opções de campos para edição
    if (encontrado)
    {
        int opcao;

        // Menu para escolher o campo a ser editado
        menuEditarCurso(&cursoEditado);
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            // Voltar
            printf("Voltando...\n");
            dormir(1);
            return;
        case 1:
            // Edita o nome do curso
            printf("Digite o novo nome do curso: ");
            limparBuffer();
            lerNomeCompleto(cursoEditado.nomeCompleto);
            break;
        case 2:
            // Edita a sigla da escola
            printf("Digite a nova sigla da escola: ");
            limparBuffer();
            lerSiglaEscola(cursoEditado.siglaEscola);
            break;
        case 3:
            // Edita a modalidade do curso
            printf("Digite a nova modalidade do curso (P - Presencial, S - Semipresencial, D - Distância): ");
            limparBuffer();
            lerModalidadeCurso(&cursoEditado.modalidadeCurso);
            break;
        case 4:
            // Exclui o curso
            printf("Excluindo o curso...\n");
            cursoEditado.cic = 0;
            dormir(1);
            break;
        default:
            printf("Opção inválida!\n");
            dormir(1);
            break;
        }

            // Move o cursor para a posição correspondente do curso no arquivo
            fseek(arquivo, -sizeof(curso), SEEK_CUR);

            // Sobrescreve o curso com as alterações realizadas
            fwrite(&cursoEditado, sizeof(curso), 1, arquivo);
    }
    else
    {
        printf("Curso com o CIC informado não encontrado!\n");
        dormir(1);
    }

    fclose(arquivo);
}

// Função: excluirCurso
// Objetivo: Excluir um curso
// Parâmetros: CIC do curso e arquivo binário
// Saída: Nenhuma
void excluirCurso(FILE *arquivo, int cic)
{
    curso cursos;
    FILE *tempFile;

    // Cria um arquivo temporário
    tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL)
    {
        printf("Erro ao criar arquivo temporario!\n");
        return;
    }

    // Lê os cursos do arquivo original e copia para o arquivo temporário,
    // exceto o curso com o cic a ser excluído
    while (fread(&cursos, sizeof(curso), 1, arquivo) == 1)
    {
        if (cursos.cic != cic)
        {
            fwrite(&cursos, sizeof(curso), 1, tempFile);
        }
    }

    fclose(tempFile);
    fclose(arquivo);

    // Remove o arquivo original
    remove("cursos.bin");

    // Renomeia o arquivo temporário para o nome do arquivo original
    rename("temp.bin", "cursos.bin");

    // Exibe mensagem de sucesso
    printf("Curso excluido com sucesso!\n");
}

// =========== FIM EDITAR =============

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
            fopen("cursos.bin", "rb");

            // Vai para o início do arquivo
            rewind(arquivo);

            ordenarCursosCrescente(arquivo);

            // Fecha o arquivo
            fclose(arquivo);
            break;

        case 'd':
        case 'D':
            // Decrescente por nome
            limpaTela();
            fopen("cursos.bin", "rb");

            // Vai para o início do arquivo
            rewind(arquivo);

            ordenarCursosDecrescente(arquivo);

            // Fecha o arquivo
            fclose(arquivo);
            break;

        case '0':
            printf("Voltando...\n");
            dormir(1);
            break;
        default:
            printf("Opcao invalida!\n");
            dormir(1);
            break;
        }

        limparBuffer();
    }
    while (opcao != '0');

    fclose(arquivo);
}

// Função       : criarVetorCursos
// Objetivo     : ler os cursos do arquivo binário e armazenar no vetor de cursos (struct)
// Parâmetros   : Vetor de cursos e tamanho do vetor
// Saída        : Nenhuma
void criarVetorCursos(curso *vetorCursos, int tamanhoVetor, FILE *arquivo)
{
    // Vai para o início do arquivo
    rewind(arquivo);

    // Lê os cursos do arquivo e armazena no vetor de cursos
    for (int i = 0; i < tamanhoVetor; i++)
    {
        fread(&vetorCursos[i], sizeof(curso), 1, arquivo);
    }
}

// Função       : definirTamanhoVetor
// Objetivo     : Definir o tamanho do vetor de cursos
// Parâmetros   : Arquivo binário
// Saída        : Tamanho do vetor de cursos
int definirTamanhoVetor(FILE *arquivo)
{
    // Vai para o início do arquivo
    rewind(arquivo);

    // Verifica o tamanho do arquivo
    fseek(arquivo, 0, SEEK_END);
    int tamanhoArquivo = ftell(arquivo);

    // Define o tamanho do vetor de cursos
    int tamanhoVetor = tamanhoArquivo / sizeof(curso);

    return tamanhoVetor;
}

// Função       : ordenarCursosDecrescente
// Objetivo     : Ordenar os cursos em ordem decrescente por nome
// Parâmetros   : Arquivo binário
// Saída        : Nenhuma
void ordenarCursosDecrescente(FILE *arquivo)
{
    // Define o tamanho do vetor de cursos
    int tamanhoVetor = definirTamanhoVetor(arquivo);

    // Cria o vetor de cursos
    curso vetorCursos[tamanhoVetor];

    // Cria o vetor de cursos
    criarVetorCursos(vetorCursos, tamanhoVetor, arquivo);

    // Ordena o vetor de cursos em ordem decrescente por nome (bubble sort)
    for (int i = 0; i < tamanhoVetor; i++)
    {
        for (int j = i + 1; j < tamanhoVetor; j++)
        {
            if (strcmp(vetorCursos[i].nomeCompleto, vetorCursos[j].nomeCompleto) < 0)
            {
                curso aux = vetorCursos[i];
                vetorCursos[i] = vetorCursos[j];
                vetorCursos[j] = aux;
            }
        }
    }

    // Exibe o vetor de cursos ordenado
    printf("DESC por nome:\n");
    exibirTabela(vetorCursos, tamanhoVetor);
}

// Função       : ordenarCursosCrescente
// Objetivo     : Ordenar os cursos em ordem crescente por nome
// Parâmetros   : Arquivo binário
// Saída        : Nenhuma
void ordenarCursosCrescente(FILE *arquivo)
{
    // Define o tamanho do vetor de cursos
    int tamanhoVetor = definirTamanhoVetor(arquivo);

    // Cria o vetor de cursos
    curso vetorCursos[tamanhoVetor];

    // Cria o vetor de cursos
    criarVetorCursos(vetorCursos, tamanhoVetor, arquivo);

    // Ordena o vetor de cursos em ordem crescente por nome (bubble sort)
    for (int i = 0; i < tamanhoVetor; i++)
    {
        for (int j = i + 1; j < tamanhoVetor; j++)
        {
            if (strcmp(vetorCursos[i].nomeCompleto, vetorCursos[j].nomeCompleto) > 0)
            {
                curso aux = vetorCursos[i];
                vetorCursos[i] = vetorCursos[j];
                vetorCursos[j] = aux;
            }
        }
    }

    // Exibe o vetor de cursos ordenado
    printf("ASC por nome:\n");
    exibirTabela(vetorCursos, tamanhoVetor);
}


// Função: exibirTabela
// Objetivo: Exibir os cursos em forma de tabela
// Parâmetros: Vetor de cursos e tamanho do vetor
// Saída: Nenhuma
void exibirTabela(curso *vetorCursos, int tamanhoVetor)
{
    printf("+================+=======================================================================+===============+=======================+\n");
    printf("| \tCIC\t | \tNome do Curso\t\t\t\t\t\t\t | \tSigla\t | \tModalidade \t |\n");
    printf("+================+=======================================================================+===============+=======================+\n");


    for (int i = 0; i < tamanhoVetor; i++)
    {
        // Apenas exibe os valores diferentes de 0
        if (vetorCursos[i].cic != 0)
        printf("|\t%d\t | \t%-50s\t\t | \t%-5.5s\t | \t%s\t |\n",
               vetorCursos[i].cic,
               vetorCursos[i].nomeCompleto,
               vetorCursos[i].siglaEscola,
               verificaModalidadeCurso(vetorCursos[i].modalidadeCurso));
    }

    printf("+================+=======================================================================+===============+=======================+\n");
    printf("Total de cursos: %d\n", tamanhoVetor);
    pausar();
}


// Função: verificaModalidadeCurso
// Objetivo: Verificar a modalidade do curso (exibir como texto os valores de P, S e D)
// Parâmetros: Modalidade do curso (char)
// Saída: Modalidade do curso (string)
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

// ========== INICIO PESQUISAR ==========

// Função       : pesquisarCursoModalidade
// Objetivo     : Pesquisar um curso por modalidade ordenado pela sigla da escola
// Parâmetros   : Arquivo binário
// Saída        : Nenhuma
void pesquisarCursoModalidade(FILE *arquivo)
{
    char modalidadeCurso;

    // Lê a modalidade do curso
    printf("Digite a modalidade do curso (P - Presencial, S - Semipresencial, D - Distância):");
    lerModalidadeCurso(&modalidadeCurso);

    // Abre o arquivo para leitura e escrita
    arquivo = fopen("cursos.bin", "rb");

    // Vai para o início do arquivo
    rewind(arquivo);

    // Verifica se o arquivo está vazio
    fseek(arquivo, 0, SEEK_END);
    if (ftell(arquivo) == 0)
    {
        printf("Arquivo vazio!\n");
        return;
    }
    else
    {
        // Ordena os cursos em ordem crescente por sigla e por modalidade digitada
        ordenarCursosSiglaModalidade(arquivo, modalidadeCurso);
    }

    // Fecha o arquivo
    fclose(arquivo);
}

// Função       : ordenarCursosSiglaModalidade
// Objetivo     : Ordenar os cursos em ordem crescente por sigla e por modalidade digitada
// Parâmetros   : Arquivo binário e modalidade do curso
// Saída        : Nenhuma
void ordenarCursosSiglaModalidade(FILE *arquivo, char modalidadeDigitada)
{
    int encontrado = 0;

    // Define o tamanho do vetor de cursos
    int tamanhoVetor = definirTamanhoVetor(arquivo);

    // Cria o vetor de cursos
    curso vetorCursos[tamanhoVetor];

    // Cria o vetor de cursos
    criarVetorCursos(vetorCursos, tamanhoVetor, arquivo);

    // Ordena o vetor de cursos em ordem crescente por sigla (bubble sort)
    for (int i = 0; i < tamanhoVetor; i++)
    {
        for (int j = i + 1; j < tamanhoVetor; j++)
        {
            if (strcmp(vetorCursos[i].siglaEscola, vetorCursos[j].siglaEscola) > 0)
            {
                curso aux = vetorCursos[i];
                vetorCursos[i] = vetorCursos[j];
                vetorCursos[j] = aux;
            }
        }
    }

    // Atribui 0 para os cursos que não são da modalidade digitada
    for (int i = 0; i < tamanhoVetor; i++)
    {
        if (vetorCursos[i].modalidadeCurso != modalidadeDigitada)
        {
            vetorCursos[i].cic = 0;
            break;
        }

        encontrado++;
    }

    // Exibe o vetor de cursos ordenado
    printf("ASC por sigla e modalidade %s:\n", verificaModalidadeCurso(modalidadeDigitada));
    exibirTabela(vetorCursos, tamanhoVetor);
}

// ============ FIM PESQUISAR ============

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
        fgets(nomeCompleto, MAXNOME + 2, stdin);
        removerQuebraLinha(nomeCompleto);
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
        fgets(siglaEscola, MINIMO + 2, stdin);
        removerQuebraLinha(siglaEscola);
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
        fgets(modalidadeCurso, 2, stdin);

        // transforma a modalidade do curso em maiúscula
        *modalidadeCurso = toupper(*modalidadeCurso);

    }
    while (validaModalidadeCurso(*modalidadeCurso));
}

// Função: removerQuebraLinha
// Objetivo: Remover a quebra de linha do final da string
// Parâmetros: String
// Saída: Nenhuma
void removerQuebraLinha(char *string)
{
    if (string[strlen(string) - 1] == '\n')
    {
        string[strlen(string) - 1] = '\0';
    }
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
    if (cic <= MINCIC)
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

    if (strlen(nomeCompleto) > MAXNOME)
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
    else if (nomeCompleto[strlen(nomeCompleto) - 1] == ' ')
    {
        printf("Não é permitido espaço em branco no final do nome completo do curso! Digite novamente:");
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
    printf("5 - Excluir arquivo\n");
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
void menuEditarCurso(curso *cursoEditado)
{
    printf("========================================\n");
    printf("========== CURSO ENCONTRADO ============\n");
    printf("========================================\n");
    printf("CIC: %d\n", cursoEditado->cic);
    printf("Nome completo: %s\n", cursoEditado->nomeCompleto);
    printf("Sigla da escola: %s\n", cursoEditado->siglaEscola);
    printf("Modalidade do curso: %s\n", verificaModalidadeCurso(cursoEditado->modalidadeCurso));
    printf("========================================\n");
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
// Objetivo     : Pausar o sistema até o usuário pressionar enter
// Parâmetros   : Nenhum
// Saída        : Nenhuma
void pausar()
{
    printf("\nPressione ENTER para continuar . . .\n");
    while (getchar() != '\n')
        ;
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
    setlocale(LC_ALL, "Portuguese");
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

    printf("Criando o arquivo, aguarde alguns instantes...\n");
    fclose(arquivo);
}

// Função: arquivoExiste
// Objetivo: Verificar se o arquivo existe
// Parâmetros: Nome do arquivo
// Saída: 1 para sim e 0 para não
int arquivoExiste(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo != NULL) {
        fclose(arquivo);
        return 1; // Arquivo existe
    }
    return 0; // Arquivo não existe
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
        return 1;
    }
    else
    {
        printf("Voltando . . .\n");
        dormir(1);
        return 0;
    }
}

// ============ FIM ARQUIVO ============
