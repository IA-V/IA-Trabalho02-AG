#include "populacao.h"
#include "cromossomo.h"
#include "alelo.h"

#include <stdlib.h>
#include <time.h>

int gerar_alelo(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

int *gerar_populacao_inicial(int tam_pop, int tamanho_cromossomo)
{
    Cromossomo **populacao = (Cromossomo **)malloc(tam_pop * sizeof(Cromossomo *));

    for(int i = 0; i < tam_pop; i++)
    {
        populacao[i] = construir_cromossomo(tamanho_cromossomo);

        populacao[i]->genes[0] = gerar_alelo(1, 5);
        populacao[i]->genes[1] = gerar_alelo(6, 10);
        populacao[i]->genes[2] = gerar_alelo(11, 15);
        populacao[i]->genes[3] = gerar_alelo(16, 20);
        populacao[i]->genes[4] = gerar_alelo(21, 25);
    }
}
