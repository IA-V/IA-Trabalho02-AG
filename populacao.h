#ifndef POPULACAO_H
#define POPULACAO_H

#include "cromossomo.h"

#define TAXA_SOBREVIVENCIA 0.1
#define TAXA_CROSSOVER 0.70
#define TAXA_MUTACAO 0.05
#define TAXA_IMIGRACAO 0.15

// ORDENACAO
void mergesort(Cromossomo **populacao, int tamanho_pop);
void sort(Cromossomo **populacao, Cromossomo **c, int i, int f);
void merge(Cromossomo **populacao, Cromossomo **c, int i, int m, int f);

// FUNCOES AUXILIARES
Cromossomo **gerar_populacao_inicial(int tam_pop, int tamanho_cromossomo);

int *gerar_aleatorios_nao_sobreviventes(int upper, int lower, int tamanho, Cromossomo **pop);
int eh_sobrevivente(Cromossomo *crom);
void exibir_genotipo(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo);

// OPERACOES GENETICAS
void sobrevivencia(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo);

void crossover(Cromossomo **pop, Cromossomo **progenitores, int tamanho_pop, int tamanho_prog, int tamanho_cromossomo);
Cromossomo **roleta(Cromossomo **pop, int tamanho_pop); // -> usada para selecao dos pais usados no crossover

void mutacao(Cromossomo **pop, int tamanho_pop);

void imigracao(Cromossomo **pop, int tamanho_pop, int tamanho_cromossomo);

// FUNCAO FITNESS
void avaliar(Cromossomo **populacao, int tamanho_pop, int tamanho_cromossomo);
void fitness(Cromossomo *individuo, int tamanho_cromossomo);

#endif
