#include "avl.h" //importa o arquivo de declaracoes
#include <stdio.h>
#include <stdlib.h>

//testar
tree rsd(tree node) {
	tree p, u, t1, t2, t3;
	p = node;
	u = node->left;

	t1 = p->left;
	t2 = u->right;
	t3 = u->left;

	p->left = t2;
	u->right = p;

	if (u->fb == -1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		p->fb = -1;
		u->fb = 1;
	}

	return u;
}
//ok
tree rse(tree node) {

	tree p, u, t1, t2, t3;
	p = node;
	u = node->right;

	t1 = p->left;
	t2 = u->left;
	t3 = u->right;

	p->right = t2;
	u->left = p;

	if (u->fb == 1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		// duvidas - caso +2 0 entendi!!
		p->fb = 1;
		u->fb = -1;
	}

	return u;
}

tree rdd(tree node) {
	tree p, u, v, t1, t2, t3, t4;

	p = node;
	u = node->left;
	v = u->right;

	t1 = u->left;
	t2 = v->left;
	t3 = v->right;
	t4 = p->right;

	v->right = p;
	u->right = t2;
	v->left = u;
	p->left = t3;

	switch (v->fb) {
    case -1:
			p->fb = 1;
			u->fb = 1;
			v->fb = 0;
      break;
    case 0:
      p->fb = 0;
      u->fb = 0;
      break;
    case 1:
			p->fb = 0;
			v->fb = 0;
			u->fb = -1;
      break;
  }

	return v;
}

tree rde(tree node) {
	tree p, u, v, t1, t2, t3, t4;

	p = node;
	u = node->right;
	v = u->left;

	//t1 = p->left;
	t2 = v->left;
	t3 = v->right;
	//t4 = u->right;

	v->left = p;
	p->right = t2; 
	v->right = u;
	u->left = t3;
	
	switch (v->fb) {
    case -1:
			v->fb = 0;
			p->fb = 0;
			u->fb = 1;
      break;
    case 0:
      p->fb = 0;
      u->fb = 0;
      break;
    case 1:
			v->fb = 0;
			p->fb = -1;
			u->fb = 0;
      break;
	}
	return v;
}

tree rotatation(tree node) {
	if (node->fb > 0) {
		switch (node->right->fb) {
      case 0: 
				return rse(node);
        break;
      case 1:
				//printf("node atual [ val =%d, fb =%d] | rotation rse,node right [ val =%d, fb =%d]\n",node->val, node->fb, node->right->val, node->right->fb);
        return rse(node);
        break;
      case -1:
				//printf("node atual [ val =%d, fb =%d] | rotation rde,node right [ val =%d, fb =%d]\n",node->val, node->fb, node->right->val, node->right->fb);
        return rde(node);
        break;
      }
	} else {
		switch (node->left->fb) {
      case 0:
				return rsd(node);
        break;
      case 1:
				//printf("node atual [ val =%d, fb =%d] | rotation rdd,node left [ val =%d, fb =%d]\n",node->val, node->fb, node->left->val, node->left->fb);
        return rdd(node);
        break;
      case -1:
				//printf("node atual [ val =%d, fb =%d] | rotation rsd,node left [ val =%d, fb =%d]\n",node->val, node->fb, node->left->val, node->left->fb);
        return rsd(node);
        break;
      }
	}
	return node;
}

tree insert_avl(tree node, int val, int *grown) {
	if (node == NULL) {
		tree new_node = (tree) malloc(sizeof(struct no));
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->fb = 0;
		new_node->val = val;
		*grown = 1;
		return new_node;
	} else {
		if (node->val <= val) {
			node->right = insert_avl(node->right, val, grown);

			if (*grown) {
				switch (node->fb) {
				case 0:
					node->fb = 1;
					*grown = 1;
					break;
				case 1:
					*grown = 0;
					return rotatation(node);
					break;
				case -1:
					node->fb = 0;
					*grown = 0;
					break;
				}
			}
			// simétrico
		} else {
			node->left = insert_avl(node->left, val, grown);

			if (*grown) {
				switch (node->fb) {
				case 0:
					node->fb = -1;
					*grown = -1;
					break;
				case 1:
					node->fb = 0;
					*grown = 0;
					break;
				case -1:
					*grown = 0;
					return rotatation(node);
					break;
				}
			}
		}

		return node;
	}
}

int max_value(tree node) {
	if (node == NULL) {
		return -1;
	}
	if (node->right == NULL) {
		return node->val;
	} else {
		return max_value(node->right);
	}
}

