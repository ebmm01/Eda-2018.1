#include <stdlib.h>
#include <stdio.h>
#include "abin.h"
#include "printTree.h"


void menu();

int  main(int argc, char const *argv[]) {
  //ArvAVL* teste = NULL;
  ArvBin* raiz = cria_ArvBin();
  int escolha = 0;
  char nome[100];
  int x = 0;

  while(escolha != 11){
    //system("clear");
     fflush ( stdin );
    menu();
    scanf("%d", &escolha);
    switch (escolha) {
      case 1:
        printf("Insira o nome do arquivo:\n\n");
        scanf("%s", nome);
        raiz = loadTreeFromFile(nome);
        printf("Arquivo aberto");
        fflush(stdin);
        break;

      case 2:
        printf("Printando raiz\n\n");
        showTree(raiz);
        break;

      case 3:
        if(isFull(raiz)) printf("Árove cheia!!\n");
        else printf("Árvore não cheia.\n" );
        break;

      case 4:{
        int valor;
        printf("Insira o valor a ser pesquisado na Árvore\n\n");
        scanf("%d",&valor);
        consulta_ArvBin(raiz,valor);
        break;
      }
      case 5:

        x = altura_ArvBin(raiz);
        if (x >=0) printf("\n\n A altura da árvore é: %d\n\n",x);
        else printf("\n\nRaiz nula.\n\n");
        break;

      case 6:{
        int valor = 0;
        printf("Insira o valor a ser removido");
        scanf("%d", &valor);
        remove_ArvBin(raiz,valor);
        break;
      }
      case 7:
        emOrdem_ArvBin(raiz);
        break;

      case 8:
        preOrdem_ArvBin(raiz);
        break;

      case 9:
        posOrdem_ArvBin(raiz);
        break;

      case 10:
        printf("NÂO IMPLEMENTADO");
        break;

      case 11:
        printf("SAINDO");
        libera_ArvBin(raiz);
        break;

      default:
       menu();
       printf("Opção inválida; Tente novamente.\n");

    }
  }


  return 0;
}

void menu(){
  printf("\nOpções disponíveis:\n");
  printf("[1] loadTreeFromFile:\n");
  printf("[2] showTree:\n");
  printf("[3] isFull:\n");
  printf("[4] searchValue:\n");
  printf("[5] getHeight:\n");
  printf("[6] removeValue:\n");
  printf("[7] printInOrder:\n");
  printf("[8] printPreOrder:\n");
  printf("[9] printPostOrder:\n");
  printf("[10] balanceTree:\n");
  printf("[11] Sair do programa:\n");

}
