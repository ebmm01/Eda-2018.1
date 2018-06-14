#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abin.h"

#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY 1048576

int print_next;
int gap = 3;

ArvBin* cria_ArvBin(){
  ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
  if(raiz!= NULL)
    *raiz = NULL;
  return raiz;
}

void libera_ArvBin(ArvBin* raiz){
  if(raiz == NULL) return;
  libera_NO(*raiz); //libera cada nó
  free(raiz); // libera a raiz
}

void libera_NO(struct NO* no){
  if(no == NULL) return;
  libera_NO(no->esquerdo);
  libera_NO(no->direito);
  free(no);
  no = NULL;
}

int estaVazia_ArvBin(ArvBin* raiz){
    return (raiz == NULL || *raiz == NULL) ? 1 : 0;
}

int altura_ArvBin(ArvBin *raiz){
  if (raiz == NULL || *raiz == NULL) return 0;
  int lado_esquerdo = altura_ArvBin(&((*raiz)->esquerdo));
  int lado_direito = altura_ArvBin(&((*raiz)->direito));
  if (lado_esquerdo> lado_direito)
    return (lado_esquerdo + 1);
  else
    return (lado_direito + 1);
}

int n_NOS(ArvBin *raiz){
  if (raiz == NULL || *raiz == NULL) return 0;
  int lado_esquerdo = altura_ArvBin(&((*raiz)->esquerdo));
  int lado_direito = altura_ArvBin(&((*raiz)->direito));
  return (lado_direito + lado_esquerdo + 1);
}

void preOrdem_ArvBin(ArvBin *raiz){
  if (raiz == NULL) return;
  if (*raiz != NULL){
    printf("Valor: %d\n", (*raiz)->num);
    preOrdem_ArvBin(&((*raiz)->esquerdo));
    preOrdem_ArvBin(&((*raiz)->direito));
  }
}

void emOrdem_ArvBin(ArvBin *raiz){
  if (raiz == NULL) return;
  if (*raiz != NULL){
    emOrdem_ArvBin(&((*raiz)->esquerdo));
    printf("Valor: %d\n", (*raiz)->num);
    emOrdem_ArvBin(&((*raiz)->direito));
  }
}

void posOrdem_ArvBin(ArvBin *raiz){
  if (raiz == NULL) return;
  if (*raiz != NULL){
    posOrdem_ArvBin(&((*raiz)->esquerdo));
    posOrdem_ArvBin(&((*raiz)->direito));
    printf("Valor: %d\n", (*raiz)->num);
  }
}

int  insere_ArvBin(ArvBin *raiz, int valor){
  if (raiz == NULL) return 0;
  struct NO* novo;
  novo = (struct NO*) malloc(sizeof(struct NO));
  if (novo == NULL) return 0;
  novo->num = valor;
  novo->esquerdo = NULL;
  novo->direito = NULL;
  if (*raiz == NULL) *raiz = novo;
  else{
    struct NO* atual = *raiz;
    struct NO* anterior = NULL;
    while(atual!=NULL){
      anterior=atual;
      if (valor == atual->num){
        free(novo);
        return 0; //elemento existe
      }
      if (valor > atual->num) atual = atual->direito;
      else atual = atual->esquerdo;
    }
    if (valor > anterior->num) anterior->direito = novo;
    else anterior->esquerdo = novo;
  }
  return 1;
}

int remove_ArvBin(ArvBin *raiz, int valor){
  if (raiz == NULL) return 0;
  struct NO* atual = *raiz;
  struct NO* anterior = NULL;
  while(atual!=NULL){
    if (valor == atual->num){
      if (atual == *raiz) *raiz = remove_atual(atual);
      else{
        if (anterior->direito == atual)
          anterior->direito = remove_atual(atual);
        else anterior->esquerdo = remove_atual(atual);
      }
      return 1;
    }
    anterior = atual;
    if (valor > atual->num) atual = atual->direito;
    else atual = atual->esquerdo;
  }
  printf("Valor não encontrado\n");
  return 1;
}

struct NO* remove_atual(struct NO *atual){
  struct NO *no1, *no2;
  if(atual->esquerdo == NULL){
    no2 = atual->direito;
    free(atual);
    return no2;
  }
  no1 = atual;
  no2 = atual->esquerdo;
  while (no2->direito != NULL) {
    no1 = no2;
    no2 = no2->direito;
  }

  if (no1 != atual){
    no1->direito = no2->esquerdo;
    no2->esquerdo = atual->esquerdo;
  }
  no2->direito = atual->direito;
  return no2;
}

int consulta_ArvBin(ArvBin *raiz, int valor){
  if (raiz==NULL) return 0;
  struct NO* atual = *raiz;
  while(atual != NULL){
    if(valor == atual ->num){
      return 1;
      //aqui outras coisas podem ser feitas.
    }
    if(valor > atual->num) atual = atual->direito;
    else atual = atual->esquerdo;
  }
  return 0;
}

