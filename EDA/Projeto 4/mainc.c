#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filas.h"

int main() {
  Fila *fi;
  fi = cria_Fila();
  /*
  int x = tamanho_Fila(fi);
  int y = Fila_vazia(fi);
  int z = insere_Fila(fi, dados_aluno);
  int w = remove_Fila(fi);
  int x = consulta_Fila(fi, &dados_aluno);
  */
  libera_Fila(fi);

  return 0;
}
