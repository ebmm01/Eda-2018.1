#ifndef filas
#define filas

struct aviao{
  char codigo[7];
  char status;
  int gasol;
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

void imprime_Fila(Fila* li);

int tamanho_Fila(Fila* fi);

int Fila_vazia(Fila* fi);

int insere_Fila(Fila* li, struct aviao al);

int remove_Fila(Fila* fi);

int consulta_Fila(Fila* fi, struct aviao *al);

int aleatorio(int min, int max);

void insere_Voo(Fila* li, char* codigo, char t);

#endif

//Funções da biblioteca:

/*
int x = tamanho_Fila(fi);
int y = Fila_vazia(fi);
int z = insere_Fila(fi, dados_aluno);
int w = remove_Fila(fi);
int x = consulta_Fila(fi, &dados_aluno);
*/
