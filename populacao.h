#ifndef POPULACAO_H
#define POPULACAO_H

#define TAXA_SOBREVIVENCIA 0.1
#define TAXA_CROSSOVER 0.75
#define TAXA_MUTACAO 0.05
#define TAXA_IMIGRACAO 0.1

int gerar_alelo(int lower, int upper);
int *gerar_populacao_inicial(int tam_pop, int tamanho_cromossomo);

// operacoes geneticas
int *sobrevivencia();
int *crossover();
int *roleta(); // -> usada para selecao dos pais usados no crossover
int *mutacao();
int *imigracao();

#endif
