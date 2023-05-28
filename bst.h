#ifndef BST_H
#define BST_H

typedef struct no{
  int val;
  struct no *left, *right;
} no;
typedef no *tree;

tree add_bst(tree node, int val);
void pre_order_bst(tree node);
void in_order_bst(tree node);
void pos_order_bst(tree node);
int ehPrimo(int num);
int qtd_primos_bst(tree node);
void reserve_bst(tree node);
int sucessor_bst(tree node, int val);
void caminho_bst(tree node, int val);
int somatorio_bst(tree node);
int existe_bst(tree node, int val);
int ajustar_porcentagem(int num, float porcentagem);
int reajuste_bst(tree node, float porcentagem);
tree remover_bst(tree node, int val);

#endif
