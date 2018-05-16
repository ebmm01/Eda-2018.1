#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listaDE.h"


int main(int argc, char const *argv[]) {
  int  linhas=0;
  char escolha= '0', letra;
  Lista *li;
  li = cria_lista();

  //Daqui pra baixo são meio que testes pra ver se funciona, apenas isso
  struct Pessoa *dados_pessoa;

  //Funções da biblioteca
  /*int x = insere_lista_inicio(li, dados_pessoa);
  int x = insere_lista_final(li, dados_pessoa);
  int x = insere_lista_ordenada(li, dados_pessoa);
  int x = remove_lista_inicio(li);
  int x = remove_lista_final(li);
  int x = remove_lista(li, cep_pessoa);
  int x = consulta_lista_pos(li, posicao, &dados_pessoa);
  int x = consulta_lista_cep(li, posicao, &dados_pessoa);*/


  FILE *fp = fopen("contatos.txt", "r");
  if (fp == NULL){
    printf("Arquivo contatos.txt não encontrado. Criando um..." );
    fp = fopen("contatos.txt", "w");
  }

  while((letra=fgetc(fp))!=EOF){
       if (letra=='\n' ){
         linhas++;
       }
   }linhas++;

printf("\n%d\n",linhas );
rewind(fp);
char (*lines)[101] = NULL;
 int i, n = 0;
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

    //for (i = 0; i < n; i++) printf (" line[%2d] : '%s'\n", i + 1, lines[i]);

  int a0 = 0,a1 = 1,a2 =2,a3 =3, a4=4, a5=5;

  for (i = 0; i < n; i++){
    if(i==a0){
      dados_pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));
      dados_pessoa->nome =lines[i] ;
     a0 += 6;
    }
    if(i==a1){
      dados_pessoa->Celular = lines[i];
     a1 += 6;
    }
    if(i==a2){
      dados_pessoa->Endereco = lines[i];
     a2 += 6;
    }
    if(i==a3){
      int num1 = atoi(lines[i]);

      dados_pessoa->cep =num1;
    	a3+= 6;
    }
    if(i==a4){
      dados_pessoa->Data = lines[i];
     a4 += 6;
    }

    if(i==a5){
  	insere_lista_final(li, *dados_pessoa);
    free(dados_pessoa);
     a5 += 6;
    }

  }
  a0 = 0,a1 = 1,a2 =2,a3 =3, a4=4, a5=5;
  imprimir(li);

  free (lines);

 while(escolha!='5'){
  int id=0;
 menu();
 scanf("%s",&escolha );

   switch(escolha){

     case '1':
      criar_contato(li);
       break;


     case '2':
      break;

     case '3':
     imprimir(li);
       break;

     case '4':
       break;

     case '5':
     salva_arquivo(li);
       break;

     default:
     menu();
     printf("Opção inválida; Tente novamente.\n");


   }

 }

}
