#include <stdlib.h>
#include <stdio.h>
#include "listaDE.h"
#include <string.h>

struct elemento{
  struct elemento *ant;
  struct Pessoa dados;
  struct elemento *prox;
};

typedef struct elemento Elem;

Lista* cria_lista(){
  Lista* li = (Lista*)malloc(sizeof(Lista));
  if (li != NULL)
    *li = NULL;
  return li;
}

void Libera_lista(Lista* li){
    if(li != NULL){
      Elem* no;
      while((*li) != NULL){
        no = *li;
        *li = (*li)->prox;
        free (no);
      }
      free(li);
    }
}

void imprimir(Lista* li){
    Lista* p = li;

    if((*li) == NULL){
    printf("Lista vazia\n");
    //exit(1);

} else {

while((*p) != NULL){
    printf("Nome: %s \n", (*p)->dados.nome);
    printf("celular: %s \n", (*p)->dados.Celular);
    printf("Endereco: %s \n", (*p)->dados.Endereco);
    printf("Cep: %d \n\n", (*p)->dados.cep);
    (*p) = (*p)->prox;
}

}
}

int insere_lista_inicio(Lista* li, struct Pessoa p){
  if(li == NULL) return 0;
  Elem* no = (Elem*) malloc(sizeof(Elem));
  if(no == NULL) return 0;
  no->dados = p;
  no->prox = (*li);
  no->ant = NULL;
  //lista não vazia, apontar para o anterior
  if(*li != NULL)
    (*li)->ant = no;
  *li = no;
  return 1;

}

int insere_lista_final(Lista* li, struct Pessoa p){
  if(li == NULL) return 0;
  Elem *no = (Elem*) malloc(sizeof(Elem));
  if (no == NULL) return 0;
  no->dados = p;
  no->prox = NULL;
  if((*li) == NULL){ //lista vazia, insiro no começo
    no->ant = NULL;
    *li = no;
  }
  else {
    Elem *aux = *li;
    while(aux->prox != NULL)
      aux = aux->prox;
    aux->prox = no;
    no->ant = aux;
  }
  return 1;
}

int insere_lista_ordenada(Lista* li, struct Pessoa p){
  if(li == NULL) return 0;
  Elem *no = (Elem*) malloc(sizeof(Elem));
  if (no == NULL) return 0;
  no->dados = p;
  if((*li) == NULL){//insere inicio
    no->prox = NULL;
    no->ant = NULL;
    *li = no;
    return 1;
  }
  else { //procura onde inserir
    Elem *ante, *atual = *li;
    while(atual != NULL && atual->dados.cep <p.cep){
      ante=atual;
      atual = atual->prox;
    }
    if(atual == *li){//insere no inicio
      no->ant = NULL;
      (*li)->ant = no;
      no->prox = (*li);
      *li = no;
    }
    else {
      no->prox = ante->prox;
      no->ant = ante;
      ante->prox = no;
      if(atual != NULL)
        atual->ant = no;
    }
    return 1;
  }

}

int remove_lista_inicio(Lista* li){
  if(li == NULL)
    return 0;
  if((*li) == NULL)
    return 0;

  Elem *no = *li;
  *li = no->prox;
  if(no->prox != NULL)
    no->prox->ant = NULL;

  free(no);
  return 1;
}

int remove_lista_final(Lista* li){
  if(li == NULL) return 0;
  if((*li) == NULL)//lista vazia
    return 0;

  Elem *no = *li;
  while(no->prox != NULL)
    no = no->prox;

  if(no->ant == NULL)//remover o primeiro e único
    *li = no->prox;
  else
    no->ant->prox = NULL;

  free(no);
  return 1;
}

int remove_lista(Lista* li, int cep){
  if(li == NULL) return 0;
  Elem *no = *li;
  while(no != NULL && no->dados.cep  != cep){
    no = no->prox;
  }
  if (no == NULL)// não encontrado
    return 0;
  if(no->ant == NULL)//remover o primeiro
    *li = no->prox;
  else
    no->ant->prox = no->prox;
  //não é o ultimo?
  if(no->prox != NULL)
    no->prox->ant = no->ant;
    free(no);
    return 1;
}

int consulta_lista_pos(Lista* li, int pos, struct Pessoa p){
  if(li == NULL || pos<= 0) return 0;
  Elem *no = *li;
  int i = 1;
  while (no != NULL && i<pos) {
    no = no->prox;
    i++;
  }
  if(no == NULL)
    return 0;
  else{
    p = no->dados;
  return 1;
  }
}