int isFull (ArvBin *raiz){
  struct NO* atual = *raiz;
    if (raiz == NULL)
        return 1;

    if (atual->esquerdo == NULL && atual->direito == NULL)
        return 1;

    if ((atual->esquerdo) && (atual->direito))
        return (isFull(&atual->esquerdo) && isFull(&atual->direito));

    return 0;
}

ArvBin* loadTreeFromFile(char *name){
  ArvBin* raiz = cria_ArvBin();
  FILE *arquivo;
  char filename[50];
  sprintf(filename, "DB/%s.txt",name);
  arquivo = fopen(filename, "r");
  int *num;
  num = (int*)malloc(11*sizeof(int));

  if (arquivo == NULL){
       printf("Não foi possível abrir o arquivo %s \n",filename);
       exit(1);
  }

  for (int i=0;i<1;i++){
        for (int j=0;j<10;j++){
           fscanf(arquivo,"%d ", (num+j));
           printf("%d\n", *(num+j));
           insere_ArvBin(raiz, *(num+j));
        }
  }

  free(num);

  return raiz;
}


void printElements(ArvBin *t) {
    BSTNode *proot;
    int xmin, i;
    if (t == NULL) return;
    proot = build_ascii_tree(t);
    filledge(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++) {
        print_next = 0;
        printLevel(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT) {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }
    free_ascii_tree(proot);
}

BSTNode *build_ascii_tree_recursive(ArvBin *t) {
    BSTNode *node;
    if ((*t) == NULL) return NULL;
    printf("CHEGOU AQUI\n");
    node = malloc(sizeof(BSTNode));
    node->ptLeft = build_ascii_tree_recursive(&((*t)->esquerdo));
    node->ptRight = build_ascii_tree_recursive(&((*t)->direito));

    if (node->ptLeft != NULL) {
        node->ptLeft->parent_dir = -1;
    }

    if (node->ptRight != NULL) {
        node->ptRight->parent_dir = 1;
    }

    sprintf(node->label, "%d", (*t)->num);
    node->element = strlen(node->label);

    return node;
}


//Copy the tree into the ascii node structre
BSTNode *build_ascii_tree(ArvBin *t) {
    BSTNode *node;
    if (t == NULL) return NULL;
    node = build_ascii_tree_recursive(t);
    node->parent_dir = 0;
    return node;
}

//Free all the nodes of the given tree
void free_ascii_tree(BSTNode *node) {
    if (node == NULL) return;
    free_ascii_tree(node->ptLeft);
    free_ascii_tree(node->ptRight);
    free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(BSTNode *node, int x, int y) {
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x - ((node->element - isleft) / 2));
    if (node->ptLeft != NULL) {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(node->ptLeft, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_lprofile(node->ptRight, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile(BSTNode *node, int x, int y) {
    int i, notleft;
    if (node == NULL) return;
    notleft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((node->element - notleft) / 2));
    if (node->ptRight != NULL) {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(node->ptLeft, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_rprofile(node->ptRight, x + node->edge_length + 1, y + node->edge_length + 1);
}

//This function fills in the edge_length and
//height fields of the specified tree
void filledge(BSTNode *node) {
    int h, hmin, i, delta;
    if (node == NULL) return;
    filledge(node->ptLeft);
    filledge(node->ptRight);

    /* first fill in the edge_length of node */
    if (node->ptRight == NULL && node->ptLeft == NULL) {
        node->edge_length = 0;
    }
    else {
        if (node->ptLeft != NULL) {
            for (i = 0; i < node->ptLeft->height && i < MAX_HEIGHT; i++) {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node->ptLeft, 0, 0);
            hmin = node->ptLeft->height;
        }
        else {
            hmin = 0;
        }
        if (node->ptRight != NULL) {
            for (i = 0; i < node->ptRight->height && i < MAX_HEIGHT; i++) {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node->ptRight, 0, 0);
            hmin = MIN(node->ptRight->height, hmin);
        }
        else {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        //If the node has two children of height 1, then we allow the
        //two leaves to be within 1, instead of 2
        if (((node->ptLeft != NULL && node->ptLeft->height == 1) ||
             (node->ptRight != NULL && node->ptRight->height == 1)) && delta > 4) {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
    }

    //now fill in the height of node
    h = 1;
    if (node->ptLeft != NULL) {
        h = MAX(node->ptLeft->height + node->edge_length + 1, h);
    }
    if (node->ptRight != NULL) {
        h = MAX(node->ptRight->height + node->edge_length + 1, h);
    }
    node->height = h;
}

void printLevel(BSTNode *node, int x, int level) {
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    if (level == 0) {
        for (i = 0; i < (x - print_next - ((node->element - isleft) / 2)); i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", node->label);
        print_next += node->element;
    }
    else if (node->edge_length >= level) {
        if (node->ptLeft != NULL) {
            for (i = 0; i < (x - print_next - (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->ptRight != NULL) {
            for (i = 0; i < (x - print_next + (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else {
        printLevel(node->ptLeft,
                   x - node->edge_length - 1,
                   level - node->edge_length - 1);
        printLevel(node->ptRight,
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
