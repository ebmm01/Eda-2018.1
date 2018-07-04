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

int getHeight(ArvBin *raiz);

int n_NOS(ArvBin *raiz);

void printPreOrder(ArvBin *raiz);

void printInOrder(ArvBin *raiz);

void printPostOrder(ArvBin *raiz);

int  insere_ArvBin(ArvBin *raiz, int valor);

int remove_ArvBin(ArvBin *raiz, int valor);

struct NO* remove_atual(struct NO *atual);

int searchValue(ArvBin *raiz, int valor);

int isFull (ArvBin *raiz);

ArvBin* loadTreeFromFile(char *name);

void printElements(ArvBin *t);


#endif
/* Chamada das funções

ArvBin* raiz = cria_ArvBin();
libera_ArvBin(raiz);
int x = estaVazia_ArvBin(raiz);
int x = n_NOS(raiz);
preOrdem_ArvBin(raiz);
emOrdem_ArvBin(raiz);
posOrdem_ArvBin(raiz);
int x = insere_ArvBin(raiz, valor);
int x = remove_ArvBin(raiz, valor);
int x = consulta_ArvBin(raiz, valor);
*/
