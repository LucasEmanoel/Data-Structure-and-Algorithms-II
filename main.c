#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  tree bst_tree;
  int option, aux;

  bst_tree = NULL;

  while (1) {
    scanf("%d", &option);
    switch (option)
    {
    case 1:
      scanf("%d", &aux);
      bst_tree = add(bst_tree ,aux);
      break;
    case 2:
      pre_order(bst_tree);
      printf("\n");
      break;
    case 3:
      in_order(bst_tree);
      printf("\n");
      break;
    case 4:
      pos_order(bst_tree);
      printf("\n");
      break;
    case 0:
      exit(0);
    }
  }
}