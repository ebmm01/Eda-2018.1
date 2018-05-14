#include <stdlib.h>
#include <stdio.h>
#include "listaDE.h"

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
//isso vai ser o programa principal
int main() {
  Lista *li;
  li = cria_lista();
  Libera_lista(li);
  /*int x = insere_lista_inicio(li, dados_pessoa);
  int x = insere_lista_final(li, dados_pessoa);
  int x = insere_lista_ordenada(li, dados_pessoa);
  int x = remove_lista_inicio(li);
  int x = remove_lista_final(li);
  int x = remove_lista(li, cep_pessoa);*/

  return 0;
}
