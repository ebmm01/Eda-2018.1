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
  menu();

  //Daqui pra baixo são meio que testes pra ver se funciona, apenas isso
  struct Pessoa *dados_pessoa;

  //pessoa 1
  dados_pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));
  dados_pessoa->nome = "Egzona";
  dados_pessoa->Celular = "12345678";
  dados_pessoa->Endereco = "Rua de sei la onde";
  dados_pessoa->cep = 123445656;
  insere_lista_ordenada(li, *dados_pessoa);
  free(dados_pessoa);

  //pessoa 2
  dados_pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));
  dados_pessoa->nome = "TEste";
  dados_pessoa->Celular = "5343345";
  dados_pessoa->Endereco = "PRaça sasasdfhsa dsf ds";
  dados_pessoa->cep = 21212122;
  insere_lista_ordenada(li, *dados_pessoa);
  free(dados_pessoa);

  //pessoa 3
  dados_pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));
  dados_pessoa->nome = "123123123";
  dados_pessoa->Celular = "123123123";
  dados_pessoa->Endereco = "123123123123";
  dados_pessoa->cep = 1222222;
  insere_lista_ordenada(li, *dados_pessoa);
  imprimir(li);
  Libera_lista(li);

  //Funções da biblioteca
  /*int x = insere_lista_inicio(li, dados_pessoa);
  int x = insere_lista_final(li, dados_pessoa);
  int x = insere_lista_ordenada(li, dados_pessoa);
  int x = remove_lista_inicio(li);
  int x = remove_lista_final(li);
  int x = remove_lista(li, cep_pessoa);
  int x = consulta_lista_pos(li, posicao, &dados_pessoa);
  int x = consulta_lista_cep(li, posicao, &dados_pessoa);*/

   //parte do arquivo, não implementada ainda
   arquivo = fopen("contatos.txt", "r");
    char linha1[100];

     while((letra=fgetc(arquivo))!=EOF){
          if (letra=='\n' ){
            linhas++;
          }
      }

printf("%d\n",linhas );

//menu incompleto
 /*while(escolha!='5'){
int id=0;
 scanf("%s",&escolha );

   switch(escolha){

     case '1':

       break;


     case '2':
      break;

     case '3':
       break;

     case '4':
       break;

     case '5':
       break;

     default:
     menu();
     printf("Opção inválida; Tente novamente.\n");


   }

 }*/

}
