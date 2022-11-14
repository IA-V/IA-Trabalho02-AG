#include "sllist.h"
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

 typedef struct _slnode_{
    void *dado;
    struct _slnode_ *proximo;
}SLNode;

 typedef struct _sllist_{
    SLNode *primeiro;
    SLNode *atual;
 }SLList;

 typedef struct _aluno_{
    char nome[30];
    int matricula;
    float nota;
}Aluno;

typedef struct _alelo_
{
    int valor;
} Alelo;

SLList *sllCriar()
{
    SLList *l;
    l = (SLList *)malloc(sizeof(SLList));
    if(l != NULL)
    {
        l->primeiro = NULL;
        l->atual = NULL;
        return l;
    }
    return NULL;
}

int sllInserirComoUltimo(SLList *l, void *item)
{
    SLNode *ultimo;
    if(l != NULL)
    {
        SLNode *novo_no = (SLNode *)malloc(sizeof(SLNode));
        if(novo_no != NULL)
        {
            novo_no->dado = item;
            novo_no->proximo = NULL;
            if(l->primeiro != NULL){
                ultimo = l->primeiro;
                while(ultimo->proximo != NULL)
                {
                    ultimo = ultimo->proximo;
                }
                ultimo->proximo = novo_no;
            }
            else
            {
                l->primeiro = novo_no;
            }
            return TRUE;
        }
    }
    return FALSE;
}

void *sllBuscar(SLList *l,	void *chave, int (*cmp)(void *, void *))
{
    void *dado;
    SLNode *atual;

    if(l != NULL)
    {
        if(l->primeiro != NULL)
        {
            atual = l->primeiro;
            while(atual->proximo != NULL && cmp(chave, atual->dado) != TRUE)
            {
                atual = atual->proximo;
            }
            if(cmp(chave, atual->dado) == TRUE)
            {
                return atual->dado;
            }
        }
    }
    return NULL;
}

void *sllPegarPrimeiro(SLList *l)
{
    void *dado;
    if(l !=	NULL)
    {
        if (l->primeiro != NULL)
        {
            dado = l->primeiro->dado;
            l->atual = l->primeiro;
            return dado;
        }
    }
    return NULL;
}

void *sllPegarProximo(SLList *l)
{
    void *dado;
    if(l !=	NULL)
    {
        if (l->atual != NULL)
        {
            l->atual = l->atual->proximo;
            dado = l->atual->dado;
            return dado;
        }
    }
    return NULL;
}

void *sllRetirar(SLList *l, void *chave, int (*cmp)(void *, void *))
{
    void *dado;
    SLNode *atual, *anterior;

    if(l != NULL)
    {
        if(l->primeiro != NULL)
        {
            atual = l->primeiro;
            anterior = NULL;
            while(atual->proximo != NULL && cmp(chave, atual->dado) != TRUE)
            {
                anterior = atual;
                atual = atual->proximo;
            }

            if(cmp(chave, atual->dado) == TRUE)
            {
                dado = atual->dado;

                if(l->primeiro == atual)
                {
                    l->primeiro = atual->proximo;
                }
                else
                {
                    anterior->proximo = atual->proximo;
                }

                free(atual);
                return dado;
            }
        }
    }
    return NULL;
}

int sllEsvaziar(SLList *l)
{
    SLNode *atual, *proximo;
    if(l != NULL)
    {
        if(l->primeiro != NULL)
        {
            atual = l->primeiro;
            proximo = atual->proximo;
            free(atual);
            while(proximo != NULL)
            {
                atual = proximo;
                proximo = atual->proximo;
                free(atual);
            }

            l->primeiro = NULL;
            return TRUE;
        }
    }
    return FALSE;
}

int sllDestruir(SLList *l)
{
    if(l != NULL)
    {
        if(l->primeiro == NULL)
        {
            free(l);
            return TRUE;
        }
    }
    return FALSE;
}

int cmpMat(void *chave, void *item)
{
    int *chave_mat;
    Aluno *item_no;

    chave_mat = (int *)chave;
    item_no = (Aluno *)item;

    if (*chave_mat == item_no->matricula)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int cmpAlelo(void *chave, void *item)
{
    int *chave_mat;
    Alelo *item_no;

    chave_mat = (int *)chave;
    item_no = (Alelo *)item;

    if (*chave_mat == item_no->valor)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int cmpNota(void *chave, void *item)
{
    float *chave_nota;
    Aluno *item_no;

    chave_nota = (float *)chave;
    item_no= (Aluno *)item;

    if (*chave_nota == item_no->nota)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
