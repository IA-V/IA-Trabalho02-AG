#ifndef POPULACAO_H
#define POPULACAO_H

#include "cromossomo.h"

#define TAXA_SOBREVIVENCIA 0.1
#define TAXA_CROSSOVER 0.75
#define TAXA_MUTACAO 0.05
#define TAXA_IMIGRACAO 0.1

int gerar_alelo(int lower, int upper);
int **gerar_populacao_inicial(int tam_pop, int tamanho_cromossomo);

void exibir_genotipo(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo);

// operacoes geneticas
int *sobrevivencia();

int *crossover(Cromossomo **pop, int tamanho_pop);
int *roleta(); // -> usada para selecao dos pais usados no crossover

void *mutacao(Cromossomo **pop, int tamanho_pop);

void substituir_individuos_menos_aptos(Cromossomo **populacao, int tamanho_pop, int tamanho_cromossomo);
void imigracao(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo);

#endif
