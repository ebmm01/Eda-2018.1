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

int verifica_comb0(Fila* li);

int tamanho_Fila(Fila* fi);

int Fila_vazia(Fila* fi);

int insere_Fila(Fila* li, struct aviao al);

int remove_Fila(Fila* fi);

int consulta_Fila(Fila* fi, struct aviao *al);

int aleatorio(int min, int max);

void insere_Voo(Fila* li,char* codigo, char t, int gasol, int preenche);

Fila* gerencia_Fila(Fila* li, Fila* destino, char tipo);

void calc_Hora(int *hora, int *min);

void reduz_comb(Fila* li);

#endif

//Funções da biblioteca:

/*
<fila> = cria_Fila();

libera_Fila(<fila>);

imprime_Fila(<fila>);

int x = tamanho_Fila(fi);

int y = Fila_vazia(fi);

int z = insere_Fila(fi, <struct aviao>);

int w = remove_Fila(fi); -- destroi a fila

int x = consulta_Fila(fi, <struct aviao>); -- consulta o primeiro da fila

int num = aleatorio(min,max); --  onde min e max são o range

insere_Voo(<fila>, codigo, tipo, gasol, preenche) -- onde caso não hava gasolina,
o int preenche deve ser 1. Caso contrário será entendido que a gasolina já foi
preenchida.



*/
