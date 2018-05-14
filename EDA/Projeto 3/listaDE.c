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
//isso vai ser o programa principal
int main() {
  Lista *li;
  li = cria_lista();
  Libera_lista(li);
  return 0;
}
