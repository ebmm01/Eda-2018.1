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


#endif
/* Chamada das funções

ArvBin* raiz = cria_ArvBin();

*/
