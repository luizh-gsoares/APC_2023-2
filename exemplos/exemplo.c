#include<stdio.h>
#include<conio.h>

int main() {
    // Declarações
    int aux, *pAux;

    // Intruções
    aux = 5;
    pAux = &aux;
    *pAux = *pAux * aux;

    if (*pAux == 5) {
        puts("Correto");
        printf("Aux = %d\n", aux);
        printf("Apontamento = %p\n", (void *)*pAux);
    } else {
        puts("Incorreto");
        printf("Ponteiro = %p\n", (void *)pAux);
        printf("Endereco Aux = %p\n", (void *)&aux);
        printf("Endereco Ponteiro = %p\n", (void *)&pAux);
    }

    getch();
    return 0;
}
