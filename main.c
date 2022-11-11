#include <stdio.h>
#include <stdlib.h>

#include "alelo.h"
#include "cromossomo.h"

#define TAMCROMOSSOMO 5 // comprimento do vetor 'genes' de cada cromossomo

#define POPINICIAL 100 // tamanho da populacao inicial
#define NUMGERACOES 50 // qtd de geracoes do algoritmo

typedef struct _cromossomo_{
    int chave;
    int *genes;
    int pontuacao;
} Cromossomo;

int geracao_atual = 1; // valor para guardar a geracao atual durante a execucao do algoritmo

int main()
{
    time_t t;
    srand((unsigned) time(&t));

    Cromossomo *crom1 = construir_cromossomo(TAMCROMOSSOMO);
    Cromossomo *crom2 = construir_cromossomo(TAMCROMOSSOMO);

    /*printf("%d\n", crom1->chave);
    printf("%d\n", crom2->chave);*/

    return 0;
}
