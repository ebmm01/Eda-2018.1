#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
  if (raiz == NULL) return 0;
  if (*raiz == NULL) return -1;
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
  int nivel=0;
  struct NO* atual = *raiz;
  struct NO* ant = NULL;
  struct NO* irmao = NULL;
  while(atual != NULL){
    if(valor == atual->num){
      printf("\n\nValor encontrado!\n");
      printf("Nível do nó: %d\n",nivel );
      printf("Valor do pai: %d\n", ant->num);
      if (irmao != NULL) printf("Valor do irmão: %d\n", irmao->num);
      else printf("Nó não tem irmao.\n\n");
      return 1;
    }
    if(valor > atual->num){
      ant = atual;
      irmao = ant->esquerdo;
      atual = atual->direito;
      nivel++;
    }
    else{
      ant = atual;
      irmao = ant->direito;
      atual = atual->esquerdo;
      nivel++;
    }
  }
  printf("Valor não encontrado.\n" );
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
