#include "cromossomo.h"
#include "alelo.h"

#include <stdlib.h>

int contador_chave = 1; // guarda o valor da ultima chave gerada

typedef struct _alelo_
{
    int valor;
} Alelo;


typedef struct _cromossomo_{
    int chave;
    int **genes; // cor, nacionalidade, bebida, cigarro, animal
    int pontuacao;
    float aptidao;
} Cromossomo;

int gerar_pts_aleatoria(int lower, int upper) // serve apenas para testar as operações geneticas
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

int gerar_alelo(SLList *lista, int tamanho_lista)
{
    int count;
    int upper = 1;
    float porcentagem = ((float)rand()/(float)(RAND_MAX)) * upper;

    Alelo *atual, *alelo;

    if(tamanho_lista == 1)
    {
        atual = (Alelo *)sllPegarPrimeiro(lista);
        alelo = (Alelo *)sllRetirar(lista, (void *)&atual->valor, cmpAlelo);
        return alelo->valor;
    } else {
        do
        {
            count = 0;

            atual = (Alelo *)sllPegarPrimeiro(lista);
            if(porcentagem <= 0.5) {
                alelo = (Alelo *)sllRetirar(lista, (void *)&atual->valor, cmpAlelo);
                return alelo->valor;
            }

            while(count < tamanho_lista-1)
            {
                atual = (Alelo *)sllPegarProximo(lista);
                porcentagem = ((float)rand()/(float)(RAND_MAX)) * upper;
                if(porcentagem <= 0.5) {
                    alelo = (Alelo *)sllRetirar(lista, (void *)&atual->valor, cmpAlelo);
                    return alelo->valor;
                }

                count++;
            }
        }while(1 == 1);
    }


}

// Aloca memoria para um cromossomo (genes e chave)
Cromossomo *construir_cromossomo(int tamanho_cromossomo)
{
    int tamanho_lista = 5;

    SLList *cores = gerar_lista_cores();
    SLList *nacionalidades = gerar_lista_nacionalidades();
    SLList *bebidas = gerar_lista_bebidas();
    SLList *cigarros = gerar_lista_cigarros();
    SLList *animais = gerar_lista_animais();

    Cromossomo *cromossomo = (Cromossomo *)malloc(sizeof(Cromossomo));
    cromossomo->genes = (int **)malloc(tamanho_cromossomo * sizeof(int *));
    for(int i = 0; i < tamanho_cromossomo; i++)
    {
        cromossomo->genes[i] = (int *)malloc(tamanho_cromossomo * sizeof(int));
        cromossomo->genes[i][0] = gerar_alelo(cores, tamanho_lista);
        cromossomo->genes[i][1] = gerar_alelo(nacionalidades, tamanho_lista);
        cromossomo->genes[i][2] = gerar_alelo(bebidas, tamanho_lista);
        cromossomo->genes[i][3] = gerar_alelo(cigarros, tamanho_lista);
        cromossomo->genes[i][4] = gerar_alelo(animais, tamanho_lista);
        tamanho_lista--;
    }
    cromossomo->chave = contador_chave;
    cromossomo->pontuacao = gerar_pts_aleatoria(0, 15); // apenas para teste
    cromossomo->aptidao = 0;

    contador_chave++;
    return cromossomo;
}
