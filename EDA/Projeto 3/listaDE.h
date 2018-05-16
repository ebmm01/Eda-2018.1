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

void imprimir_elemento(Lista* li);

int count(Lista *temp);

void salva_arquivo(Lista* li);

void abre_arquivo(char lines[][101], int n, Lista* li);


int insere_lista_inicio(Lista* li, struct Pessoa p);

int insere_lista_final(Lista* li, struct Pessoa p);

int verifica_ordem_alfabetica(char* char1, char * char2);

int insere_lista_ordenada(Lista* li, struct Pessoa p);

int remove_lista_inicio(Lista* li);

int remove_lista_final(Lista* li);

int remove_lista(Lista* li, char *name);//trocar o cep pelo nome talvez

int consulta_lista_pos(Lista* li, int pos, struct Pessoa *p);

int consulta_lista_nome(Lista* li, char *name, struct Pessoa *p);

void pegar_contato(Lista *li,char *name,char *celular,char *endereco,char *data,int cep);

void criar_contato(Lista* li);

void criar_contato(Lista* li);

int validar_telefone(char *telefone);

int validar_data(char *data);

int validar_nome(char *nome);

void menu();

#endif

//Funções da biblioteca
/*int x = insere_lista_inicio(li, dados_pessoa);
int x = insere_lista_final(li, dados_pessoa);
int x = insere_lista_ordenada(li, dados_pessoa);
int x = remove_lista_inicio(li);
int x = remove_lista_final(li);
int x = remove_lista(li, cep_pessoa);
int x = consulta_lista_pos(li, posicao, &dados_pessoa);
int x = consulta_lista_cep(li, posicao, &dados_pessoa);*/
