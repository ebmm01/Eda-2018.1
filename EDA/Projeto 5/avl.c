#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

int alt_NO(struct elem* no){
  if (no ==NULL) return -1;
  else return no->alt;
}

int fatorBalanceamento_NO(struct elem* no){
  return labs(alt_NO(no->esquerdo) - alt_NO(no->direito));
}

int maior(int x, int y){
  if(x>y) return x;
  else return y;
}

void rotacaoLL(ArvAVL* raiz){
  struct elem *no;
  no = (*raiz)->esquerdo;
  (*raiz)->esquerdo = no->direito;
  no->direito = (*raiz);
  (*raiz)->alt = maior(alt_NO((*raiz)->esquerdo), alt_NO((*raiz)->direito));
  no->alt = maior(alt_NO(no->esquerdo),(*raiz)->alt)+1;
  (*raiz) = no;
}

void rotacaoRR(ArvAVL* raiz){
  struct elem *no;
  no = (*raiz)->direito;
  (*raiz)->direito = no->esquerdo;
  no->esquerdo = (*raiz);
  (*raiz)->alt = maior(alt_NO((*raiz)->esquerdo), alt_NO((*raiz)->direito));
  no->alt = maior(alt_NO(no->direito),(*raiz)->alt)+1;
  (*raiz) = no;
}

void rotacaoLR(ArvAVL* raiz){
  rotacaoRR(&(*raiz)->esquerdo);
  rotacaoLL(raiz);
}

void rotacaoRL(ArvAVL* raiz){
  rotacaoLL(&(*raiz)->direito);
  rotacaoRR(raiz);
}

int insere_ArvAVL(ArvAVL *raiz, int valor){
  int res;
  if (*raiz == NULL){
    struct elem *novo;
    novo = (struct elem*)malloc(sizeof(struct elem));
    if(novo==NULL) return 0;
    novo->info = valor;
    novo->alt = 0;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    *raiz = novo;
    return 1;
  }
  struct elem *atual = *raiz;

  if (valor < atual->info){
    if ((res=insere_ArvAVL(&(atual->esquerdo), valor)) == 1){
      if (fatorBalanceamento_NO(atual) >= 2){
        if (valor < (*raiz)->esquerdo->info){
          rotacaoLL(raiz);
        }
        else{
          rotacaoLR(raiz);
        }
      }
    }
  }
  else {
    if (valor > atual->info){
      if ((res=insere_ArvAVL(&(atual->direito), valor))== 1){
        if (fatorBalanceamento_NO(atual) >= 2){
          if ((*raiz)->direito->info <valor){
            rotacaoRR(raiz);
          }
          else{
            rotacaoRL(raiz);
          }
        }
      }
    }
    else{
      printf("Valor duplicado!!\n");
      return 0;
    }
  }
  atual->alt = maior(alt_NO(atual->esquerdo),alt_NO(atual->direito)) + 1;

  return res;
}

int remove_ArvAVL(ArvAVL *raiz, int valor){
  if (*raiz == NULL){
    printf("Valor não existe na árvore!!\n");
    return 0;
  }
  int res;
  if (valor < (*raiz)->info){
    if ((res=remove_ArvAVL(&(*raiz)->esquerdo, valor)) == 1){
      if (fatorBalanceamento_NO(*raiz) >= 2){
        if(alt_NO((*raiz)->direito->esquerdo) <= alt_NO((*raiz)->direito->esquerdo))
          rotacaoRR(raiz);
        else
          rotacaoLR(raiz);
      }
    }
  }
  if ((*raiz)->info < valor){
    if((res=remove_ArvAVL(&(*raiz)->direito, valor))== 1){
      if (fatorBalanceamento_NO(*raiz) >= 2){
        if (alt_NO((*raiz)->esquerdo->direito) <= alt_NO((*raiz)->esquerdo->esquerdo))
          rotacaoLL(raiz);
        else rotacaoLR(raiz);
      }
    }
  }
  if ((*raiz)->info == valor){
    if (((*raiz)->esquerdo==NULL || (*raiz)->direito==NULL)){
      struct elem *antigo = (*raiz);
      if((*raiz)->esquerdo != NULL) *raiz = (*raiz)->esquerdo;
      else *raiz = (*raiz)->esquerdo;
      free(antigo);
    }
    else{
      struct elem *temp = procuraMenor((*raiz)->direito);
      (*raiz)->info = temp->info;
      remove_ArvAVL(&(*raiz)->direito, (*raiz)->info);
      if(fatorBalanceamento_NO(*raiz)>=2){
        if (alt_NO((*raiz)->esquerdo->direito) <= alt_NO((*raiz)->esquerdo->esquerdo))
          rotacaoLL(raiz);
        else rotacaoLR(raiz);
      }
      temp->alt = maior(alt_NO(temp->esquerdo),alt_NO(temp->direito)) + 1;
    }
    return 1;
  }
  return res;
}

struct elem* procuraMenor(struct elem* atual){
  struct elem *no1 = atual;
  struct elem *no2 = atual->esquerdo;
  while(no2 != NULL){
    no1=no2;
    no2 = no2->esquerdo;
  }
  return no1;
}
