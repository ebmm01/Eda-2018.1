#include <stdlib.h>
#include "abin.h"

int  main(int argc, char const *argv[]) {
  ArvBin* raiz = cria_ArvBin();
  loadTreeFromFile("bst1");
  libera_ArvBin(raiz);
  return 0;
}
