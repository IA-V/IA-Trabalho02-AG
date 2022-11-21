#include "populacao.h"
#include "cromossomo.h"
#include "alelo.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define FALSE 0
#define TRUE !(FALSE)

typedef struct _cromossomo_{
    int chave;
    int **genes;
    int pontuacao;
    float aptidao;
} Cromossomo;

int qtd_sobreviventes = 0;
Cromossomo **sobreviventes = NULL; // vetor para armazenar os individuos que sobrevivem para a proxima geracao

// Codigo do MergeSort adaptado de https://gist.github.com/olegon/27c2a880c9b932862e60ab5eb89be5b6
void mergesort(Cromossomo **populacao, int tamanho_pop) {
  Cromossomo **c = (Cromossomo **)malloc(sizeof(Cromossomo *) * tamanho_pop);
  sort(populacao, c, 0, tamanho_pop - 1);
  free(c);
}

void sort(Cromossomo **populacao, Cromossomo **c, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(populacao, c, i, m);
  sort(populacao, c, m + 1, f);

  /* Se v[m] <= v[m + 1], então v[i..f] já está ordenado. */
  if (populacao[m]->pontuacao <= populacao[m + 1]->pontuacao) return;

  merge(populacao, c, i, m, f);
}

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

// Codigo adaptado de https://wagnergaspar.com/como-gerar-numeros-aleatorios-com-a-funcao-rand-sem-repeticao/
int *gerar_aleatorios_nao_sobreviventes(int upper, int lower, int tamanho, Cromossomo **pop) // Gera, sem repeticao, indices aleatorios de individuos nao sobreviventes
{
    int i = 0, j, igual, *vet = (int *)malloc(sizeof(int)*tamanho);

    do{
        vet[i] = (rand() % ((upper) - lower + 1)) + lower; // sorteia um número
        igual = 0;
        if(!eh_sobrevivente(pop[vet[i]]))
        {
            for(j = 0; j < i; j++){ // percorre a parte do vetor já preenchido
                if(vet[j] == vet[i])
                    igual = 1; // número repetido
            }

            if(igual == 0) // significa que o elemento não se repetiu
                i++;
        }

    }while(i < tamanho);

    return vet;

}

void exibir_genotipo(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo)
{
    // Exibe apenas o ultimo elemento
    printf("\tIndividuo %d\nPontuacao: %d\nChave: %d\nAptidao: %.3f\n", tamanho_pop, pop[tamanho_pop-1]->pontuacao, pop[tamanho_pop-1]->chave, pop[tamanho_pop-1]->aptidao);
    for(int j = 0; j < tamanho_cromossomo; j++)
    {
        printf("Casa %d: %d %d %d %d %d\n", j+1, pop[tamanho_pop-1]->genes[j][0], pop[tamanho_pop-1]->genes[j][1], pop[tamanho_pop-1]->genes[j][2], pop[tamanho_pop-1]->genes[j][3], pop[tamanho_pop-1]->genes[j][4]);
    }
    printf("\n");
    // system("cls");
}

