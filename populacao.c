#include "populacao.h"
#include "cromossomo.h"
#include "alelo.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define FALSE 0
#define TRUE !(FALSE)

typedef struct _sllist_{
    SLNode *primeiro;
    SLNode *atual;
}SLList;

typedef struct _alelo_
{
    int valor;
} Alelo;

typedef struct _cromossomo_{
    int chave;
    int **genes;
    int pontuacao;
} Cromossomo;

int qtd_sobreviventes = 0;
Cromossomo **sobreviventes = NULL; // vetor para armazenar os individuos que sobrevivem para a proxima geracao

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

void exibir_genotipo_sobreviventes(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo)
{
    for(int i = 0; i < qtd_sobreviventes; i++)
    {
        printf("\tIndividuo %d\nPontuacao: %d\nChave: %d\n", i+1, sobreviventes[i]->pontuacao, sobreviventes[i]->chave);
        for(int j = 0; j < tamanho_cromossomo; j++)
        {
            printf("Casa %d: %d %d %d %d %d\n", j+1, sobreviventes[i]->genes[j][0], sobreviventes[i]->genes[j][1], sobreviventes[i]->genes[j][2], sobreviventes[i]->genes[j][3], sobreviventes[i]->genes[j][4]);
        }
        printf("\n");
    }
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

int **gerar_populacao_inicial(int tam_pop, int tamanho_cromossomo)
{
    Cromossomo **populacao = (Cromossomo **)malloc(tam_pop * sizeof(Cromossomo *));

    for(int i = 0; i < tam_pop; i++)
    {
        populacao[i] = construir_cromossomo(tamanho_cromossomo);
    }

    return populacao;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void *mutacao(Cromossomo **pop, int tamanho_pop)
{
    int qtd_individuos = tamanho_pop * TAXA_MUTACAO;
    int indice;
    int locus, casa1, casa2;
    for(int i = 0; i < qtd_individuos; i++)
    {
        indice = (rand() % ((tamanho_pop-1) - 0 + 1)) + 0;
        if(!eh_sobrevivente(pop[indice]))
        {
            locus = (rand() % (4 - 0 + 1)) + 0; // seleciona aleatoriamente um dos loci do individuo que sofrera mutacao
            casa1 = (rand() % (4 - 0 + 1)) + 0; // seleciona aleatoriamente uma das casas cujo gene sofrera alteracao

            do
            {
                casa2 = (rand() % (4 - 0 + 1)) + 0; // seleciona aleatoriamente uma das casas cujo gene sofrera alteracao
            }while(casa1 == casa2);

            int alelo_aux;

            alelo_aux = pop[indice]->genes[casa1][locus];
            pop[indice]->genes[casa1][locus] = pop[indice]->genes[casa2][locus];
            pop[indice]->genes[casa2][locus] = alelo_aux;

            /*printf("Individuo: %d\n", indice+1);
            printf("\n");*/
        }

    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void imigracao(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo)
{
    int qtd_individuos = tamanho_pop * TAXA_IMIGRACAO; // TAXA_IMIGRACAO% da populacao sera selecionada como parte menos apta

    // printf("%d\n", qtd_individuos);
    mergesort(pop, tamanho_pop); // ordena o vetor da populacao em ordem crescente

    for(int i = 0; i < qtd_individuos; i++)
    {
        free(pop[i]);
        pop[i] = construir_cromossomo(tamanho_cromossomo); // substitui os primeiros "qtd_individuos" cromossomos por cromossomos aleatorios
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int eh_sobrevivente(Cromossomo *crom)
{
    if(sobreviventes != NULL)
    {
        for(int i = 0; i < qtd_sobreviventes; i++)
        {
            if(sobreviventes[i]->chave == crom->chave)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

void sobrevivencia(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo)
{
    qtd_sobreviventes = tamanho_pop * TAXA_SOBREVIVENCIA; // TAXA_SOBREVIVENCIA% da populacao sera selecionada como parte sobrevivente
    sobreviventes = (Cromossomo **)malloc(qtd_sobreviventes * sizeof(Cromossomo *));

    mergesort(pop, tamanho_pop); // ordena o vetor da populacao em ordem crescente

    for(int i = tamanho_pop-1, j = 0; i >= (tamanho_pop - qtd_sobreviventes); i--, j++)
    {
        sobreviventes[j] = pop[i];
    }
}
