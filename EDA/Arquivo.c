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
      int decimal=0;
      double media=0;

      //contador de média
      for (int i2=i -1;i2<i+ 2;i2++){
        for (int j2 =j -1; j2<j+ 2; j2++){
          media += *(*(mat+i2)+j2);
        }
      }//fim do contador de média.

      //cria a submatriz e aloca char.
      char *bit = (char *) calloc(9, sizeof (char));
      for (int i2=i -1;i2<i+ 2;i2++){
        for (int j2 =j -1; j2<j+ 2; j2++){
          if (*(*(mat+i2)+j2) > (media/9))
            *(*(submat+i2)+j2) = 1;
        }
      }//fim do criador da submatriz

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
      //fim do concatenador

      //verificador de decimal do bit original. Ver o que fazer com isso dps.
      for (int bitj=0; bitj<9; bitj++){
      if (bit[bitj] == '1') decimal = decimal * 2 + 1;
      else if (bit[bitj] == '0') decimal *= 2;}
      printf("Bit original: %s\n",bit);
      printf("decimal original: %d\n",decimal);

      //"shiftador".
      int dec = 0;
      for (int contador = 0; contador <8; contador ++){
        dec = 0;
        char bit2 = bit[0];
        for (int shiftj=0;shiftj<9;shiftj++){


          if (shiftj==8)
            bit[8]=bit2;
          else
            bit[shiftj]=bit[shiftj+1];
              //implementar um contador pro bit original tbm
            if (bit[shiftj] == '1') dec = dec * 2 + 1;
            else if (bit[shiftj] == '0') dec *= 2;



        }
        if (decimal>dec )
          decimal=dec;

        printf("Bit shiftado %d: %s\n",contador+1,bit);
        printf("%d\n", dec);

      }//fim do shiftador
      printf("O menor decimal é:%d\n", decimal);
      free(bit);

      printf("Posição: %dx%d (%d)\n",i,j, *(*(mat+i)+j));

    }
  }//fim do ilbp


  //Lembrar de liberar a memória da matriz (free)
  printf("Linhas: %d \n Colunas: %d \n", linha,coluna);
  fclose(arquivo);

  return 0;
}
