#include <stdio.h>
#include "binary_tree.h"

int main(){
  Tree * arvore;
  arvore = loadTreeFromFile("BSTs/bst1.txt");

  // int tamanho = getHeight(arvore);
  // printf("altura = %d\n", tamanho);
  // isFull(arvore);
  // searchValue(arvore,26);
  // showTree(arvore);
  printInOrder(arvore);
  printf("\n");
  printPreOrder(arvore);
  printf("\n");
  printPosOrder(arvore);
  printf("\n");
  return 0;
}