#include <stdlib.h>
#include <stdio.h>

void menu();

typedef struct Contatos
{
        char nome[100];
        char celular [10];
        char Endereco [100];
        int cep;

} Contato;

struct Agenda
{
  Contato *conteudo;
  struct Agenda*ant;
  struct A*seg;
};
typedef struct Agenda pessoa;

int main(int argc, char const *argv[]) {
FILE *arquivo;
int c;
char escolha;



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
       break;

     case '2':
       menu();
      break;

     case '3':
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
