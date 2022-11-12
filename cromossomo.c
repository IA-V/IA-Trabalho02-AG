#include "cromossomo.h"
#include <stdlib.h>

int contador_chave = 1; // guarda o valor da ultima chave gerada

typedef struct _cromossomo_{
    int chave;
    int **genes; // cor, nacionalidade, bebida, cigarro, animal
    int pontuacao;
} Cromossomo;

int gerar_pts_aleatoria(int lower, int upper) // serve apenas para testar as opera��es geneticas
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
        cromossomo->genes[i][0] = gerar_alelo(1, 5);
        cromossomo->genes[i][1] = gerar_alelo(6, 10);
        cromossomo->genes[i][2] = gerar_alelo(11, 15);
        cromossomo->genes[i][3] = gerar_alelo(16, 20);
        cromossomo->genes[i][4] = gerar_alelo(21, 25);
    }
    cromossomo->chave = contador_chave;
    cromossomo->pontuacao = gerar_pts_aleatoria(0, 15); // apenas para teste

    contador_chave++;
    return cromossomo;
}
