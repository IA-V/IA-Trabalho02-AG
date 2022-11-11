#include "cromossomo.h"
#include <stdlib.h>

int contador_chave = 1; // guarda o valor da ultima chave gerada

typedef struct _cromossomo_{
    int chave;
    int *genes; // cor, nacionalidade, bebida, cigarro, animal
    int pontuacao;
} Cromossomo;

// Aloca memoria para um cromossomo (genes e chave)
Cromossomo *construir_cromossomo(int tamanho_cromossomo)
{
    Cromossomo *cromossomo = (Cromossomo *)malloc(sizeof(Cromossomo));
    cromossomo->genes = (int *)malloc(tamanho_cromossomo * sizeof(int));
    cromossomo->chave = contador_chave;
    cromossomo->pontuacao = 0;

    contador_chave++;
    return cromossomo;
}
