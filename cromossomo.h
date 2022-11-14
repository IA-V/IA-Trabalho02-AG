#ifndef CROMOSSOMO_H
#define CROMOSSOMO_H

#include "sllist.h"

typedef struct _cromossomo_ Cromossomo;

int gerar_alelo(SLList *lista, int tamanho_lista);
Cromossomo *construir_cromossomo(int tamanho_cromossomo);

#endif
