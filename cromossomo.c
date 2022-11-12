#include "cromossomo.h"
#include <stdlib.h>

int contador_chave = 1; // guarda o valor da ultima chave gerada

typedef struct _cromossomo_{
    int chave;
    int **genes; // cor, nacionalidade, bebida, cigarro, animal
    int pontuacao;
} Cromossomo;

int gerar_pts_aleatoria(int lower, int upper) // serve apenas para testar as operações geneticas
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

// Aloca memoria para um cromossomo (genes e chave)
Cromossomo *construir_cromossomo(int tamanho_cromossomo)
{
    Cromossomo *cromossomo = (Cromossomo *)malloc(sizeof(Cromossomo));
    cromossomo->genes = (int **)malloc(tamanho_cromossomo * sizeof(int*));
    for(int i = 0; i < tamanho_cromossomo; i++)
    {
        cromossomo->genes[i] = (int *)malloc(tamanho_cromossomo * sizeof(int));
    }
    cromossomo->chave = contador_chave;
    cromossomo->pontuacao = gerar_pts_aleatoria(0, 15);

    contador_chave++;
    return cromossomo;
}
