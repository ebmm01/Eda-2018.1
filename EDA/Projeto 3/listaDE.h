#ifndef listaDE
#define listaDE


struct Pessoa{
  char *nome;
  char *Celular;
  char *Endereco;
  int cep;
  char *Data;
};

struct elemento{
  struct elemento *ant;
  struct Pessoa dados;
  struct elemento *prox;
};

typedef struct elemento Elem;

typedef struct elemento* Lista;

Lista *cria_lista();

void Libera_lista(Lista* li);

void imprimir(Lista* li);

int insere_lista_inicio(Lista* li, struct Pessoa p);

int insere_lista_final(Lista* li, struct Pessoa p);

int insere_lista_ordenada(Lista* li, struct Pessoa p);

int remove_lista_inicio(Lista* li);

int remove_lista_final(Lista* li);

int remove_lista(Lista* li, int cep);//trocar o cep pelo nome talvez

int consulta_lista_pos(Lista* li, int pos, struct Pessoa *p);

int consulta_lista_cep(Lista* li, int cep, struct Pessoa *p);
//fazer a pesquisa por nome tbm

void menu();

#endif
