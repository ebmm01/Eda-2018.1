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

//imprime_Fila(fi);
//printf("============================================\n" );
pouso = gerencia_Fila(fi, pouso, 'a');
//imprime_Fila(pouso);
//printf("============================================\n" );
decolagem = gerencia_Fila(fi, decolagem, 'd');
//imprime_Fila(decolagem);
printf("============================================\n" );
printf("Hora: %d:%d \n",hour, min );
/*min+= 3;
calc_Hora(&hour,&min);
printf("Hora: %d:%d \n",hour, min );*/

//("Tamanho da fila: %d\n",tamanho_Fila(fi));
//printf("Nvoos: %d \n NApro: %d\n NDec: %d\n", NVoos, NApro, NDec );
//printf("Tamanho da fila gerenciada: %d\n",tamanho_Fila(gerenciada));

/*while(1){
  insere_Voo(pista[0],
    gerenciada->inicio->dados.codigo,
    gerenciada->inicio->dados.status,
    gerenciada->inicio->dados.gasol,
    0);
  gerenciada = gerenciada->inicio->prox;
  insere_Voo(pista[1],
    gerenciada->inicio->dados.codigo,
    gerenciada->inicio->dados.status,
    gerenciada->inicio->dados.gasol,
    0);

}*/
//comb0 = verifica_comb0(pouso);
//printf(" Aviões com gasolina crítica: %d\n", comb0 );
//reduz_comb(pouso);
//comb0 = verifica_comb0(pouso);
//printf(" Aviões com gasolina crítica: %d\n", comb0 );
//imprime_Fila(pouso);
libera_Fila(fi);


  printf("---------------------------------------------------------------------------------\n");
  printf("Aeroporto Internacional de Brasília\n");
  printf("Hora Inicial: %d:%d\n",hour,min);
  printf("Fila de Pedidos: [código do voo – P/D – prioridade]\n");
  //printf("NVoos: %d\n", nVoos);
  //printf("Naproximações: %d\n", nAprox);
  //printf("NDecolagens: %d\n", nDecol);
  printf("---------------------------------------------------------------------------------\n\n\n");
  printf("Listagem de eventos:\n\n\n");


  //~~~~~~~~~~~~~~~~/LÓGICA DO VOO/~~~~~~~~~~~~~~~~/

  int verifica_gas = 1;
  int pista_1 = 0, pista_2 = 0, pista_3 = 0;

  while(pouso->inicio != NULL || decolagem->inicio != NULL) {

    //Verificação de Emergência//
    int gas_zero = 0;

    gas_zero = verifica_comb0(pouso);

    if(gas_zero >= 3) {
      printf("\n\nALERTA GERAL DE DESVIO DE AERONAVE\n\n\n");

    }

    //Pista 1//
    if(pista_1 == 0) {
      if(pouso->inicio != NULL) {
        printf("Código do voo: %s\n", pouso->inicio->dados.codigo);
        printf("Status: [Aeronave Pousou]\n");
        printf("Horário do ínicio do procedimento: %d:%d\n", hour, min);
        printf("Número da pista: 1\n\n");
        pista_1 = 3;
        remove_Fila(pouso);
      }
      else if(decolagem->inicio != NULL){
        printf("Código do voo: %s\n", decolagem->inicio->dados.codigo);
        printf("Status: [Aeronave Decolou]\n");
        printf("Horário do ínicio do procedimento: %d:%d\n", hour, min);
        printf("Número da pista: 1\n\n");
        pista_1 = 2;
        remove_Fila(decolagem);
      }
    }


    //Pista 2//
    if(pista_2 == 0) {
      if(pouso->inicio != NULL) {
        printf("Código do voo: %s\n", pouso->inicio->dados.codigo);
        printf("Status: [Aeronave Pousou]\n");
        printf("Horário do ínicio do procedimento: %d:%d\n", hour, min);
        printf("Número da pista: 2\n\n");
        pista_2 = 3;
        remove_Fila(pouso);
      }
      else if(decolagem->inicio != NULL) {
        printf("Código do voo: %s\n", decolagem->inicio->dados.codigo);
        printf("Status: [Aeronave Decolou]\n");
        printf("Horário do ínicio do procedimento: %d:%d\n", hour, min);
        printf("Número da pista: 2\n\n");
        pista_2 = 2;
        remove_Fila(decolagem);
      }
    }


    //Pista 3//
    if(gas_zero >= 3) {
      if(pista_3 == 0) {
        printf("Código do voo: %s\n", pouso->inicio->dados.codigo);
        printf("Status: [Aeronave Pousou]\n");
        printf("Horário do ínicio do procedimento: %d:%d\n", hour, min);
        printf("Número da pista: 3\n\n");
        pista_3 = 3;
        remove_Fila(pouso);
      }
      Elem *avioes_que_caem = pouso->inicio;
      while(avioes_que_caem != NULL) {
        if(avioes_que_caem->dados.gasol == 0) {
          printf("ALERTA CRÍTICO: Aeronave irá cair\n");
          printf("Código do voo: %s\n", avioes_que_caem->dados.codigo);
          printf("Status: [Aeronave Caiu]\n\n");
          printf("teu cu\n");
          remove_Fila(pouso);
        }
        avioes_que_caem = avioes_que_caem->prox;
      }
    }

    if(pista_3 == 0) {
      if(decolagem->inicio != NULL) {
        printf("Código do voo: %s\n", decolagem->inicio->dados.codigo);
        printf("Status: [Aeronave Decolou]\n");
        printf("Horário do ínicio do procedimento: %d:%d\n", hour, min);
        printf("Número da pista: 3\n\n");
        pista_3 = 2;
        remove_Fila(decolagem);
      }
    }



    //Verificação de Rotina//
    if(pista_1 > 0){
      pista_1--;
    }

    if(pista_2 > 0){
      pista_2--;
    }

    if(pista_3 > 0){
      pista_3--;
    }

    min+= 5;
    calc_Hora(&hour, &min);

    if(verifica_gas%10 == 0) {
      reduz_comb(pouso);

    }

    verifica_gas++;

  }

  libera_Fila(pouso);
  libera_Fila(decolagem);

  /////////////////////////////Printagem/////////////////////////////////

  printf("----Final do programa-------------------------------------------------\n");
  return 0;
}
