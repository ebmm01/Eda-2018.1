#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printTree.h"

void showTree(ArvBin *t) {
    ArvBinPrint *raiz;
    int minX, i;
    if (t == NULL) return;
    raiz = insere_ArvBinPrint(t);
    preenche_borda(raiz);
    for (i = 0; i < raiz->altura && i < ALT_MAX; i++) {
        ladoEsquerdo[i] = 9999;
    }
    computa_Lados(raiz, 0, 0, 'e');
    minX = 0;
    for (i = 0; i < raiz->altura && i < ALT_MAX; i++) {
        minX = MIN(minX, ladoEsquerdo[i]);
    }
    for (i = 0; i < raiz->altura; i++) {
        print_next = 0;
        desenhaLinha(raiz, -minX, i);
        printf("\n");
    }
    libera_ArvBinPrint(raiz);
}

ArvBinPrint *insere_ArvBinPrint_rec(ArvBin *t) {
    ArvBinPrint *no;
    if ((*t) == NULL) return NULL;
    no = (ArvBinPrint*)malloc(sizeof(ArvBinPrint));
    no->esquerdo = insere_ArvBinPrint_rec(&((*t)->esquerdo));
    no->direito = insere_ArvBinPrint_rec(&((*t)->direito));

    if (no->esquerdo != NULL) {
        no->esquerdo->pai = -1;
    }

    if (no->direito != NULL) {
        no->direito->pai = 1;
    }

    sprintf(no->impressao, "%d", (*t)->num);
    no->elemento = strlen(no->impressao);

    return no;
}

ArvBinPrint *insere_ArvBinPrint(ArvBin *t) {
    ArvBinPrint *no;
    if (t == NULL) return NULL;
    no = insere_ArvBinPrint_rec(t);
    no->pai = 0;
    return no;
}

void libera_ArvBinPrint(ArvBinPrint *no) {
    if (no == NULL) return;
    libera_ArvBinPrint(no->esquerdo);
    libera_ArvBinPrint(no->direito);
    free(no);
}

//preenche os lados direito e esquero (array)
void computa_Lados(ArvBinPrint *no, int x, int y, char direcao) {
    int i, esquerdo,direito;
    if (no == NULL) return;
    if (direcao =='e'){
      esquerdo = (no->pai == -1);
      ladoEsquerdo[y] = MIN(ladoEsquerdo[y], x - ((no->elemento - esquerdo) / 2));
      if (no->esquerdo != NULL) {
          for (i = 1; i <= no->comprimento && y + i < ALT_MAX; i++) {
              ladoEsquerdo[y + i] = MIN(ladoEsquerdo[y + i], x - i);
          }
      }
    }
    if (direcao == 'd'){
      direito = (no->pai != -1);
      ladoDireito[y] = MAX(ladoDireito[y], x + ((no->elemento - direito) / 2));
      if (no->direito != NULL) {
          for (i = 1; i <= no->comprimento && y + i < ALT_MAX; i++) {
              ladoDireito[y + i] = MAX(ladoDireito[y + i], x + i);
          }
      }
    }
    computa_Lados(no->esquerdo, x - no->comprimento - 1, y + no->comprimento + 1, direcao);
    computa_Lados(no->direito, x + no->comprimento + 1, y + no->comprimento + 1, direcao);
}

//preenche comprimento e altura
void preenche_borda(ArvBinPrint *no) {
    int h, hmin, i, delta;
    if (no == NULL) return;
    preenche_borda(no->esquerdo);
    preenche_borda(no->direito);

    if (no->direito == NULL && no->esquerdo == NULL) {
        no->comprimento = 0;
    }
    else {
        if (no->esquerdo != NULL) {
            for (i = 0; i < no->esquerdo->altura && i < ALT_MAX; i++) {
                ladoDireito[i] = -9999;
            }
            computa_Lados(no->esquerdo, 0, 0, 'd');
            hmin = no->esquerdo->altura;
        }
        else {
            hmin = 0;
        }
        if (no->direito != NULL) {
            for (i = 0; i < no->direito->altura && i < ALT_MAX; i++) {
                ladoEsquerdo[i] = 9999;
            }
            computa_Lados(no->direito, 0, 0, 'e');
            hmin = MIN(no->direito->altura, hmin);
        }
        else {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = MAX(delta, 3 + 1 + ladoDireito[i] - ladoEsquerdo[i]);
        }

        //ajustes para o caso de 1 nó com 2 filhos de altura 1
        if (((no->esquerdo != NULL && no->esquerdo->altura == 1) ||
             (no->direito != NULL && no->direito->altura == 1)) && delta > 4) {
            delta--;
        }

        no->comprimento = ((delta + 1) / 2) - 1;
    }

    //preenche a altura do nó
    h = 1;
    if (no->esquerdo != NULL) {
        h = MAX(no->esquerdo->altura + no->comprimento + 1, h);
    }
    if (no->direito != NULL) {
        h = MAX(no->direito->altura + no->comprimento + 1, h);
    }
    no->altura = h;
}

void desenhaLinha(ArvBinPrint *no, int x, int level) {
    int i, esquerdo;
    if (no == NULL) return;
    esquerdo = (no->pai == -1);
    if (level == 0) {
        for (i = 0; i < (x - print_next - ((no->elemento - esquerdo) / 2)); i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", no->impressao);
        print_next += no->elemento;
    }
    else if (no->comprimento >= level) {
        if (no->esquerdo != NULL) {
            for (i = 0; i < (x - print_next - (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (no->direito != NULL) {
            for (i = 0; i < (x - print_next + (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else {
        desenhaLinha(no->esquerdo,
                   x - no->comprimento - 1,
                   level - no->comprimento - 1);
        desenhaLinha(no->direito,
                   x + no->comprimento + 1,
                   level - no->comprimento - 1);
    }
}

int MIN(int X, int Y) {
    return ((X) < (Y)) ? (X) : (Y);
}

int MAX(int X, int Y) {
    return ((X) > (Y)) ? (X) : (Y);
}
