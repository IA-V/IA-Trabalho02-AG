#ifndef CROMOSSOMO_H
#define CROMOSSOMO_H

typedef struct _cromossomo_ Cromossomo;

int gerar_alelo(int lower, int upper);
Cromossomo *construir_cromossomo(int tamanho_cromossomo);

#endif
