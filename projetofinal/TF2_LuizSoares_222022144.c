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

    #define MINCIC 10
    #define MAXIMO 5

    // Enumeração para representar a modalidade do curso (Questionar se pode ser utilizado no TF...)
    enum modalidade {
        presencial = 'P',
        semipresencial = 'S',
        distancia = 'D'
    };

    // Struct para armazenar os dados de cada curso
    struct curso {
        int CIC;                        // Código de Identificação do Curso
        char nomeCompleto[150];          // Nome completo do curso
        char siglaEscola[MAXIMO];       // Sigla da escola
        enum modalidade modalidade;     // Modalidade do curso com enum
        char modalidadeCurso[1];        // Modalidade do curso com char
    };

    // ========== MAIN ==========
    int main()
    {
        // Definindo a quantidade máxima de cursos e valores fixos da posição 0.
        struct curso Cursos[1];
        Cursos[0].CIC = 1234567890;
        strcpy(Cursos[0].nomeCompleto, "Algoritmo e Programação de Computadores");
        strcpy(Cursos[0].siglaEscola, "UnB");

        // TODO : Questionar qual modalidades é o mais adequado para    utilizar
        strcpy(Cursos[0].modalidadeCurso, "P");
        Cursos[0].modalidade = presencial;

        // Exemplo de como acessar os dados do curso
        printf("CIC: %d\n", Cursos[0].CIC);
        printf("Nome do Curso: %s\n", Cursos[0].nomeCompleto);
        printf("Sigla da Escola: %s\n", Cursos[0].siglaEscola);
        printf("Modalidade: %c\n", Cursos[0].modalidade);
        printf("Modalidade: %s\n", Cursos[0].modalidadeCurso);

        return 0;
    }







































    // ========== SUBPROGRAMAS  ==========
    // Função       :
    // Objetivo     :
    // Parâmetros   :
    // Saída        :