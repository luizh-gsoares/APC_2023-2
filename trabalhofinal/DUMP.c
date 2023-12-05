// Protótipos das funções de edição
void editarCurso(curso *cursos, int cont);
int verificaPosicaoCic(int cic, curso *cursos);

// Protótipos das funções de listagem
void listarCursos(curso *cursos, int cont);
void exibirCursosCrescente(curso *cursos, int cont);
void exibirCursosDecrescente(curso *cursos, int cont);
void exibirTabela(curso *cursos, int cont);
char *verificaModalidadeCurso(char modalidadeCurso);



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

    pausar();
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
