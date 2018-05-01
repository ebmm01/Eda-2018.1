#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void rng(char *);
void ilbp(int**, double**, int, int,int );
void glcm(int **, int, int, int, int, double **, int, int);
void manipula_arquivo(FILE **,double**,int , int , int ,int **, char );
void normaliza(double **, double **,  int);
void calcula_media(double **, double*);

int main(int argc, char const *argv[]) {
    int linha,coluna,n=0,
        **matAsfalto,
        **matGrama;

    double **vetresultanteasfalto, //vetor resultante.
           **vetnormalizadoasfalto,
           *vetfinalasfalto,
           **vetresultantegrama, //vetor resultante.
           **vetnormalizadograma,
           *vetfinalgrama;

    FILE *arquivoA, *arquivoG;
    char fNameAsfalto[50],fNameGrama[50],letra;

    char asfalto[50],grama[50];

rng(asfalto);
rng(grama);

for (int i = 1; i < 51; i++) {
    printf("%d ",asfalto[i]);
}
for (int i = 1; i < 51; i++) {
    printf("%d ",grama[i]);
}
//alocao vetor resultante
vetresultanteasfalto = (double**)malloc(50*sizeof(double *));
for(int i = 0; i<51; i++)
  *(vetresultanteasfalto+i) = (double*)malloc(536*sizeof(double));

vetresultantegrama = (double**)malloc(50*sizeof(double *));
for(int i = 0; i<51; i++)
  *(vetresultantegrama+i) = (double*)malloc(536*sizeof(double));

//alocao vetor normalizado
vetnormalizadoasfalto = (double**)malloc(50*sizeof(double *));
for(int i = 0; i<51; i++)
  *(vetnormalizadoasfalto+i) = (double*)malloc(536*sizeof(double));

vetnormalizadograma = (double**)malloc(50*sizeof(double *));
for(int i = 0; i<51; i++)
  *(vetnormalizadograma+i) = (double*)malloc(536*sizeof(double));

//alocao vetor final asfalto
vetfinalasfalto = (double*)malloc(536*sizeof(double));
vetfinalgrama = (double*)malloc(536*sizeof(double));

//Base de testes
 for (int i = 1; i < 26 ; i++){

   if (asfalto[i]<10 || grama[i]<10){
    sprintf(fNameAsfalto,"asphalt/asphalt_0%d.txt",asfalto[i]);
    sprintf(fNameGrama,"grass/grass_0%d.txt",grama[i]);
  }
   else if (asfalto[i]>=10 || grama[i]>=10){
    sprintf(fNameAsfalto,"asphalt/asphalt_%d.txt",asfalto[i]);
    sprintf(fNameGrama,"grass/grass_%d.txt",grama[i]);
  }
    arquivoA = fopen(fNameAsfalto, "r");
    arquivoG = fopen(fNameGrama, "r");

    if (arquivoA  == NULL || arquivoG == NULL)
       {
        if (arquivoA)
         printf("Não foi possível abrir o arquivo %s \n",fNameAsfalto);
        else
        printf("Não foi possível abrir o arquivo %s \n",fNameGrama);

         system("pause");
         exit(1);
       }
  // Processamento de dados
    linha = 0, coluna = 1;
    while((letra=fgetc(arquivoG))!=EOF){
          if (letra=='\n'){
            linha++;
          }
          else if (linha==0 && letra == ';'){
            coluna++;
          }
    }
    while((letra=fgetc(arquivoA))!=EOF){
          if (letra=='\n'){
            linha++;
          }
          else if (linha==0 && letra == ';'){
            coluna++;
          }
    }
    rewind(arquivoA);
    rewind(arquivoG);
    //aloca a matriz de ponteiros
    matGrama = (int**)malloc(linha*sizeof(int *));
    for(int i = 0; i<linha; i++)
      *(matGrama+i) = (int*)malloc(coluna*sizeof(int));

    //aloca a matriz de ponteiros
    matAsfalto = (int**)malloc(linha*sizeof(int *));
    for(int i = 0; i<linha; i++)
      *(matAsfalto+i) = (int*)malloc(coluna*sizeof(int));

     manipula_arquivo(&arquivoA, vetresultanteasfalto, linha,  coluna, n,matAsfalto, letra);
     manipula_arquivo(&arquivoG, vetresultantegrama, linha,  coluna, n,matGrama, letra);

     glcm(matAsfalto , linha, coluna, 0, -1, vetresultanteasfalto, 512, n); // esquerda
     glcm(matGrama , linha, coluna, 0, -1, vetresultantegrama, 512, n); // esquerda
     printf("\n");
     glcm(matAsfalto, linha, coluna, 0, +1, vetresultanteasfalto, 515, n); // direita
     glcm(matGrama, linha, coluna, 0, +1, vetresultantegrama, 515, n); // direita
     printf("\n");
     glcm(matAsfalto , linha, coluna, -1, 0, vetresultanteasfalto, 518, n); // cima
     glcm(matGrama , linha, coluna, -1, 0, vetresultantegrama, 518, n); // cima
     printf("\n");
     glcm(matAsfalto , linha, coluna, +1, 0, vetresultanteasfalto, 521, n); // baixo
     glcm(matGrama , linha, coluna, +1, 0, vetresultantegrama, 521, n); // baixo
     printf("\n");
     glcm(matAsfalto , linha, coluna, -1, -1, vetresultanteasfalto, 524, n); // diagonal superior esquerda
     glcm(matGrama , linha, coluna, -1, -1, vetresultantegrama, 524, n); // diagonal superior esquerda
     printf("\n");
     glcm(matAsfalto , linha, coluna, -1, +1, vetresultanteasfalto, 527, n); // diagonal superior direita
     glcm(matGrama , linha, coluna, -1, +1, vetresultantegrama, 527, n); // diagonal superior direita
     printf("\n");
     glcm(matAsfalto , linha, coluna, +1, +1, vetresultanteasfalto, 530, n); // diagonal inferior direita
     glcm(matGrama , linha, coluna, +1, +1, vetresultantegrama, 530, n); // diagonal inferior direita
     printf("\n");
     glcm(matAsfalto , linha, coluna, +1, -1, vetresultanteasfalto, 533, n); // diagonal inferior esquerda
     glcm(matGrama , linha, coluna, +1, -1, vetresultantegrama, 533, n); // diagonal inferior esquerda
     printf("\n");
     normaliza(vetresultanteasfalto, vetnormalizadoasfalto, n);
     normaliza(vetresultantegrama, vetnormalizadograma, n);

     fclose(arquivoA);
     fclose(arquivoG);

    n+=1;

    printf("\nArquivo %s \nLinhas: %d \n Colunas: %d \n",fNameAsfalto, linha,coluna);
    printf("\nArquivo %s \nLinhas: %d \n Colunas: %d \n",fNameGrama, linha,coluna);
    //libera a matriz mat
    for (int i=0;i<linha;i++){
           free(*(matAsfalto+i));
           free(*(matGrama+i));
    }
           free(matAsfalto);
           free(matGrama);

  }  //fim da base de testes

  printf("Normalizando ...\n" );
  printf("Normalizando ...\n" );
  printf("Normalizando ...\n" );
  printf("Normalizando ...\n" );

calcula_media(vetnormalizadoasfalto,vetfinalasfalto);
calcula_media(vetnormalizadograma,vetfinalgrama);

//libera o vetor resultante
for (int i=0;i<50;i++){
  free(*(vetresultanteasfalto+i));
  free(*(vetresultantegrama+i));
}
free(vetresultanteasfalto);
free(vetresultantegrama);

 //libera o vetor normalizado
 for (int i=0;i<50;i++){
  free(*(vetnormalizadoasfalto+i));
  free(*(vetnormalizadograma+i));
}
 free(vetnormalizadoasfalto);
 free(vetnormalizadograma);

  //libera o vetor final
  free(vetfinalasfalto);
  free(vetfinalgrama);

    return 0;

}

