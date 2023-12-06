//  Objetivo: ordenar os funcionarios de acordo com os meses que se passaram desde a contraçao
//  Entrada : matricula do funcionário, periodo de trabalho
//  Saída   : lista ordenada dos mais recentes aos mais antigos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX 100

// PROTOTIPOS
int validaMatricula(int matricula[], int contador);
int validaMatriculaRepetida(int matricula[], int contador);

int main()
{
    int matricula[MAX], mesesContratados[MAX], tamanhoTotal = 100, contador = 0, funcionario = 0;
    setlocale(LC_ALL, "pt_BR.UTF-8");

    do
    {
        printf("Informe a matrícula do funcionário numero %d (digite '0' para encerrar) : ", contador + 1);
        scanf("%d", matricula[contador]);
		matricula[contador] = validaMatricula(matricula, contador);
        contador++;
    } while ((contador <= tamanhoTotal - 1) && (matricula[contador - 1] != 0));
    return 0;
}

/*------SUBALGORITMOS ---------*/
// Objetivo: Validar matricula
// Parametros: matricula e contador
// Retorno: matricula valida
int validaMatricula(int matricula[], int contador)
{
    while (matricula[contador] < 0)
    {
        printf("Matrícula inválida, por favor verifique e digite novamente: ");
        scanf(matricula[contador]);
    }

    matricula[contador] = validaMatriculaRepetida(matricula, contador);

    return matricula[contador];
}

// Objetivo: verificar se há alguma matricula repetida
// Parametros: matricula e contador
// Retorno: matricula exclusiva
int validaMatriculaRepetida(int matricula[], int contador)
{
    // Declarações
    int indice = 0;

    if (contador != 0)
    {
        do
        {
            if (matricula[contador] == matricula[indice])
            {
                while (matricula[contador] == matricula[indice])
                {
                    printf("Matrícula repetida, por favor digite uma matrícula diferente");
                    scanf("%d", matricula[contador]);
                    indice = 0;
                }
            }

            indice++;
        } while (indice < contador);
    }

    return matricula[contador];
}
