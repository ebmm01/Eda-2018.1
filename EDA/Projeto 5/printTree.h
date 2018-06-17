#ifndef print
#define print
#include "abin.h"
#define MAX_HEIGHT 1000
#define INFINITY 1048576

typedef struct ArvBinBusca ArvBinPrint;

struct ArvBinBusca {
    ArvBinPrint *esquerdo;
    ArvBinPrint *direito;

    //length of the edge from this node to its children
    int edge_length;
    int height;
    int elemento;
    //-1=I am left, 0=I am root, 1=right
    int parent_dir;
    char label[11];
};

int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
int print_next;

void showTree(ArvBin *t);

ArvBinPrint *insere_ArvBinPrint_rec(ArvBin *t);

ArvBinPrint *insere_ArvBinPrint(ArvBin *t);

void free_ascii_tree(ArvBinPrint *node);

void compute_profile(ArvBinPrint *node, int x, int y,char direction);

void filledge(ArvBinPrint *node);

void printLevel(ArvBinPrint *node, int x, int level) ;

int MIN(int X, int Y);

int MAX(int X, int Y);

#endif
