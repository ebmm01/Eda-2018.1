struct Pessoa{
  char nome[100];
  char Celular[10];
  char Endereco[100];
  int cep;
};

typedef struct elemento* Lista;

Lista *cria_lista();

void Libera_lista(Lista* li);

int insere_lista_inicio(Lista* li, struct Pessoa p);

int insere_lista_final(Lista* li, struct Pessoa p);

int insere_lista_ordenada(Lista* li, struct Pessoa p);

int remove_lista_inicio(Lista* li);

int remove_lista_final(Lista* li);

int remove_lista(Lista* li, int cep);//trocar o cep pelo nome talvez
