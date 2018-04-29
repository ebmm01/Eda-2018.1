#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void rng(char *);
void ilbp(int**, int, int);
void manipula_arquivo(FILE **,int , int ,int **, char );

int main(int argc, char const *argv[]) {
    int linha,coluna,
        **mat;
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
  // Processamento de dados
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

        //aloca a matriz de ponteiros
        mat = (int**)malloc(linha*sizeof(int *));
        for(int i = 0; i<linha; i++)
          *(mat+i) = (int*)malloc(coluna*sizeof(int));
          //libera a matriz mat

          manipula_arquivo(&arquivo,linha, coluna,mat, letra);

    rewind(arquivo);
    fclose(arquivo);
    printf("\nArquivo %s \nLinhas: %d \n Colunas: %d \n",fName, linha,coluna);
    for (int i=0;i<linha;i++)
           free(*(mat+i));

           free(mat);

  }  //fim da base de testes



    return 0;

}

void rng(char *array){

  srand(time(NULL));//garante que a cada vez que eu rodar o programa o rng será diferente

  printf("\n Vetor original: \n");
  for (int i = 1; i < 51; i++) {     // preenche o vetor
      array[i] = i;
      printf("%d ", array[i]);
  }

  printf("Esse é o vetor final:\n");

  for (int i = 1; i < 51; i++) {    // rng

    int temp = array[i];
    int randomIndex = rand() % 50;

      array[i]           = array[randomIndex];
      array[randomIndex] = temp;
    }

printf("\n");

}

void ilbp(int **mat,int linha,int coluna){

  int decimal=0,i,j,
  contl=0,contc=0;

  double media=0;

  char submat[3][3],
       bit[9];

  //contador de média
  for ( i=linha-1 ;i<linha+2;i++){
    for ( j =coluna-1 ; j<coluna+2; j++){
      media += *(*(mat+(i))+(j));
    }
  }

  //cria a submatriz de vetores( 0 e 1).
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

  //verificador de decimal do bit original. Ver o que fazer com isso dps.
  for (int bitj=0; bitj<9; bitj++){
  if (bit[bitj] == '1') decimal = decimal * 2 + 1;
  else if (bit[bitj] == '0') decimal *= 2;}

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

  }//fim do shiftador

}

void manipula_arquivo(FILE **arquivo,int linha, int coluna,int **mat, char letra){

  //salva o arquivo na matriz de ponteiros
  for (int i=0;i<linha;i++){
        for (int j=0;j<coluna;j++){
           fscanf(*arquivo,"%d%c", (*(mat+i)+j),&letra);
        }
  }
  //aplica as métricas ilbp no arquivo
  for (int i=1;i<linha-1;i++){
    for (int j=1;j<coluna-1;j++){
      ilbp(mat,i,j);
    }
  }

}
