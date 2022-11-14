#include "alelo.h"

typedef struct _alelo_
{
    int valor;
} Alelo;

typedef struct _sllist_{
    SLNode *primeiro;
    SLNode *atual;
 }SLList;

SLList *gerar_lista_cores()
{
    SLList *cores = sllCriar();

    Alelo *amarelo = (Alelo *)malloc(sizeof(Alelo));
    amarelo->valor = AMARELO;

    Alelo *azul = (Alelo *)malloc(sizeof(Alelo));
    azul->valor = AZUL;

    Alelo *branco = (Alelo *)malloc(sizeof(Alelo));
    branco->valor = BRANCO;

    Alelo *verde = (Alelo *)malloc(sizeof(Alelo));
    verde->valor = VERDE;

    Alelo *vermelho = (Alelo *)malloc(sizeof(Alelo));
    vermelho->valor = VERMELHO;

    sllInserirComoUltimo(cores, (void *)amarelo);
    sllInserirComoUltimo(cores, (void *)azul);
    sllInserirComoUltimo(cores, (void *)branco);
    sllInserirComoUltimo(cores, (void *)verde);
    sllInserirComoUltimo(cores, (void *)vermelho);

    return cores;
}

SLList *gerar_lista_nacionalidades()
{
    SLList *nacionalidades = sllCriar();

    Alelo *alemao = (Alelo *)malloc(sizeof(Alelo));
    alemao->valor = ALEMAO;

    Alelo *dinamarques = (Alelo *)malloc(sizeof(Alelo));
    dinamarques->valor = DINAMARQUES;

    Alelo *ingles = (Alelo *)malloc(sizeof(Alelo));
    ingles->valor = INGLES;

    Alelo *noruegues = (Alelo *)malloc(sizeof(Alelo));
    noruegues->valor = NORUEGUES;

    Alelo *sueco = (Alelo *)malloc(sizeof(Alelo));
    sueco->valor = SUECO;

    sllInserirComoUltimo(nacionalidades, (void *)alemao);
    sllInserirComoUltimo(nacionalidades, (void *)dinamarques);
    sllInserirComoUltimo(nacionalidades, (void *)ingles);
    sllInserirComoUltimo(nacionalidades, (void *)noruegues);
    sllInserirComoUltimo(nacionalidades, (void *)sueco);

    return nacionalidades;
}

SLList *gerar_lista_bebidas()
{
    SLList *bebidas = sllCriar();

    Alelo *agua = (Alelo *)malloc(sizeof(Alelo));
    agua->valor = AGUA;

    Alelo *cafe = (Alelo *)malloc(sizeof(Alelo));
    cafe->valor = CAFE;

    Alelo *cerveja = (Alelo *)malloc(sizeof(Alelo));
    cerveja->valor = CERVEJA;

    Alelo *cha = (Alelo *)malloc(sizeof(Alelo));
    cha->valor = CHA;

    Alelo *leite = (Alelo *)malloc(sizeof(Alelo));
    leite->valor = LEITE;

    sllInserirComoUltimo(bebidas, (void *)agua);
    sllInserirComoUltimo(bebidas, (void *)cafe);
    sllInserirComoUltimo(bebidas, (void *)cerveja);
    sllInserirComoUltimo(bebidas, (void *)cha);
    sllInserirComoUltimo(bebidas, (void *)leite);

    return bebidas;
}

SLList *gerar_lista_cigarros()
{
    SLList *cigarros = sllCriar();

    Alelo *blends = (Alelo *)malloc(sizeof(Alelo));
    blends->valor = BLENDS;

    Alelo *bluemaster = (Alelo *)malloc(sizeof(Alelo));
    bluemaster->valor = BLUEMASTER;

    Alelo *dunhill = (Alelo *)malloc(sizeof(Alelo));
    dunhill->valor = DUNHILL;

    Alelo *pallmall = (Alelo *)malloc(sizeof(Alelo));
    pallmall->valor = PALLMALL;

    Alelo *prince = (Alelo *)malloc(sizeof(Alelo));
    prince->valor = PRINCE;

    sllInserirComoUltimo(cigarros, (void *)blends);
    sllInserirComoUltimo(cigarros, (void *)bluemaster);
    sllInserirComoUltimo(cigarros, (void *)dunhill);
    sllInserirComoUltimo(cigarros, (void *)pallmall);
    sllInserirComoUltimo(cigarros, (void *)prince);

    return cigarros;
}

SLList *gerar_lista_animais()
{
    SLList *animais = sllCriar();

    Alelo *cachorro = (Alelo *)malloc(sizeof(Alelo));
    cachorro->valor = CACHORRO;

    Alelo *cavalo = (Alelo *)malloc(sizeof(Alelo));
    cavalo->valor = CAVALO;

    Alelo *gato = (Alelo *)malloc(sizeof(Alelo));
    gato->valor = GATO;

    Alelo *passaro = (Alelo *)malloc(sizeof(Alelo));
    passaro->valor = PASSARO;

    Alelo *peixe = (Alelo *)malloc(sizeof(Alelo));
    peixe->valor = PEIXE;

    sllInserirComoUltimo(animais, (void *)cachorro);
    sllInserirComoUltimo(animais, (void *)cavalo);
    sllInserirComoUltimo(animais, (void *)gato);
    sllInserirComoUltimo(animais, (void *)passaro);
    sllInserirComoUltimo(animais, (void *)peixe);

    return animais;
}
