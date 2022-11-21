#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "alelo.h"
#include "cromossomo.h"
#include "populacao.h"

#define TAMCROMOSSOMO 5 // comprimento do vetor 'genes' de cada cromossomo

#define POPINICIAL 5000 // tamanho da populacao inicial
#define NUMGERACOES 8000 // qtd de geracoes do algoritmo

typedef struct _cromossomo_{
    int chave;
    int **genes;
    int pontuacao;
    float aptidao;
} Cromossomo;

int geracao_atual = 1; // valor para guardar a geracao atual durante a execucao do algoritmo

void exibir_forma_selecionada(int opcao, Cromossomo **populacao)
{
    switch(opcao)
    {
        case 1:
            exibir_genotipo(populacao, POPINICIAL, TAMCROMOSSOMO);
            break;
        case 2:
            exibir_fenotipo(populacao, POPINICIAL, TAMCROMOSSOMO);
            break;
    }
}

int main()
{
    int opcao;
    printf("1 - Exibir genotipo\n2 - Exibir fenotipo\n");
    scanf("%d", &opcao);

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

    while(geracao_atual <= NUMGERACOES && populacao[POPINICIAL - 1]->pontuacao != 15)
    {
        printf("-------------------------------------------------------------------------------------------------------------------------------------\nGeracao %d\n\n", geracao_atual);
        if(geracao_atual % 2 == 0)
        {
            imigracao(populacao, POPINICIAL, TAMCROMOSSOMO);
        }
        Cromossomo **progenitores = roleta(populacao, POPINICIAL);
        crossover(populacao, progenitores, POPINICIAL, qtd_progenitores, TAMCROMOSSOMO);

        mutacao(populacao, POPINICIAL);
        avaliar(populacao, POPINICIAL, TAMCROMOSSOMO);
        sobrevivencia(populacao, POPINICIAL, TAMCROMOSSOMO);

        exibir_forma_selecionada(opcao, populacao);
        // exibir_fenotipo(populacao, POPINICIAL, TAMCROMOSSOMO);
        geracao_atual++;
    }

    return 0;
}
