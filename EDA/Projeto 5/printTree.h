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

void printElements(ArvBin *t);

ArvBinPrint *build_ascii_tree_recursive(ArvBin *t);

ArvBinPrint *build_ascii_tree(ArvBin *t);

void free_ascii_tree(ArvBinPrint *node);

void compute_lprofile(ArvBinPrint *node, int x, int y);

void compute_rprofile(ArvBinPrint *node, int x, int y);

void filledge(ArvBinPrint *node);

void printLevel(ArvBinPrint *node, int x, int level) ;

int MIN(int X, int Y);

int MAX(int X, int Y);

#endif
