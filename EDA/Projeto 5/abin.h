#ifndef filas
#define filas

struct NO{
  int num;
  struct NO *esquerdo;
  struct NO *direito;
};

typedef struct NO* ArvBin;

#endif
