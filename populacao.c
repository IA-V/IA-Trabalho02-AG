#include "populacao.h"
#include "cromossomo.h"
#include "alelo.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct _cromossomo_{
    int chave;
    int **genes;
    int pontuacao;
} Cromossomo;

// Codigo do MergeSort adaptado de https://gist.github.com/olegon/27c2a880c9b932862e60ab5eb89be5b6
void mergesort(Cromossomo **populacao, int tamanho_pop) {
  Cromossomo **c = (Cromossomo **)malloc(sizeof(Cromossomo *) * tamanho_pop);
  sort(populacao, c, 0, tamanho_pop - 1);
  free(c);
}

/*
  Dado um vetor de inteiros v e dois inteiros i e f, ordena o vetor v[i..f] em ordem crescente.
  O vetor c é utilizado internamente durante a ordenação.
*/
void sort(Cromossomo **populacao, Cromossomo **c, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(populacao, c, i, m);
  sort(populacao, c, m + 1, f);

  /* Se v[m] <= v[m + 1], então v[i..f] já está ordenado. */
  if (populacao[m]->pontuacao <= populacao[m + 1]->pontuacao) return;

  merge(populacao, c, i, m, f);
}


/*
  Dado um vetor v e três inteiros i, m e f, sendo v[i..m] e v[m+1..f] vetores ordenados,
  coloca os elementos destes vetores, em ordem crescente, no vetor em v[i..f].
*/
void merge(Cromossomo **populacao, Cromossomo **c, int i, int m, int f) {
  int z, iv = i, ic = m + 1;

  for (z = i; z <= f; z++) c[z] = populacao[z];

  z = i;

  while (iv <= m && ic <= f) {
    /* Invariante: v[i..z] possui os valores de v[iv..m] e v[ic..f] em ordem crescente. */

    if (c[iv]->pontuacao <= c[ic]->pontuacao) populacao[z++] = c[iv++];
    else populacao[z++] = c[ic++];
  }

  while (iv <= m) populacao[z++] = c[iv++];

  while (ic <= f) populacao[z++] = c[ic++];
}

int gerar_alelo(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

void exibir_genotipo(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo)
{
    for(int i = 0; i < tamanho_pop; i++)
    {
        printf("\tIndividuo %d\nPontuacao: %d\nChave: %d\n", i+1, pop[i]->pontuacao, pop[i]->chave);
        for(int j = 0; j < tamanho_cromossomo; j++)
        {
            printf("Casa %d: %d %d %d %d %d\n", j+1, pop[i]->genes[j][0], pop[i]->genes[j][1], pop[i]->genes[j][2], pop[i]->genes[j][3], pop[i]->genes[j][4]);
        }
        printf("\n");
    }
}

/*void ordenar_por_pts(Cromossomo **pop, int tamanho_pop)
{
    for(int i = 0; i < tamanho_pop; i++)
    {

    }
}*/

int **gerar_populacao_inicial(int tam_pop, int tamanho_cromossomo)
{
    Cromossomo **populacao = (Cromossomo **)malloc(tam_pop * sizeof(Cromossomo *));

    for(int i = 0; i < tam_pop; i++)
    {
        populacao[i] = construir_cromossomo(tamanho_cromossomo);

        for(int j = 0; j < tamanho_cromossomo; j++)
        {
            populacao[i]->genes[j][0] = gerar_alelo(1, 5);
            populacao[i]->genes[j][1] = gerar_alelo(6, 10);
            populacao[i]->genes[j][2] = gerar_alelo(11, 15);
            populacao[i]->genes[j][3] = gerar_alelo(16, 20);
            populacao[i]->genes[j][4] = gerar_alelo(21, 25);
        }

        // populacao[i]->genes[5] = gerar_alelo(26, 30);
    }

    return populacao;
}

void *mutacao(Cromossomo **pop, int tamanho_pop)
{
    float porcentagem = ((float)rand()/(float)(RAND_MAX)) * 1; // gera float aleatorio entre 0 e 1

    if(porcentagem <= TAXA_MUTACAO)
    {
        int locus, casa;
        for(int i = 0; i < tamanho_pop; i++)
        {
            locus = (rand() % (4 - 0 + 1)) + 0; // seleciona aleatoriamente o locus do individuo que sofrera mutacao
            casa = (rand() % (4 - 0 + 1)) + 0; // seleciona aleatoriamente a casa cujo gene sofrera alteracao
            int novo_alelo;
            switch(locus)
            {
                case 0:
                    do
                    {
                        novo_alelo = gerar_alelo(1, 5);
                    }while(novo_alelo == pop[i]->genes[casa][locus]);

                    break;
                case 1:
                    do
                    {
                        novo_alelo = gerar_alelo(6, 10);
                    }while(novo_alelo == pop[i]->genes[casa][locus]);

                    break;
                case 2:
                    do
                    {
                        novo_alelo = gerar_alelo(11, 15);
                    }while(novo_alelo == pop[i]->genes[casa][locus]);

                    break;
                case 3:
                    do
                    {
                        novo_alelo = gerar_alelo(16, 20);
                    }while(novo_alelo == pop[i]->genes[casa][locus]);

                    break;
                case 4:
                    do
                    {
                        novo_alelo = gerar_alelo(21, 25);
                    }while(novo_alelo == pop[i]->genes[casa][locus]);

                    break;
            }
            pop[i]->genes[casa][locus] = novo_alelo;
        }
    }
    // printf("%.2f\n", porcentagem);
}

void substituir_individuos_menos_aptos(Cromossomo **populacao, int tamanho_pop, int tamanho_cromossomo)
{
    int qtd_individuos = tamanho_pop * 0.15; // 15% da populacao sera selecionada como parte menos apta
    int qtd_selecionados = 0;

    // printf("%d\n", qtd_individuos);
    int *chaves_menos_aptos = (int *)malloc(qtd_individuos * sizeof(int));
    mergesort(populacao, tamanho_pop); // ordena o vetor da populacao em ordem crescente


    for(int i = 0; i < qtd_individuos; i++)
    {
        populacao[i] = construir_cromossomo(tamanho_cromossomo); // substitui os primeiros "qtd_individuos" cromossomos por cromossomos aleatorios
    }
}

void *imigracao(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo)
{
    float porcentagem = ((float)rand()/(float)(RAND_MAX)) * 1; // gera float aleatorio entre 0 e 1

    if(porcentagem <= TAXA_IMIGRACAO)
    {
        substituir_individuos_menos_aptos_individuos_menos_aptos(pop, tamanho_pop, tamanho_cromossomo);
    }
}
