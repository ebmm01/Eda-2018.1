#include <stdlib.h>
#include <stdio.h>
#include "abin.h"

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
