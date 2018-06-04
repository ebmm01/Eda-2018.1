#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filas.h"
#include <stdbool.h>

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

void imprime_Fila(Fila* li){
  Fila* p = li;
  Elem* no = p->inicio;
  if(no == NULL){
  printf("Lista vazia\n");
  //exit(1);

  } else {

    while(&(*no) != NULL){
      printf(" Codigo: %s \n", no->dados.codigo);
      printf(" Status: %c \n", no->dados.status);
      printf(" Gasol: %d \n", no->dados.gasol);
        no =no->prox;
    }

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
    fi->final->prox = no;
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

int verifica_comb0(Fila* li){
  Fila* p = li;
  Elem* no = p->inicio;
  int comb=0;
  if(no == NULL){
  printf("Lista vazia\n");
  //exit(1);

  } else {

    while(&(*no) != NULL){
        if (no->dados.gasol== 0) comb++;
        no =no->prox;
    }
  }
  return comb;
}

int aleatorio(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void insere_Voo(Fila* li,char* codigo, char t, int gasol, int preenche){
  struct aviao *voo = (struct aviao*)malloc(sizeof(struct aviao));
     strcpy(voo->codigo, codigo);
     if(preenche == 1){
       if(t=='d')
          voo->gasol = 12;
       else
           voo->gasol = aleatorio(0,12);
     }
     else voo->gasol = gasol;
     voo->status = t;
     insere_Fila(li,*voo);
}

Fila* gerencia_Fila(Fila* li, Fila* destino, char tipo){
  if(li == NULL) return 0;
  Elem *no = (Elem*) malloc(sizeof(Elem));
  no = li->inicio;
  for (int j = 0; j<=12; j++){
  for (int i = 0; i<tamanho_Fila(li); i++){
    if(no->dados.gasol == j && no->dados.status == tipo){
      insere_Voo(destino, no->dados.codigo, no->dados.status,no->dados.gasol, 2);

    }
    no = no->prox;
  }
  no = li->inicio;
}
  return destino;
}

void calc_Hora(int *hora, int *min){
  if (*min>= 60){
    if (*min == 60){
      *min = 0;
      *hora+=1;
    }
    else{
      *min -= 60;
      *hora+=1;
    }

  }
}

void reduz_comb(Fila* li){
  Fila* p = li;
  Elem* no = p->inicio;
  if(no == NULL){
  printf("Lista vazia\n");
  //exit(1);

  } else {

    while(&(*no) != NULL){
        no->dados.gasol -=1;
        no =no->prox;
    }
  }
}
