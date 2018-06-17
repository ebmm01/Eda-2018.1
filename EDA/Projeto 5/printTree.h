#ifndef print
#define print
#include "abin.h"

typedef int ELEMENT;

typedef struct BSTNode_struct BSTNode;

struct BSTNode_struct {
    BSTNode *ptLeft, *ptRight;

    //length of the edge from this node to its children
    int edge_length;

    int height;

    ELEMENT element;

    //-1=I am left, 0=I am root, 1=right
    int parent_dir;

    //max supported unit32 in dec, 10 digits max
    char label[11];
};

void printElements(ArvBin *t);

BSTNode *build_ascii_tree_recursive(ArvBin *t);

BSTNode *build_ascii_tree(ArvBin *t);

void free_ascii_tree(BSTNode *node);

void compute_lprofile(BSTNode *node, int x, int y);

void compute_rprofile(BSTNode *node, int x, int y);

void filledge(BSTNode *node);

void printLevel(BSTNode *node, int x, int level) ;

int MIN(int X, int Y);

int MAX(int X, int Y);

#endif