void exibir_fenotipo(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo)
{
    // Exibe apenas o ultimo elemento
    printf("\tIndividuo %d\nPontuacao: %d\nChave: %d\nAptidao: %.3f\n", tamanho_pop, pop[tamanho_pop-1]->pontuacao, pop[tamanho_pop-1]->chave, pop[tamanho_pop-1]->aptidao);
    for(int j = 0; j < tamanho_cromossomo; j++)
    {
        printf("Casa %d: |", j+1);
        // CORES
        switch(pop[tamanho_pop-1]->genes[j][0])
        {
            case AMARELO:
                printf(" AMARELO |");
                break;
            case AZUL:
                printf(" AZUL |");
                break;
            case BRANCO:
                printf(" BRANCO |");
                break;
            case VERDE:
                printf(" VERDE |");
                break;
            case VERMELHO:
                printf(" VERMELHO |");
                break;
        }

        // NACIONALIDADES
        switch(pop[tamanho_pop-1]->genes[j][1])
        {
            case ALEMAO:
                printf(" ALEMAO |");
                break;
            case DINAMARQUES:
                printf(" DINAMARQUES |");
                break;
            case INGLES:
                printf(" INGLES |");
                break;
            case NORUEGUES:
                printf(" NORUEGUES |");
                break;
            case SUECO:
                printf(" SUECO |");
                break;
        }

        // BEBIDAS
        switch(pop[tamanho_pop-1]->genes[j][2])
        {
            case AGUA:
                printf(" AGUA |");
                break;
            case CAFE:
                printf(" CAFE |");
                break;
            case CHA:
                printf(" CHA |");
                break;
            case CERVEJA:
                printf(" CERVEJA |");
                break;
            case LEITE:
                printf(" LEITE |");
                break;
        }

        // CIGARROS
        switch(pop[tamanho_pop-1]->genes[j][3])
        {
            case BLENDS:
                printf(" BLENDS |");
                break;
            case BLUEMASTER:
                printf(" BLUEMASTER |");
                break;
            case DUNHILL:
                printf(" DUNHILL |");
                break;
            case PALLMALL:
                printf(" PALLMALL |");
                break;
            case PRINCE:
                printf(" PRINCE |");
                break;
        }

        // ANIMAIS
        switch(pop[tamanho_pop-1]->genes[j][4])
        {
            case CACHORRO:
                printf(" CACHORRO |");
                break;
            case CAVALO:
                printf(" CAVALO |");
                break;
            case GATO:
                printf(" GATO |");
                break;
            case PASSARO:
                printf(" PASSARO |");
                break;
            case PEIXE:
                printf(" PEIXE |");
                break;
        }

        printf("\n");
    }
    printf("\n");
    // system("cls");
}

