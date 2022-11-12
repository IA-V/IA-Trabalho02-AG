#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "alelo.h"
#include "cromossomo.h"
#include "populacao.h"

#define TAMCROMOSSOMO 5 // comprimento do vetor 'genes' de cada cromossomo

#define POPINICIAL 100 // tamanho da populacao inicial
#define NUMGERACOES 50 // qtd de geracoes do algoritmo

typedef struct _cromossomo_{
    int chave;
    int **genes;
    int pontuacao;
} Cromossomo;

int geracao_atual = 1; // valor para guardar a geracao atual durante a execucao do algoritmo

int main()
{
    time_t t;
    srand((unsigned) time(&t));

    Cromossomo *crom1 = construir_cromossomo(TAMCROMOSSOMO);
    Cromossomo *crom2 = construir_cromossomo(TAMCROMOSSOMO);

    Cromossomo **populacao = gerar_populacao_inicial(POPINICIAL, TAMCROMOSSOMO);


    exibir_genotipo(populacao, POPINICIAL, TAMCROMOSSOMO);
    // mutacao(populacao, POPINICIAL);
    // imigracao(populacao, POPINICIAL, TAMCROMOSSOMO);
    sobrevivencia(populacao, POPINICIAL, TAMCROMOSSOMO);
    exibir_genotipo_sobreviventes(populacao, POPINICIAL, TAMCROMOSSOMO);
    // exibir_genotipo(populacao, POPINICIAL, TAMCROMOSSOMO);

    /*printf("%d\n", crom1->chave);
    printf("%d\n", crom2->chave);*/

    return 0;
}
