#include <stdlib.h>
#include <stdio.h>
#include "abin.h"

int  main(int argc, char const *argv[]) {
  ArvBin* raiz = cria_ArvBin();
  raiz = loadTreeFromFile("bst1");
  printf("Testando a raiz:\n");
  emOrdem_ArvBin(raiz);
  printElements(raiz);
  libera_ArvBin(raiz);
  return 0;
}
