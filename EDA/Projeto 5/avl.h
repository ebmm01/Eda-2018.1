#ifndef avl
#define avl

struct elem {
  int info;
  int alt;
  struct elem *esquerdo;
  struct elem *direito;
};

typedef struct elem* ArvAVL;

int alt_NO(struct elem* no);

int fatorBalanceamento_NO(struct elem* no);

void rotacaoLL(ArvAVL* raiz);

void rotacaoRR(ArvAVL* raiz);

void rotacaoLR(ArvAVL* raiz);

void rotacaoRL(ArvAVL* raiz);

int insere_ArvAVL(ArvAVL *raiz, int valor);

int remove_ArvAVL(ArvAVL *raiz, int valor);

struct elem* procuraMenor(struct elem* atual);

#endif

/*
int x = insere_ArvAVL(raiz, valor);

*/
