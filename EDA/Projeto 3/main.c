#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listaDE.h"


int main(int argc, char const *argv[]) {
  int  linhas=0;
  char escolha= '0', letra;
  Lista *li;
  li = cria_lista();
  char *name;

  struct Pessoa *dados_pessoa;

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
 if (!(lines = malloc (linhas * sizeof *lines))) {
     fprintf (stderr, "Erro: memória não suficiente'.\n");
     return 1;
 }

    while (n < linhas && fgets (lines[n], 100, fp)) {
        char *p = lines[n];
        for (; *p && *p != '\n'; p++) {}
        *p = 0, n++;
    }
    if (fp != stdin) fclose (fp);

    //for (i = 0; i < n; i++) printf (" line[%2d] : '%s'\n", i + 1, lines[i]);

    abre_arquivo(lines, n,  li);

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
     {
      name = (char *)malloc(101*sizeof(char));

      int verify = 0;

      do{
        printf("Nome a ser apagado: ");

        scanf(" %[^\n]s", name);
        verify = validar_nome(name);
        if (verify != 1) {
          printf("Nome não pode passar 100 caracteres!\n");
        }
     }while(verify != 1);

      remove_lista(li, name);
      free(name);
    }

      break;

     case '3':
     {
       struct Pessoa *pessoa;
       pessoa = (struct Pessoa*)malloc(sizeof(struct Pessoa));
       name = (char *)malloc(101*sizeof(char));
       int verify;
         verify = 0;
       do{
         printf("Nome a ser pesquisada: ");

         scanf(" %[^\n]s", name);
         verify = validar_nome(name);
         if (verify != 1) {
           printf("Nome não pode passar 100 caracteres!\n");
         }
       }while(verify != 1);

       if(consulta_lista_nome(li, name, pessoa) == 1){
         printf("\n");
         printf(" Nome: %s \n", pessoa->nome);
         printf(" celular: %s \n", pessoa->Celular);
         printf(" Endereco: %s \n", pessoa->Endereco);
         printf(" Cep: %d \n", pessoa->cep);
         printf(" Nascimento: %s \n\n", pessoa->Data);

       }

     else{
       printf("Não há contatos com este nome! \n");
     }

     free(pessoa);
     free(name);

   }

   break;

    case '4':{
    imprimir(li);
    break;

     case '5':
     salva_arquivo(li);
     Libera_lista(li);
       break;

     default:
     menu();
     printf("Opção inválida; Tente novamente.\n");


    }

    }
  }
}
