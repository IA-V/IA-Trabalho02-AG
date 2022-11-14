#ifndef ALELO_H
#define ALELO_H

#include "sllist.h"

// CORES
#define AMARELO 1
#define AZUL 2
#define BRANCO 3
#define VERDE 4
#define VERMELHO 5

// NACIONALIDADES
#define ALEMAO 6
#define DINAMARQUES 7
#define INGLES 8
#define NORUEGUES 9
#define SUECO 10

// BEBIDAS
#define AGUA 11
#define CAFE 12
#define CERVEJA 13
#define CHA 14
#define LEITE 15

// CIGARROS
#define BLENDS 16
#define BLUEMASTER 17
#define DUNHILL 18
#define PALLMALL 19
#define PRINCE 20

// ANIMAIS
#define CACHORRO 21
#define CAVALO 22
#define GATO 23
#define PASSARO 24
#define PEIXE 25

typedef struct _alelo_ Alelo;

SLList *gerar_lista_cores();
SLList *gerar_lista_nacionalidades();
SLList *gerar_lista_bebidas();
SLList *gerar_lista_cigarros();
SLList *gerar_lista_animais();

#endif
