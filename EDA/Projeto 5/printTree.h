#ifndef print
#define print
#include "abin.h"
#define ALT_MAX 1000

int ladoEsquerdo[ALT_MAX];
int ladoDireito[ALT_MAX];
int print_next;
typedef struct ArvBinBusca ArvBinPrint;

struct ArvBinBusca {
    ArvBinPrint *esquerdo;
    ArvBinPrint *direito;
    int comprimento;
    int altura;
    int elemento;
    int pai;
    char impressao[11];
};

void showTree(ArvBin *t);

ArvBinPrint *insere_ArvBinPrint_rec(ArvBin *t);

ArvBinPrint *insere_ArvBinPrint(ArvBin *t);

void libera_ArvBinPrint(ArvBinPrint *no);

void computa_Lados(ArvBinPrint *no, int x, int y,char direction);

void preenche_borda(ArvBinPrint *no);

void desenhaLinha(ArvBinPrint *no, int x, int level) ;

int MIN(int X, int Y);

int MAX(int X, int Y);

#endif
