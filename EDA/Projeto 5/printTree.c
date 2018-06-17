#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printTree.h"

void showTree(ArvBin *t) {
    ArvBinPrint *raiz;
    int xmin, i;
    if (t == NULL) return;
    raiz = build_ascii_tree(t);
    filledge(raiz);
    for (i = 0; i < raiz->height && i < MAX_HEIGHT; i++) {
        lprofile[i] = INFINITY;
    }
    compute_profile(raiz, 0, 0, 'l');
    xmin = 0;
    for (i = 0; i < raiz->height && i < MAX_HEIGHT; i++) {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < raiz->height; i++) {
        print_next = 0;
        printLevel(raiz, -xmin, i);
        printf("\n");
    }
    if (raiz->height >= MAX_HEIGHT) {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }
    free_ascii_tree(raiz);
}

ArvBinPrint *build_ascii_tree_recursive(ArvBin *t) {
    ArvBinPrint *node;
    if ((*t) == NULL) return NULL;
    node = malloc(sizeof(ArvBinPrint));
    node->esquerdo = build_ascii_tree_recursive(&((*t)->esquerdo));
    node->direito = build_ascii_tree_recursive(&((*t)->direito));

    if (node->esquerdo != NULL) {
        node->esquerdo->parent_dir = -1;
    }

    if (node->direito != NULL) {
        node->direito->parent_dir = 1;
    }

    sprintf(node->label, "%d", (*t)->num);
    node->elemento = strlen(node->label);

    return node;
}


//Copy the tree into the ascii node structre
ArvBinPrint *build_ascii_tree(ArvBin *t) {
    ArvBinPrint *node;
    if (t == NULL) return NULL;
    node = build_ascii_tree_recursive(t);
    node->parent_dir = 0;
    return node;
}

//Free all the nodes of the given tree
void free_ascii_tree(ArvBinPrint *node) {
    if (node == NULL) return;
    free_ascii_tree(node->esquerdo);
    free_ascii_tree(node->direito);
    free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_profile(ArvBinPrint *node, int x, int y, char direction) {
    int i, isleft,notleft;
    if (node == NULL) return;
    if (direction =='l'){
      isleft = (node->parent_dir == -1);
      lprofile[y] = MIN(lprofile[y], x - ((node->elemento - isleft) / 2));
      if (node->esquerdo != NULL) {
          for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
              lprofile[y + i] = MIN(lprofile[y + i], x - i);
          }
      }
    }
    if (direction == 'r'){
      notleft = (node->parent_dir != -1);
      rprofile[y] = MAX(rprofile[y], x + ((node->elemento - notleft) / 2));
      if (node->direito != NULL) {
          for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
              rprofile[y + i] = MAX(rprofile[y + i], x + i);
          }
      }
    }
    compute_profile(node->esquerdo, x - node->edge_length - 1, y + node->edge_length + 1, direction);
    compute_profile(node->direito, x + node->edge_length + 1, y + node->edge_length + 1, direction);
}

//This function fills in the edge_length and
//height fields of the specified tree
void filledge(ArvBinPrint *node) {
    int h, hmin, i, delta;
    if (node == NULL) return;
    filledge(node->esquerdo);
    filledge(node->direito);

    /* first fill in the edge_length of node */
    if (node->direito == NULL && node->esquerdo == NULL) {
        node->edge_length = 0;
    }
    else {
        if (node->esquerdo != NULL) {
            for (i = 0; i < node->esquerdo->height && i < MAX_HEIGHT; i++) {
                rprofile[i] = -INFINITY;
            }
            compute_profile(node->esquerdo, 0, 0, 'r');
            hmin = node->esquerdo->height;
        }
        else {
            hmin = 0;
        }
        if (node->direito != NULL) {
            for (i = 0; i < node->direito->height && i < MAX_HEIGHT; i++) {
                lprofile[i] = INFINITY;
            }
            compute_profile(node->direito, 0, 0, 'l');
            hmin = MIN(node->direito->height, hmin);
        }
        else {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = MAX(delta, 3 + 1 + rprofile[i] - lprofile[i]);
        }

        //If the node has two children of height 1, then we allow the
        //two leaves to be within 1, instead of 2
        if (((node->esquerdo != NULL && node->esquerdo->height == 1) ||
             (node->direito != NULL && node->direito->height == 1)) && delta > 4) {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
    }

    //now fill in the height of node
    h = 1;
    if (node->esquerdo != NULL) {
        h = MAX(node->esquerdo->height + node->edge_length + 1, h);
    }
    if (node->direito != NULL) {
        h = MAX(node->direito->height + node->edge_length + 1, h);
    }
    node->height = h;
}

void printLevel(ArvBinPrint *node, int x, int level) {
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    if (level == 0) {
        for (i = 0; i < (x - print_next - ((node->elemento - isleft) / 2)); i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", node->label);
        print_next += node->elemento;
    }
    else if (node->edge_length >= level) {
        if (node->esquerdo != NULL) {
            for (i = 0; i < (x - print_next - (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->direito != NULL) {
            for (i = 0; i < (x - print_next + (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else {
        printLevel(node->esquerdo,
                   x - node->edge_length - 1,
                   level - node->edge_length - 1);
        printLevel(node->direito,
                   x + node->edge_length + 1,
                   level - node->edge_length - 1);
    }
}

int MIN(int X, int Y) {
    return ((X) < (Y)) ? (X) : (Y);
}

int MAX(int X, int Y) {
    return ((X) > (Y)) ? (X) : (Y);
}
