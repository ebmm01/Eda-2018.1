#ifndef filas
#define filas

struct aviao{
  char *codigo;
  char *status;
  char *gasol;
  int horario;
  int npista;
};

typedef struct elemento{
  struct aviao dados;
  struct elemento *prox;
}Elem;

typedef struct fila{
  struct elemento *inicio;
  struct elemento *final;
}Fila;

Fila* cria_Fila();

void libera_Fila(Fila* fi);

int tamanho_Fila(Fila* fi);

int Fila_vazia(Fila* fi);

int insere_Fila(Fila* li, struct aviao al);

int remove_Fila(Fila* fi);

int consulta_Fila(Fila* fi, struct aviao *al);

#endif
