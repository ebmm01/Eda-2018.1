#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "filas.h"



int main() {
  Fila *fi;
  fi = cria_Fila();
  struct aviao teste;
  teste.codigo = "TEste";
  teste.status = "Decolou";
  teste.gasol = "A03";
  teste.horario = 12;
  teste.npista = 1;

  insere_Fila(fi, teste);
  imprime_Fila(fi);

  libera_Fila(fi);
  int n=0;
  srand(time(NULL));
  while(n!= 20){
    printf("Aleatório: %d\n", aleatorio(20,60) );
    n++;
  }
  return 0;
}
