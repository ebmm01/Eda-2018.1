#include <stdlib.h>
#include <stdio.h>

void ilbp(int**, int, int);

int main(int argc, char const *argv[]) {

  int i,j,
      linha=0, //contador de linhas.
      coluna=1, // contador de colunas. Iniciado em 1 pois não há ';' final.
      **mat, //declaração da matriz (ponteiro de ponteiro).
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

    for (i=1;i<linha-1;i++){
      for (j=1;j<coluna-1;j++){
        ilbp(mat,i,j);
      }
    }//fim do ilbp




    //libera as linhas da matriz
    for (i=0;i<linha;i++)
           free(*(mat+i));

    free(mat);    // libera o vetor de ponteiros

    printf("Linhas: %d \n Colunas: %d \n", linha,coluna);
    fclose(arquivo);

    return 0;
}

void ilbp(int **mat,int linha,int coluna){

  int decimal=0,i,j,
  contl=0,contc=0;
       //declaração da submatriz do ilbp.
  double media=0;
  char submat[3][3],
       bit[9];


  //contador de média
  for ( i=linha-1 ;i<linha+2;i++){
    for ( j =coluna-1 ; j<coluna+2; j++){
      media += *(*(mat+(i))+(j));
    }
  }
  printf("Posição: %dx%d (%d)\n",linha,coluna, *(*(mat+linha)+coluna));
  //fim do contador de média.
  printf("Soma: %f\n Média: %f\n",media, media/9);

  //cria a submatriz e aloca char.
  for ( i=linha-1 ;i<linha+2;i++){
    for ( j =coluna-1 ; j<coluna+2; j++){
      if ( *(*(mat+(i))+(j)) > (media/9)){
        submat[contl][contc] = '1';
        contc++;}
      if ( *(*(mat+(i))+(j)) < (media/9)){
        submat[contl][contc] = '0';
        contc++;}

    }
  }

  //apagar isso aqui dps
  for ( i=0 ;i<3;i++){
    for ( j =0 ; j<3; j++){
        printf(" %c", submat[i][j]);
    }
    printf("\n" );
  }
  //apagar


  //concatenador
  bit[0]=submat[0][0];
  bit[1]=submat[0][1];
  bit[2]=submat[0][2];
  bit[3]=submat[1][2];
  bit[4]=submat[2][2];
  bit[5]=submat[2][1];
  bit[6]=submat[2][0];
  bit[7]=submat[1][0];
  bit[8]=submat[1][1];
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


}