Cromossomo **gerar_populacao_inicial(int tam_pop, int tamanho_cromossomo)
{
    Cromossomo **populacao = (Cromossomo **)malloc(tam_pop * sizeof(Cromossomo *));

    for(int i = 0; i < tam_pop; i++)
    {
        populacao[i] = construir_cromossomo(tamanho_cromossomo);
    }

    return populacao;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void mutacao(Cromossomo **pop, int tamanho_pop)
{
    int qtd_individuos = tamanho_pop * TAXA_MUTACAO;
    int *indices, indice;
    int locus, casa1, casa2;

    indices = gerar_aleatorios_nao_sobreviventes(tamanho_pop-1, 0, qtd_individuos, pop);

    for(int i = 0; i < qtd_individuos; i++)
    {
        indice = indices[i];

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

    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void imigracao(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo)
{
    int qtd_individuos = tamanho_pop * TAXA_IMIGRACAO; // TAXA_IMIGRACAO% da populacao sera selecionada como parte menos apta

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
    if(sobreviventes != NULL)
    {
        free(sobreviventes);
        sobreviventes = NULL;
        qtd_sobreviventes = 0;
    }

    qtd_sobreviventes = tamanho_pop * TAXA_SOBREVIVENCIA; // TAXA_SOBREVIVENCIA% da populacao sera selecionada como parte sobrevivente
    sobreviventes = (Cromossomo **)malloc(qtd_sobreviventes * sizeof(Cromossomo *));

    mergesort(pop, tamanho_pop); // ordena o vetor da populacao em ordem crescente

    for(int i = tamanho_pop-1, j = 0; i >= (tamanho_pop - qtd_sobreviventes); i--, j++)
    {
        sobreviventes[j] = pop[i];
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Cromossomo **roleta(Cromossomo **pop, int tamanho_pop)
{
    int qtd_individuos = tamanho_pop * TAXA_CROSSOVER;
    int qtd_pais, count_mais_aptos = 0;

    int soma_pts = 0;

    Cromossomo **progenitores;

    for(int i = 0; i < tamanho_pop; i++)
    {
        soma_pts += pop[i]->pontuacao;
    }

    mergesort(pop, tamanho_pop);

    for(int i = 0; i < tamanho_pop; i++)
    {
        pop[i]->aptidao = pop[i]->pontuacao / (float)(soma_pts / (tamanho_pop/10));
    }

    if(qtd_individuos % 2 != 0)
    {
        qtd_individuos--;
    }
    qtd_pais = qtd_individuos / 2;

    if((qtd_pais % 2) != 0)
    {
        qtd_pais--;
    }

    progenitores = (Cromossomo **)malloc(sizeof(Cromossomo *) * qtd_pais);

    int j = tamanho_pop-1;
    float porcentagem;
    while(count_mais_aptos < qtd_pais)
    {

        porcentagem = ((float)rand()/(float)(RAND_MAX)) * 1;
        if(1 - porcentagem <= pop[j]->aptidao)
        {
            progenitores[count_mais_aptos] = pop[j];
            count_mais_aptos++;
        }


        j--;
        if(j == -1)
        {
            j = tamanho_pop-1;
        }
    }
    mergesort(progenitores, qtd_pais);

    return progenitores;
}

void crossover(Cromossomo **pop, Cromossomo **progenitores, int tamanho_pop, int tamanho_prog, int tamanho_cromossomo)
{
    int indice_ponto_corte = 2;
    int qtd_novos_individuos = tamanho_prog * 2;
    int indice_novos_individuos = 0;

    Cromossomo **novos_individuos = (Cromossomo **)malloc(sizeof(Cromossomo *) * qtd_novos_individuos);

    for(int i = 0; i < (tamanho_prog/2); i++)
    {
        Cromossomo *novo_crom1 = construir_cromossomo(tamanho_cromossomo);
        Cromossomo *novo_crom2 = construir_cromossomo(tamanho_cromossomo);
        Cromossomo *novo_crom3 = construir_cromossomo(tamanho_cromossomo);
        Cromossomo *novo_crom4 = construir_cromossomo(tamanho_cromossomo);

        for(int j = 0; j < tamanho_cromossomo; j++)
        {
            for(int k = 0; k < tamanho_cromossomo; k++)
            {
                if(k < indice_ponto_corte)
                {
                    novo_crom1->genes[j][k] = progenitores[i]->genes[j][k];
                    novo_crom3->genes[j][k] = progenitores[i]->genes[j][k];
                    novo_crom2->genes[j][k] = progenitores[tamanho_prog-(i+1)]->genes[j][k];
                    novo_crom4->genes[j][k] = progenitores[tamanho_prog-(i+1)]->genes[j][k];
                } else {
                    novo_crom4->genes[j][k] = progenitores[i]->genes[j][k];
                    novo_crom2->genes[j][k] = progenitores[i]->genes[j][k];
                    novo_crom3->genes[j][k] = progenitores[tamanho_prog-(i+1)]->genes[j][k];
                    novo_crom1->genes[j][k] = progenitores[tamanho_prog-(i+1)]->genes[j][k];
                }

                novo_crom3->genes[0][k] = novo_crom1->genes[tamanho_cromossomo-1][k];
                novo_crom3->genes[tamanho_cromossomo-1][k] = novo_crom1->genes[0][k];

                novo_crom4->genes[1][k] = novo_crom2->genes[3][k];
                novo_crom4->genes[3][k] = novo_crom2->genes[1][k];
            }
        }

        novos_individuos[0 + indice_novos_individuos] = novo_crom1;
        novos_individuos[1 + indice_novos_individuos] = novo_crom2;
        novos_individuos[2 + indice_novos_individuos] = novo_crom3;
        novos_individuos[3 + indice_novos_individuos] = novo_crom4;

        indice_novos_individuos += 4;
    }

    int *indices = gerar_aleatorios_nao_sobreviventes(tamanho_pop-1, 0, qtd_novos_individuos, pop);

    for(int i = 0; i < qtd_novos_individuos; i++)
    {
        int indice = indices[i];

        Cromossomo *aux = pop[indice];
        pop[indice] = novos_individuos[i];
        free(aux);
    }
}

void avaliar(Cromossomo **populacao, int tamanho_pop, int tamanho_cromossomo)
{
    for(int i = 0; i < tamanho_pop; i++)
    {
        populacao[i]->pontuacao = 0;
        fitness(populacao[i], tamanho_cromossomo);
    }

    mergesort(populacao, tamanho_pop);
}

void fitness(Cromossomo *individuo, int tamanho_cromossomo)
{
    if(individuo->genes[0][1] == NORUEGUES)
    {
        individuo->pontuacao++;
    } else {
        individuo->pontuacao--;
    }

    if(individuo->genes[2][2] == LEITE)
    {
        individuo->pontuacao++;
    }

    for(int i = 0; i < tamanho_cromossomo; i++)
    {
        if(individuo->genes[i][1] == INGLES && individuo->genes[i][0] == VERMELHO)
        {
            individuo->pontuacao++;
        }

        if(individuo->genes[i][1] == SUECO && individuo->genes[i][4] == CACHORRO)
        {
            individuo->pontuacao++;
        }

        if(individuo->genes[i][1] == DINAMARQUES && individuo->genes[i][2] == CHA)
        {
            individuo->pontuacao++;
        }

        if(individuo->genes[i][3] == PALLMALL && individuo->genes[i][4] == PASSARO)
        {
            individuo->pontuacao++;
        }

        if(individuo->genes[i][0] == AMARELO && individuo->genes[i][3] == DUNHILL)
        {
            individuo->pontuacao++;
        }

        if(individuo->genes[i][0] == BRANCO)
        {
            int pontuar = FALSE;
            if(i > 0)
            {
                if(individuo->genes[i-1][0] == VERDE)
                {
                    pontuar = TRUE;
                }
            } else {
                individuo->pontuacao--;
            }

            if(individuo->genes[i][2] == CAFE)
            {
                pontuar = TRUE;
            }

            if(pontuar)
            {
                individuo->pontuacao++;
            }
        }

        if(individuo->genes[i][0] == VERDE)
        {
            int pontuar = FALSE;
            if(i < tamanho_cromossomo-1)
            {
                if(individuo->genes[i+1][0] == BRANCO)
                {
                    pontuar = TRUE;
                }
            } else {
                individuo->pontuacao--;
            }

            if(individuo->genes[i][2] == CAFE)
            {
                pontuar = TRUE;
            } else {
                individuo->pontuacao--;
            }

            if(pontuar)
            {
                individuo->pontuacao++;
            }
        }

        if(individuo->genes[i][3] == BLENDS)
        {
            int pontuar = FALSE;
            if(i > 0)
            {
                if(individuo->genes[i-1][4] == GATO)
                {
                    individuo->pontuacao++;
                } else if(i < (tamanho_cromossomo-1))
                {
                    if(individuo->genes[i+1][4] == GATO)
                    {
                        individuo->pontuacao++;
                    }
                }

                if(individuo->genes[i-1][2] == AGUA)
                {
                    pontuar = TRUE;
                } else if(i < (tamanho_cromossomo-1))
                {
                    if(individuo->genes[i+1][2] == AGUA)
                    {
                        pontuar = TRUE;
                    }
                }
            }

            if(pontuar)
            {
                individuo->pontuacao++;
            }
        }

        if(individuo->genes[i][4] == CAVALO)
        {
            int pontuar = FALSE;
            if(i > 0)
            {
                if(individuo->genes[i-1][3] == DUNHILL)
                {
                    pontuar = TRUE;
                } else if(i < (tamanho_cromossomo-1))
                {
                    if(individuo->genes[i+1][3] == DUNHILL)
                    {
                        pontuar = TRUE;
                    }
                }
            }

            if(pontuar)
            {
                individuo->pontuacao++;
            }
        }

        if(individuo->genes[i][1] == NORUEGUES)
        {
            int pontuar = FALSE;
            if(i > 0)
            {
                if(individuo->genes[i-1][0] == AZUL)
                {
                    pontuar = TRUE;
                } else
                {
                    individuo->pontuacao--;
                }
            } else if(i < (tamanho_cromossomo-1))
            {
                if(individuo->genes[i+1][0] == AZUL)
                {
                    pontuar = TRUE;
                } else
                {
                    individuo->pontuacao--;
                }
            }

            if(individuo->genes[i][0] == AZUL)
            {
                individuo->pontuacao--;
            }

            if(pontuar)
            {
                individuo->pontuacao++;
            }
        }

        if(individuo->genes[i][3] == BLUEMASTER && individuo->genes[i][2] == CERVEJA)
        {
            individuo->pontuacao++;
        }

        if(individuo->genes[i][1] == ALEMAO && individuo->genes[i][3] == PRINCE)
        {
            individuo->pontuacao++;
        }
    }
}
