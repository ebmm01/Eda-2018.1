#include <stdlib.h>
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
