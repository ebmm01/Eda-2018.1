#ifndef _LISTAS_
#define _LISTAS_


 struct Pessoa{
  char *nome;
  char *Celular;
  char *Endereco;
  int cep;
};

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

int consulta_lista_pos(Lista* li, int pos, struct Pessoa p);

#endif
