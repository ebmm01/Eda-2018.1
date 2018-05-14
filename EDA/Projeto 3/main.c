#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listaDE.h"

void menu();

int main(int argc, char const *argv[]) {
  printf("TESTE");
FILE *arquivo;
int c, linhas=0;
char escolha= '0', letra;
int x;
Lista *li;
li = cria_lista();

struct Pessoa *dados_pessoa;
dados_pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));
dados_pessoa->nome = "Egzona";
dados_pessoa->Celular = "12345678";
dados_pessoa->Endereco = "Rua de sei la onde";
dados_pessoa->cep = 123445656;
printf("TESTE");
insere_lista_ordenada(li, *dados_pessoa);
printf("TESTE");
free(dados_pessoa);
dados_pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));
dados_pessoa->nome = "TEste";
dados_pessoa->Celular = "5343345";
dados_pessoa->Endereco = "PRaça sasasdfhsa dsf ds";
dados_pessoa->cep = 21212122;
insere_lista_ordenada(li, *dados_pessoa);
free(dados_pessoa);
dados_pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));
dados_pessoa->nome = "123123123";
dados_pessoa->Celular = "123123123";
dados_pessoa->Endereco = "123123123123";
dados_pessoa->cep = 1222222;
insere_lista_ordenada(li, *dados_pessoa);
imprimir(li);
//Libera_lista(li);
/*int x = insere_lista_inicio(li, dados_pessoa);
int x = insere_lista_final(li, dados_pessoa);
int x = insere_lista_ordenada(li, dados_pessoa);
int x = remove_lista_inicio(li);
int x = remove_lista_final(li);
int x = remove_lista(li, cep_pessoa);
int x = consulta_lista_pos(li,posicao, &dados_pessoa);*/


 arquivo = fopen("contatos.txt", "r");
char linha1[100];

 while((letra=fgetc(arquivo))!=EOF){
      if (letra=='\n' ){
        linhas++;
      }
  }

printf("%d\n",linhas );
 /*while(escolha!='5'){
int id=0;
 scanf("%s",&escolha );

   switch(escolha){

     case '1':

     cont = (Contato*)malloc(sizeof(Contato));
     char *name, *telefone, *local;
     int *cep;
     name = (char*)malloc(100*sizeof(char));
     telefone = (char*)malloc(10*sizeof(char));
     local = (char*)malloc(100*sizeof(char));
     cep = (int*)malloc(100*sizeof(int));
     id++;
     printf("Insira o nome:\n");
     scanf (" %[^\n]s", name);
     printf("Insira o telefone:\n");
     scanf (" %[^\n]s", telefone);
     printf("Insira o endereço:\n");
     scanf (" %[^\n]s", local);
     printf("Insira o cep:\n");
     scanf (" %d", cep);
     cont->nome = name;
     cont->Celular = telefone;
     cont->Endereco = local;
     cont->cep = *cep;
     inserir(&lst, cont);
       break;


     case '2':
       menu();
      break;

     case '3':
     imprimir(lst);
       break;

     case '4':
     deletar(&lst, cont);
       break;

     case '5':
       break;

     default:
     menu();
     printf("Opção inválida; Tente novamente.\n");

     free(cont);
     free(name);
     free(telefone);
     free(local);
     free(cep);
   }

 }*/

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
