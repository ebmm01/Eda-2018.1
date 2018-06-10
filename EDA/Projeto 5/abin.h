#ifndef filas
#define filas

struct NO{
  int num;
  struct NO *esquerdo;
  struct NO *direito;
};

typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();

void libera_ArvBin(ArvBin *raiz);

void libera_NO(struct NO* no);

int estaVazia_ArvBin(ArvBin* raiz);

int altura_ArvBin(ArvBin *raiz);

int n_NOS(ArvBin *raiz);

void preOrdem_ArvBin(ArvBin *raiz);

void emOrdem_ArvBin(ArvBin *raiz);

void posOrdem_ArvBin(ArvBin *raiz);

#endif
/* Chamada das funções

ArvBin* raiz = cria_ArvBin();
libera_ArvBin(raiz);
int x = estaVazia_ArvBin(raiz);
int x = n_NOS(raiz);
preOrdem_ArvBin(raiz);
emOrdem_ArvBin(raiz);
posOrdem_ArvBin(raiz);

*/