void rng(char *array){

  srand(( unsigned )time( 0 ) * 100 );//garante que a cada vez que eu rodar o programa o rng será diferente

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

void ilbp(int **mat,double **vetresul,int linha,int coluna,int n){

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
(*(*(vetresul+n)+decimal))++;
}

void manipula_arquivo(FILE **arquivo, double **vetresul,int linha, int coluna, int n, int **mat, char letra){


  //salva o arquivo na matriz de ponteiros
  for (int i=0;i<linha;i++){
        for (int j=0;j<coluna;j++){
           fscanf(*arquivo,"%d%c", (*(mat+i)+j),&letra);
        }
  }
  //aplica as métricas ilbp no arquivo
  for (int i=1;i<linha-1;i++){
    for (int j=1;j<coluna-1;j++){
      ilbp(mat,vetresul ,i,j,n);
    }
  }

}

void glcm(int **img , int L, int C, int pos_lin, int pos_col, double **vetresul, int pos_freq,int n){
  int **glcm, i, j, lin_glcm, col_glcm;
  double energia = 0.0, contraste = 0.0, homogeneidade = 0.0;

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

    *(*(vetresul + n)+ pos_freq) = contraste;
    *(*(vetresul + n)+ (pos_freq + 1)) = energia;
    *(*(vetresul + n)+ (pos_freq + 2)) = homogeneidade;

    printf("Cont: %.0lf ener: %.0lf homo: %.0lf \n", contraste, energia, homogeneidade);

   for (i=0;i<256;i++)       //libera as linhas da matriz
      free(*(glcm+i));

    free(glcm);    // libera o vetor de ponteiros


}
void normaliza(double **vetresul, double **vetnormalizadoasfalto, int n){
  int i = 0;
  double menor = 999999999, maior = 0;

    for(i = 0; i < 536; i++){
      if(*(*(vetresul + n)+ i) > maior){
          maior = *(*(vetresul + n)+ i);
      }
      if(*(*(vetresul + n)+ i) < menor){
        menor = *(*(vetresul + n)+ i);
      }

    }
    for(i = 0; i < 536; i++){
      *(*(vetnormalizadoasfalto + n)+ i) = (*(*(vetresul + n)+ i) - menor) / (maior - menor);
    }
    printf("Menor: %f\n Maior: %f\n", menor, maior );

}

void calcula_media(double **vetnormalizadoasfalto, double *vetfinalasfalto){
  int i,j=0;
  double *media;

  media = (double *) calloc(536, sizeof (double));

  for(i=0;i<50;i++){
    for(j=0;j<536;j++){
      *(media+j) += (*(*(vetnormalizadoasfalto + i)+ j));
    }
  }

  for(j=0;j<536;j++){
    *(vetfinalasfalto+j)= *(media+j)/50;
  }
  printf("Médias:::::::\n" );

  for(j=0;j<536;j++){
    printf(" %lf", *(vetfinalasfalto+j));
  }
  free(media);
}
