#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "alelo.h"
#include "cromossomo.h"
#include "populacao.h"

#define TAMCROMOSSOMO 5 // comprimento do vetor 'genes' de cada cromossomo

#define POPINICIAL 10000 // tamanho da populacao inicial
#define NUMGERACOES 10000 // qtd de geracoes do algoritmo

typedef struct _cromossomo_{
    int chave;
    int **genes;
    int pontuacao;
    float aptidao;
} Cromossomo;

int geracao_atual = 1; // valor para guardar a geracao atual durante a execucao do algoritmo

int main()
{
    int geracao_atual = 1;

    int qtd_progenitores = (POPINICIAL * TAXA_CROSSOVER) / 2;
    if(qtd_progenitores % 2 != 0)
        qtd_progenitores--;

    time_t t;
    srand((unsigned) time(&t));

    Cromossomo *crom1 = construir_cromossomo(TAMCROMOSSOMO);
    Cromossomo *crom2 = construir_cromossomo(TAMCROMOSSOMO);

    Cromossomo **populacao = gerar_populacao_inicial(POPINICIAL, TAMCROMOSSOMO);
    avaliar(populacao, POPINICIAL, TAMCROMOSSOMO);

    exibir_genotipo(populacao, POPINICIAL, TAMCROMOSSOMO);
    while(geracao_atual <= NUMGERACOES)
    {
        Cromossomo **progenitores = roleta(populacao, POPINICIAL);
        crossover(populacao, progenitores, POPINICIAL, qtd_progenitores, TAMCROMOSSOMO);
        mutacao(populacao, POPINICIAL);
        avaliar(populacao, POPINICIAL, TAMCROMOSSOMO);
        geracao_atual++;
        sobrevivencia(populacao, POPINICIAL, TAMCROMOSSOMO);
        exibir_genotipo(populacao, POPINICIAL, TAMCROMOSSOMO);
        printf("Geracao %d\n\n", geracao_atual);
        if(geracao_atual % 2 == 0)
        {
            imigracao(populacao, POPINICIAL, TAMCROMOSSOMO);
        }
    }

    // crossover(populacao, progenitores, POPINICIAL, qtd_progenitores, TAMCROMOSSOMO);
    // mutacao(populacao, POPINICIAL);
    // imigracao(populacao, POPINICIAL, TAMCROMOSSOMO);
    // sobrevivencia(populacao, POPINICIAL, TAMCROMOSSOMO);
    // exibir_genotipo_sobreviventes(populacao, POPINICIAL, TAMCROMOSSOMO);
    // roleta(populacao, POPINICIAL);
    // exibir_genotipo(populacao, POPINICIAL, TAMCROMOSSOMO);

    /*printf("%d\n", crom1->chave);
    printf("%d\n", crom2->chave);*/

    return 0;
}
