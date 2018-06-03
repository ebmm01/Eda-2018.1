#include <stdlib.h>
#include <stdio.h>
#include "filas.h"

Fila* cria_Fila(){
  Fila* fi = (Fila*) malloc(sizeof(Fila));
  if (fi != NULL){
    fi->final = NULL;
    fi->inicio = NULL;
  }
  return fi;
}

void libera_Fila(Fila* fi){
  if(fi != NULL){
    Elem* no;
    while (fi->inicio != NULL) {
     no = fi -> inicio;
     fi->inicio = fi -> inicio -> prox;
     free(no);
    }
    free(fi);
  }
}

int tamanho_Fila(Fila* fi){
  if (fi == NULL) return 0;
  int cont = 0;
  Elem* no = fi->inicio;
  while(no !=NULL){
    cont++;
    no = no->prox;
  }
  return cont;
}

int Fila_vazia(Fila* fi){
  if (fi == NULL) return 1;
  if (fi ->inicio == NULL) return 1;
  return 0;
}

int insere_Fila(Fila* fi, struct aviao al){
  if(fi == NULL) return 0;
  Elem *no = (Elem*) malloc(sizeof(Elem));
  if (no == NULL) return 0;
  no->dados = al;
  no->prox = NULL;
  if (fi->final == NULL)
    fi->inicio = no;
  else
    fi->inicio = no;
  fi->final = no;
  return 1;
}

int remove_Fila(Fila* fi){
  if( fi == NULL) return 0;
  if(fi->inicio == NULL)
    return 0;
  Elem *no = fi->inicio;
  fi->inicio = fi->inicio->prox;
  if(fi->inicio == NULL)
    fi->final = NULL;
  free(no);
  return 1;
}

int consulta_Fila(Fila* fi, struct aviao *al){
  if(fi==NULL) return 0;
  if(fi->inicio == NULL)
    return 0;
  *al = fi->inicio->dados;
  return 1;
}
