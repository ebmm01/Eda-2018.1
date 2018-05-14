struct Pessoa{
  char nome[100];
  char Celular[10];
  char Endereco[100];
  int cep;
};
typedef struct elemento* Lista;

Lista *cria_lista();

void Libera_lista(Lista* li);
