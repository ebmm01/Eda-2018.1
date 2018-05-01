#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void rng(char *);
void ilbp(int**, float**, int, int,int );
void glcm(int **, int, int, int, int, float **, int, int);
void manipula_arquivo(FILE **,float**,int , int , int ,int **, char );

int main(int argc, char const *argv[]) {
    int linha,coluna,n=0,
        **mat;
    float **vetresultante; //vetor resultante.
    FILE *arquivo;
    char fName[50],letra;

    char asfalto[50],grama[50];

 rng(asfalto);


for (int i = 1; i < 51; i++) {
    printf("%d ",asfalto[i]);
}

//alocao vetor resultante
vetresultante = (float**)malloc(50*sizeof(float *));
for(int i = 0; i<51; i++)
  *(vetresultante+i) = (float*)malloc(536*sizeof(float));

//Base de testes
 for (int i = 1; i < 51; i++){

   if (asfalto[i]<10)
    sprintf(fName,"grass/grass_0%d.txt",asfalto[i]);

   else
    sprintf(fName,"grass/grass_%d.txt",asfalto[i]);

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
        rewind(arquivo);
        //aloca a matriz de ponteiros
        mat = (int**)malloc(linha*sizeof(int *));
        for(int i = 0; i<linha; i++)
          *(mat+i) = (int*)malloc(coluna*sizeof(int));


           manipula_arquivo(&arquivo, vetresultante, linha,  coluna, n,mat, letra);
           glcm(mat , linha, coluna, 0, -1, vetresultante, 512, n); // esquerda
           printf("\n");
           glcm(mat, linha, coluna, 0, +1, vetresultante, 515, n); // direita
           printf("\n");
           glcm(mat , linha, coluna, -1, 0, vetresultante, 518, n); // cima
           printf("\n");
           glcm(mat , linha, coluna, +1, 0, vetresultante, 521, n); // baixo
           printf("\n");
           glcm(mat , linha, coluna, -1, -1, vetresultante, 524, n); // diagonal superior esquerda
           printf("\n");
           glcm(mat , linha, coluna, -1, +1, vetresultante, 527, n); // diagonal superior direita
           printf("\n");
           glcm(mat , linha, coluna, +1, +1, vetresultante, 530, n); // diagonal inferior direita
           printf("\n");
           glcm(mat , linha, coluna, +1, -1, vetresultante, 533, n); // diagonal inferior esquerda
           printf("\n");

    fclose(arquivo);
    n+=1;
    printf("\nArquivo %s \nLinhas: %d \n Colunas: %d \n",fName, linha,coluna);
    //libera a matriz mat
    for (int i=0;i<linha;i++)
           free(*(mat+i));

           free(mat);

  }  //fim da base de testes
  for(int i =0; i<50;i++){
    for(int j =0; j<536;j++){
      printf(" %.0f", *(*(vetresultante+i)+j));
    }
        printf("\n");
  }
  //libera o vetor resultante
    for (int i=0;i<50;i++)
      free(*(vetresultante+i));

     free(vetresultante);

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

void ilbp(int **mat,float **vetresultante,int linha,int coluna,int n){

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
(*(*(vetresultante+n)+decimal))++;
}

void manipula_arquivo(FILE **arquivo, float **vetresultante,int linha, int coluna, int n, int **mat, char letra){


  //salva o arquivo na matriz de ponteiros
  for (int i=0;i<linha;i++){
        for (int j=0;j<coluna;j++){
           fscanf(*arquivo,"%d%c", (*(mat+i)+j),&letra);
        }
  }
  //aplica as métricas ilbp no arquivo
  for (int i=1;i<linha-1;i++){
    for (int j=1;j<coluna-1;j++){
      ilbp(mat,vetresultante ,i,j,n);
    }
  }

}

void glcm(int **img , int L, int C, int pos_lin, int pos_col, float **vetresultante, int pos_freq,int n){
  int **glcm, i, j, lin_glcm, col_glcm;
  float energia = 0.0, contraste = 0.0, homogeneidade = 0.0;

  glcm = (int**)calloc(256,sizeof(int *));

  for(i = 0; i<256; i++)                         //declaração da matriz
    *(glcm+i) = (int*)calloc(256,sizeof(int));


    for(i = 1; i<L - 1; i++){
      for(j = 1; j<C - 1; j++){     //verificar toda a posição da matriz com seus vizinhos
          lin_glcm = img[i][j];
          col_glcm = img[i + pos_lin][j + pos_col]; // posição linha e posição coluna define para qual direção o glcm irá indicar cima/baixo/direita/esquerda..
          *(*(glcm+lin_glcm)+col_glcm) += 1;

        }
      }

      for (i = 0; i < 256; i++){
          for (j = 0; j < 256; j++){
          if(*(*(glcm + i)+ j) >= 1){
            contraste += (*(*(glcm + i)+ j)) * pow(i - j, 2);    //imprimir onde esta colocando na matriz
            energia += pow((*(*(glcm + i)+ j)), 2);
            homogeneidade += (*(*(glcm + i)+ j))/(pow(i - j, 2) + 1);
          }
        }
      }

    energia = sqrt(energia);

    *(*(vetresultante + n)+ pos_freq) = contraste;
    *(*(vetresultante + n)+ (pos_freq + 1)) = energia;
    *(*(vetresultante + n)+ (pos_freq + 2)) = homogeneidade;

    printf("Cont: %.0f ener: %.0f homo: %.0f \n", contraste, energia, homogeneidade);

   for (i=0;i<256;i++)       //libera as linhas da matriz
      free(*(glcm+i));

    free(glcm);    // libera o vetor de ponteiros


}
