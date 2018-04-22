#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {

  int i,j,
      linha=0, //contador de linhas.
      coluna=1, // contador de colunas. Iniciado em 1 pois não há ';' final.
      **mat, //declaração da matriz (ponteiro de ponteiro).
      **submat, //declaração da submatriz do ilbp.
      **vetresultante; //vetor resultante.

  char letra;
  FILE *arquivo;
  arquivo = fopen("test.txt", "r");

  //Verifica se o arquivo está vazio.
  if(arquivo == NULL){
     printf("Erro: arquivo em branco!\n");
  }

  //Determina o número de linhas e colunas.
  while((letra=fgetc(arquivo))!=EOF){
        if (letra=='\n'){
          linha++;
        }
        else if (linha==1 && letra == ';'){
          coluna++;
        }
  }

  //retorna o ponteiro do arquivo para o início. Sem isso vai dar erro.
  rewind(arquivo);

  //aloca as linhas da matriz de ponteiros
  mat = (int**)malloc(linha*sizeof(int *));

  //aloca as colunas da matriz de ponteiros
  for(i = 0; i<linha; i++)
    *(mat+i) = (int*)malloc(coluna*sizeof(int));

  //alocação da matriz 3x3 submat que será usada no ilbp.
  submat = (int**)calloc(3,sizeof(int *));
  for(i = 0; i<3; i++)
    *(submat+i) = (int*)calloc(3,sizeof(int));

  //salva o arquivo na matriz de ponteiros
  for (i=0;i<linha;i++){
        for (j=0;j<coluna;j++){
           fscanf(arquivo,"%d%c", (*(mat+i)+j),&letra);
        }
  }

  //imprime a matriz na tela
  for (i=0;i<linha;i++){
    for (j=0;j<coluna;j++){
      printf(" %d", *(*(mat+i)+j));
    }
        printf("\n");
  }

  //ilbp
  for (i=1;i<linha-1;i++){
    for (j=1;j<coluna-1;j++){
      double media=0;
      for (int i2=-1;i2<2;i2++){
        for (int j2 = -1; j2<2; j2++){
          media += *(*(mat+(i+i2))+(j+j2));

          //lembrar de transformar tudo até a parte demarcada em uma função

          //até aqui
        }
      }
      //aqui idem
      char *bit = (char *) calloc(9, sizeof (char));
      for (int i =0; i<3; i++){
        for(int j=0;j<3;j++){
          if (*(*(mat+i)+j)> (media/9))
            *(*(submat+i)+j) = 1;
        }
      }
      //concatenador
      sprintf (bit, "%s%d",bit, *(*(submat+0)+0));
      sprintf (bit, "%s%d",bit, *(*(submat+0)+1));
      sprintf (bit, "%s%d",bit, *(*(submat+0)+2));
      sprintf (bit, "%s%d",bit, *(*(submat+1)+2));
      sprintf (bit, "%s%d",bit, *(*(submat+2)+2));
      sprintf (bit, "%s%d",bit, *(*(submat+2)+1));
      sprintf (bit, "%s%d",bit, *(*(submat+2)+0));
      sprintf (bit, "%s%d",bit, *(*(submat+1)+0));
      sprintf (bit, "%s%d",bit, *(*(submat+1)+1));

      printf("Bit original: %s\n",bit);

      //"shiftador".
        int dec = 0;
      for (int contador = 0; contador <8; contador ++){
        dec = 0;
        char bit2 = bit[0];
        for (j=0;j<9;j++){

          if (bit[j] == '1') dec = dec * 2 + 1;
          else if (bit[j] == '0') dec *= 2;


          if (j==8)
            bit[8]=bit2;
          else
            bit[j]=bit[j+1];


        }


        printf("%d\n", dec);
        printf("Bit shiftado %d: %s\n",contador+1,bit);
      }
      //fim do ilbp
    }
  }

  //imprime a matriz na tela
    for (i=0;i<linha;i++){
      for (j=0;j<coluna;j++){
        printf(" %d", *(*(submat+i)+j));
      }
          printf("\n");
    }

  //Lembrar de liberar a memória da matriz (free)
  printf("Linhas: %d \n Colunas: %d \n", i,j);
  fclose(arquivo);

  return 0;
}
