#ifndef SLLIST_H
#define	SLLIST_H
typedef struct _sllist_ SLList;
typedef struct _slnode_ SLNode;
typedef struct _aluno_ Aluno;
typedef struct _alelo_ Alelo;

SLList *sllCriar();
int sllInserirComoUltimo(SLList *l, void *item);
void *sllRetirar(SLList *l, void *chave, int (*cmp)(void *, void *));
void *sllBuscar(SLList *l,	void *chave, int (*cmp)(void *, void *));
void *sllPegarPrimeiro(SLList *l);
void *sllPegarProximo(SLList *l);
int sllEsvaziar(SLList *l);
int sllDestruir(SLList *l);
int cmpMat(void *chave, void *item);
int cmpNota(void *chave, void *item);
int cmpAlelo(void *chave, void *item);

#endif