tree remove_avl(tree node, int val, int *reduce) {

	if (node == NULL) {
		return NULL;
	}
	if (node->val == val) { // 90 == 90
		//printf("\nencontrou %d\n",node->val);
		if (node->left != NULL && node->right != NULL) {
			switch_nodes(node, val);
			node->left = remove_avl(node->left, val, reduce);
		}
		if (node->left == NULL) {
			*reduce = 1;
			tree aux = node->right;
      free(node);
			return aux;
		}
		if (node->right == NULL) {
      tree aux = node->left;
			free(node);
			return aux;
		}
		
		node->val = max_value(node->left);
		node->left = remove_avl(node->left, node->val, reduce);
		return node;
	}
	if (node->val <= val) { // 80 <= 90 - sim
		node->right = remove_avl(node->right, val, reduce);
		//printf("right %d valor, fb= %d\n",node->val, node->fb);
		if (*reduce) { // sim
			switch (node->fb) {
				case 1:
					node->fb = 0;
					*reduce = 1;
					break;
				case 0:
					node->fb = -1;
					*reduce = 0; //deu erros
					break;
				case -1: // 80 = -1
					return rotatation(node);
					break;
				}
		}
	} else { // node left 100
		node->left = remove_avl(node->left, val, reduce);
		//printf("left %d valor, fb= %d\n",node->val, node->fb);
		if (*reduce) {
			switch (node->fb) {
				case 1:
					return rotatation(node);
					break;
				case 0:
					node->fb = 1;
					*reduce = 0;
					break;
				case -1:
					node->fb = 0;
					*reduce = 1;
					break;
			}
		}
	}
	return node;
}

void switch_nodes(tree node, int val) {
	tree aux = node->left;
	while (aux->right != NULL) {
		aux = aux->right;
	}
	node->val = aux->val;
	aux->val = val;
}

void pre_order_avl(tree node) {
	if (node != NULL) {
		printf("[%d, %d]", node->val, node->fb);
		pre_order_avl(node->left);
		pre_order_avl(node->right);
	}
}

void in_order_avl(tree node) {
	if (node != NULL) {
		in_order_avl(node->left);
		printf("[%d]", node->val);
		in_order_avl(node->right);
	}
}

void pos_order_avl(tree node) {
	if (node != NULL) {
		pos_order_avl(node->left);
		pos_order_avl(node->right);
		printf("[%d]", node->val);
	}
}

void reverse_avl(tree node) {
	if (node != NULL) {
		reverse_avl(node->right);
		printf("[%d]", node->val);
		reverse_avl(node->left);
	}
}

int isPrime(int num) {
	for (int i = 2; i < num; i++) {
		if (num % i == 0)
			return 1; // nao e primo.
	}
	return 0; // e primo
}

int sum_prime_numbers_avl(tree no) {
	int aux, i;
	if (no != NULL) {
		aux = sum_prime_numbers_avl(no->left)
				+ sum_prime_numbers_avl(no->right);
		if (isPrime(no->val) == 0) {
			return aux + 1;
		} else {
			return aux;
		}
	}
}

int successor_avl(tree node, int suc, int val) {
	if (node != NULL) {
		if (node->val > val && node->left == NULL) {
			return node->val;
		}
		if (node->val <= val) {
			successor_avl(node->right, suc, val);
		} else {
			suc = node->val;
			successor_avl(node->left, suc, val);
		}
	} else {
		return suc;
	}
}

void path_avl(tree node, int val) {
	if (node != NULL && node->val != val) {
		printf("[%d]", node->val);
		if (node->val <= val) {
			path_avl(node->right, val);
		} else {
			path_avl(node->left, val);
		}
	}
}

int sum_all_numbers_avl(tree node) {
	int aux;
	if (node != NULL) {
		aux = sum_all_numbers_avl(node->left)
				+ sum_all_numbers_avl(node->right);
		return aux + node->val;
	}
}

int exist_avl(tree node, int val) {
	if (node != NULL) {
		if (node->val == val) {
			return 1;
		}
		if (node->val <= val) {
			exist_avl(node->right, val);
		} else {
			exist_avl(node->left, val);
		}
	} else {
		return 0;
	}
}

int transform_percentage(int num, float porcentagem) {
	return num + (num * (porcentagem / 100));
}

int adjust_percentage_avl(tree node, float porcentagem) {
	if (node != NULL) {
		adjust_percentage_avl(node->left, porcentagem);
		adjust_percentage_avl(node->right, porcentagem);
		node->val = transform_percentage(node->val, porcentagem);
	}
}

int height_avl(tree node) {
	int left_height, right_height;
	if (node != NULL) {
		left_height = height_avl(node->left);
		right_height = height_avl(node->right);

		if (right_height >= left_height) {
			return right_height + 1;
		} else {
			return left_height + 1;
		}
	} else {
		return 0;
	}
}

void succession_avl(tree node, int n) {
	if (node != NULL) {
		if (node->val == n) {
			in_order_avl(node);
		}
		if (node->val <= n) {
			succession_avl(node->right, n);
		} else {
			succession_avl(node->left, n);
		}
	}
}