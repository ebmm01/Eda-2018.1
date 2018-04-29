#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void rng(char *);

int main(int argc, char const *argv[]) {
    int linha,coluna;
    FILE *arquivo;
    char fName[50],letra;

    char asfalto[50],grama[50];

rng(asfalto);


for (int i = 1; i < 51; i++) {
    printf("%d ",asfalto[i]);
}

//Base de testes
 for (int i = 1; i < 51; i++){

   if (asfalto[i]<10)
    sprintf(fName,"asphalt/asphalt_0%d.txt",asfalto[i]);

   else
    sprintf(fName,"asphalt/asphalt_%d.txt",asfalto[i]);

    arquivo = fopen(fName, "r");
    if (arquivo == NULL)
       {
         printf("Não foi possível abrir o arquivo %s \n",fName);
         system("pause");
         exit(1);
       }
  // process your data here
  linha = coluna = 0;
    while((letra=fgetc(arquivo))!=EOF){
          if (letra=='\n'){
            linha++;
          }
          else if (linha==0 && letra == ';'){
            coluna++;
          }
        }
        coluna++;

        printf("\nArquivo %s \nLinhas: %d \n Colunas: %d \n",fName, linha,coluna);

    rewind(arquivo);
    fclose(arquivo);
  }  //fim da base de testes



    return 0;

}

void rng(char *array){

  srand(time(NULL));//garante que a cad vez que eu rodar o programa o rng será diferente

  printf("\n Vetor original: \n");
  for (int i = 1; i < 51; i++) {     // fill array
      array[i] = i;
      printf("%d ", array[i]);
  }

  printf("Esse é o vetor final:\n");

  for (int i = 1; i < 51; i++) {    // shuffle array

    int temp = array[i];
    int randomIndex = rand() % 50;

      array[i]           = array[randomIndex];
      array[randomIndex] = temp;
    }

printf("\n");

}
