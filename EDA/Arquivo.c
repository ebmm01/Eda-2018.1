#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {

  int i,j,
      linha=0, //contador de linhas.
      coluna=1, // contador de colunas. Iniciado em 1 pois não há ';' final.
      **mat; //declaração da matriz (ponteiro de ponteiro).

  char letra;
  FILE *arquivo;
  arquivo = fopen("test.txt", "r");

//verifica se o arquivo está vazio.
  if(arquivo == NULL){
     printf("Erro: arquivo em branco!\n");
  }

while((letra=fgetc(arquivo))!=EOF){
      if (letra=='\n'){
        linha++;
      }
      else if (linha==1 && letra == ';'){
        coluna++;
      }
  }

rewind(arquivo);

  mat = (int**)malloc(linha*sizeof(int *));
  for(i = 0; i<linha; i++){
    *(mat+i) = (int*)malloc(coluna*sizeof(int));}

    for (i=0;i<linha;i++){
      for (j=0;j<coluna;j++){
         fscanf(arquivo,"%d%c", (*(mat+i)+j),&letra);
      }
  }

    for (i=0;i<linha;i++){
      for (j=0;j<coluna;j++){
        printf(" %d", *(*(mat+i)+j));
      }
      printf("\n");
  }


//Lembrar de liberar a memória da matriz (free)
  printf("Linhas: %d \n Colunas: %d", i,j);
  fclose(arquivo);

  return 0;
}
