#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listaDE.h"

void menu();

int main(int argc, char const *argv[]) {
  FILE *arquivo;
  int c, linhas=0;
  char escolha= '0', letra;
  int x;
  Lista *li;
  li = cria_lista();

  //Daqui pra baixo são meio que testes pra ver se funciona, apenas isso
  struct Pessoa *dados_pessoa;
  char name[100];
  //pessoa 1
  dados_pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));
  scanf(" %[^\n]s", name);
  dados_pessoa->nome = name;
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
  //Libera_lista(li);

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

    FILE *fp = fopen("contatos.txt", "r");

  while((letra=fgetc(fp))!=EOF){
       if (letra=='\n' ){
         linhas++;
       }
   }

printf("\n%d\n",linhas );
rewind(fp);
char (*lines)[100] = NULL; /* pointer to array of type char [MAXC] */
 int i, n = 0;
    if (fp == NULL) {  /* valida o arquivo para leitura */
        fprintf (stderr, "error: file open failed'.\n");
        return 1;
    }

    if (!(lines = malloc (linhas * sizeof *lines))) { /* alloca o max de arrays */
        fprintf (stderr, "error: virtual memory exhausted 'lines'.\n");
        return 1;
    }

    while (n < linhas && fgets (lines[n], 100, fp)) { /* lê cada linha */
        char *p = lines[n];                  /* designa o ponteiro */
        for (; *p && *p != '\n'; p++) {}     /* encontra o 1º '\n'  */
        *p = 0, n++;                         /* nul-termiante  */
    }
    if (fp != stdin) fclose (fp);   /* fecha o arquivo se ! stdin */

    /* exibe linhas */
    for (i = 0; i < n; i++) printf (" line[%2d] : '%s'\n", i + 1, lines[i]);
dados_pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));
for (i = 1; i < 5; i++){
  if(i==0+1)
    dados_pessoa->nome =lines[0] ;
  if(i==1+1)
    dados_pessoa->Celular = lines[i];
  if(i==2+1)
    dados_pessoa->Endereco = lines[i];
  if(i==4){
    int num1 = atoi(lines[3]);

    dados_pessoa->cep =num1 ;}
}
insere_lista_ordenada(li, *dados_pessoa);
imprimir(li);

free(dados_pessoa);
    free (lines);   /* free allocated memory */



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
