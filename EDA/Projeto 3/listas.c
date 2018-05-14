#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void menu();

typedef struct Contatos
{
        char nome[100];
        char Celular[10];
        char Endereco[100];
        int cep;

} Contato;

struct Agenda
{
  Contato *conteudo;
  struct Agenda*ant;
  struct Agenda*seg;
};
typedef struct Agenda pessoa;


void inserir(pessoa **lst, Contato *p){
     pessoa *nova;
     pessoa *aux;
     nova = (pessoa*)malloc(sizeof(pessoa*));
     nova->conteudo = p;
     nova->seg = NULL ;
     nova->ant = (*lst);



     if((*lst)->seg == NULL){
        (*lst)->seg=nova;

     }
     else{
        aux = (*lst)->seg;
        while(aux->seg != NULL){
            aux= aux->seg;
        }
        aux->seg=nova;
        nova->ant= aux;

     }


}
/* insere entre lst  e a seguinte ou seja no inicio */

void inserir_inicio(pessoa **lst, Contato *p){
     pessoa *nova;
     nova = (pessoa*)malloc(sizeof(pessoa*));
     nova->conteudo = p;
     nova->seg = (*lst) ;
     nova->seg = (*lst)->seg;
     (*lst)->seg = nova;
     if(nova->seg !=NULL){
        nova->seg->ant=nova;
     }
}
void deletar( pessoa **lst){
   pessoa *p;
   p = (*lst);
   if((*lst)->seg ==NULL){
    printf("lista vazia");
   }
   else
    {
        p->seg->ant = *lst;
        p->ant->seg = p->seg;
        free(p);
   }
}
void imprimir(pessoa*lst){
    pessoa*p;
    p = lst->seg;
    while(p != NULL){
        printf( "%s", p->conteudo->nome);
        p = p->seg;
    }
}


int main(int argc, char const *argv[]) {
FILE *arquivo;
int c;
char escolha;
pessoa*lst;

lst = (pessoa*)malloc(sizeof(pessoa*));
lst->seg = NULL;
lst->ant = NULL;
lst->conteudo = 0;

  Contato c1,c2,c3;

  strcpy(c1.nome, "Dssd");
  strcpy(c2.nome, "joao");
  strcpy(c3.nome, "pessoa");

 arquivo = fopen("contatos.txt", "a+");
 if (arquivo) {
     while ((c = getc(arquivo)) != EOF)
         putchar(c);
     fclose(arquivo);
 }
 menu();

 while(escolha!='5'){

 scanf("%s",&escolha );

   switch(escolha){

     case '1':
     inserir_inicio(&lst, &c3);
inserir_inicio(&lst, &c2);
       break;

     case '2':
       menu();
      break;

     case '3':
     imprimir(lst);
       break;

     case '4':
       break;

     case '5':
       break;

     default:
     system("clear");
     menu();
     printf("Opção inválida; Tente novamente.\n");
   }

 }

}

void menu(){

  system("clear");

  printf("\n Agenda \n");
  printf("\n 1 - Inserir novo registro");
  printf("\n 2 - Remover registros");
  printf("\n 3 - Visualizar registros");
  printf("\n 4 - Visualizar todos os registros");
  printf("\n 5 - Sair");
  printf("\n");

}
