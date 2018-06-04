#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "filas.h"


int main() {

  time_t now;
  struct tm *now_tm;
  int hour,min, comb0;
  now = time(NULL);
  now_tm = localtime(&now);
  hour = now_tm->tm_hour;
  min = now_tm->tm_min;
  Fila *fi, *pouso,*decolagem;
  fi = cria_Fila();
  pouso = cria_Fila();
  decolagem = cria_Fila();

// Database
  char db[][7] = {
  "VG3001", "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009",
  "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012",
  "TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002",
  "AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001",
  "LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601", "TT4500",
  "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392", "GF4681",
  "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065", "LF0978",
  "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510", "TT1020",
  "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609", "KL5610", "KL5611",
  "AZ1008"
  };

srand(time(NULL));

int NApro = aleatorio(10,32);
int NDec = aleatorio(10,32);
int NVoos = NApro + NDec;

for(int i=0;i<NApro;i++)
    insere_Voo(fi,db[i],'a',0,1);

for(int i=NApro;i<NVoos;i++)
    insere_Voo(fi,db[i],'d',0,1);

pouso = gerencia_Fila(fi, pouso, 'a');
decolagem = gerencia_Fila(fi, decolagem, 'd');
libera_Fila(fi);


  printf("---------------------------------------------------------------------------------\n");
  printf("Aeroporto Internacional de Brasília\n");
  printf("Hora Inicial: %d:%d\n",hour,min);
  printf("Fila de Pedidos: [código do voo – P/D – prioridade]\n");
  printf("Número de voos: %d\n", NVoos);
  printf("Número de aproximações: %d\n", NApro);
  printf("Número de decolagens: %d\n", NDec);
  printf("---------------------------------------------------------------------------------\n\n\n");
  printf("Listagem de eventos:\n\n\n");

  int verifica_gas = 1;
  int pista[3] = {0,0,0};

  while(pouso->inicio != NULL || decolagem->inicio != NULL) {

    int comb0 = 0;

    comb0 = verifica_comb0(pouso);

    if(comb0 >= 3) {
      printf("\n\nALERTA GERAL DE DESVIO DE AERONAVE\n\n\n");
    }

    //Pista 1//
    if(pista[0] == 0) {
      if(pouso->inicio != NULL) {
        procedimento(pouso,1, hour, min,'p');
        pista[0] = 3;
      }
      else if(decolagem->inicio != NULL){
        procedimento(decolagem,1, hour, min, 'd');
        pista[0] = 2;
      }
    }

    //Pista 2//
    if(pista[1] == 0) {
      if(pouso->inicio != NULL) {
        procedimento(pouso,2, hour, min, 'p');
        pista[1] = 3;
      }
      else if(decolagem->inicio != NULL) {
        procedimento(decolagem,2, hour, min, 'd');
        pista[1] = 2;
      }
    }


    //Pista 3//
    if(comb0 >= 3) {
      if(pista[2] == 0) {
        procedimento(pouso,3, hour, min, 'p');
        pista[2] = 3;
      }
      Elem *queda = pouso->inicio;
      while(queda != NULL) {
        if(queda->dados.gasol == 0) {
          printf("ALERTA CRÍTICO: Aeronave irá cair\n");
          printf("Código do voo: %s\n", queda->dados.codigo);
          printf("Status: [Aeronave Caiu]\n\n");
          remove_Fila(pouso);
        }
        queda = queda->prox;
      }
    }

    if(pista[2] == 0) {
      if(decolagem->inicio != NULL) {
        procedimento(decolagem,3, hour, min, 'd');
        pista[2] = 2;
      }
    }

    if(pista[0] > 0) pista[0]--;

    if(pista[1] > 0) pista[1]--;

    if(pista[2] > 0) pista[2]--;

    min+= 5;
    calc_Hora(&hour, &min);

    if(verifica_gas%10 == 0) {
      reduz_comb(pouso);
    }
    verifica_gas++;

  }

  libera_Fila(pouso);
  libera_Fila(decolagem);

  printf("----Final do programa-------------------------------------------------\n");
  return 0;
}
