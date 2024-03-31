#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define element int
typedef enum {
	RED,
	BLACK
}colortype;
 
typedef struct rbt {
	element val;
	rbt* left;
	rbt* right;
	rbt* parent;
	colortype color;
}rbt;

typedef struct rbt_root {
	rbt* root;
	rbt* nil;
}rbt_root;

rbt_root* rbt_init(void) {
	rbt_root* root = (rbt_root*)malloc(sizeof(rbt_root));
	root->nil = (rbt*)malloc(sizeof(rbt));
	root->nil->color = BLACK;
	root->nil->left = root->nil->right = NULL;
	root->nil->parent = NULL;
	root->root = root->nil;

	return root;
}

void leftRotate(rbt_root* root, rbt* x) {
	rbt* y = x->right;
	x->right = y->left;
	if (x->right != root->nil) {
		x->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == root->nil) {
		root->root = y;
	}
	else if (y->val < y->parent->val) {
		y->parent->left = y;
	}
	else {
		y->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void rightRotate(rbt_root* root, rbt* x) {
	rbt* y = x->left;
	x->left = y->right;
	if (x->left != root->nil) {
		x->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == root->nil) {
		root->root = y;
	}
	else if (y->val < y->parent->val) {
		y->parent->left = y;
	}
	else {
		y->parent->right = y;
	}
	y->right = x;
	x->parent = y;
}

void fixup(rbt_root* T, rbt* z) {
	while (z->parent->color == RED) {
		if (z->parent->parent->left == z->parent) {
			rbt* u = z->parent->parent->right;
			if (u->color == RED) {
				z->parent->color = BLACK;
				u->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else {
				if (z->parent->right == z) {//进行左旋使得z->parent->left==z
					z = z->parent;
					leftRotate(T, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rightRotate(T, z->parent->parent);

			}
		}
		else {
			rbt* u = z->parent->parent->left;
			if (u->color == RED) {
				z->parent->color = BLACK;
				u->color = BLACK;
				z->parent->parent->color == RED;
				z = z->parent->parent;
			}
			else {  //uncle's color is black
				if (z->parent->left == z) {
					z = z->parent;
					rightRotate(T, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				leftRotate(T, z->parent->parent);
			}
		}
			
	}
	T->root->color = BLACK;
}

void insert(rbt_root* T, rbt* z) {
	rbt* pre = T->nil;
	rbt* cur = T->root;
	while (cur != T->nil) {
		pre = cur;
		if (z->val < cur->val) {
			cur = cur->left;
		}
		else if (z->val > cur->val) {
			cur = cur->right;
		}
		else return;
	}
	z->parent = pre;
	if (pre == T->nil) {
		T->root = z;
	}
	else {
		if (pre->val > z->val) {
			pre->left = z;
		}
		else pre->right = z;
	}
	z->left = T->nil;
	z->right = T->nil;
	z->color = RED;
	fixup(T, z);
}

rbt* initnode() {
	rbt* node= (rbt*)malloc(sizeof(rbt));
	return node;
}

rbt* minitree(rbt_root* T, rbt* node) {   //找到结点的子树的最左边的也就是值最小的关联结点
	while (node->left!=T->nil) {
		node = node->left;
	}
	return node;
}

rbt* maxtree(rbt_root* T, rbt* node) {		//找到结点的子树的最右边的也就是值最大的关联结点
	while (node->right != T->nil) {
		node = node->right;
	}
	return node;
}

rbt* successor(rbt_root* T, rbt* node) {
	rbt* y = node->parent;
	if (node->right!=T->nil) {
		return minitree(T, node->right);
	}
	while ((y != T->nil) && (node == y->right)) {
		node = y;
		y = y->parent;
	}
	return y;
}

void dele_fixup(rbt_root* T, rbt* x) {
	while ((x != T->root) && (x->color == BLACK)) {  //如果x不是根节点而且是黑色的话
		if (x == x->parent->left) {  //如果x是父亲结点的左孩子，x的父亲是不知道什么颜色的，只知道原来删除的结点是黑色的
			rbt* w = x->parent->right;  //这里x的兄弟也就是父亲的右节点一定是存在的，如果不存在那么黑高就不相等了
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				leftRotate(T,x->parent);
				w = w->parent->right;
			}
			if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
				w->color = RED;
				x = x->parent;
			}

			//---------------------------------侄子的颜色不全为黑 而且一定是一红一黑-------------------------------------
			else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(T, w);
					w = x->parent->right;
				}
				//如果是左侄子为红 要变成右侄子为红的情况来处理
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				leftRotate(T, x->parent);
				x = T->root;
				//这里的意思是进了这里面结束后就不用继续while了结束了
			}
		}
		else {          //x == x->parent->right
			rbt* w = x->parent->left;  //顶替节点的兄弟
			if (w->color == RED) {  //x是父亲结点的右子树
				w->color = BLACK;
				x->parent->color = RED;
				rightRotate(T, x->parent);
				w = x->parent->left;
			}
			if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					leftRotate(T, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rightRotate(T, x->parent);
				x = T->root; //结束循环  也就是结束了；
			}
		}
	}
	x->color = BLACK;
}

rbt* rbt_delete(rbt_root* T, rbt* z) {
	rbt* y = T->nil;
	rbt* x = T->nil;
	if ((z->left == T->nil) || (z->right == T->nil)) {   //判断删除结点是不是双子结点 
		y = z;    //要么覆盖（有孩子），要么直接删掉（没孩子） 这里直接整合为一种了   现在y存的是要删除的值
	}
	else {
		y = successor(T, z);   //如果是双子结点，那么就要找要删除结点的右子树中值最小的结点
	}

	if (y->left != T->nil) x = y->left;
	else if (y->right != T->nil) x = y->right;
	x->parent = y->parent;
	if (y->parent == T->nil) T->root = x;
	else if (y == y->parent->left) y->parent->left = x;
	else y->parent->right = x;
	if (y != z) {
		z->val = y->val;
	}
	if (y->color == BLACK) {
		dele_fixup(T, x);
	}

	return y;
}

rbt* search(rbt_root* T, int target) {
	rbt* node = T->root;
	while (node != T->nil) {
		if (target < node->val) {
			node = node->left;
		}
		else if (target > node->val) {
			node = node->right;
		}
		else {
			return node;
		}
	}
	return T->nil;
}

void display(rbt_root* T, rbt* z) {
	if (z != T->nil) {
		display(T, z->left);
		printf("%d ", z->val);
		display(T, z->right);
	}
}

int main(void) {
	rbt_root* T = (rbt_root*)malloc(sizeof(rbt_root));
	T->nil = (rbt*)malloc(sizeof(rbt));
	T->nil->color = BLACK;
	T->root = T->nil;
	rbt* node = T->nil;
	node = initnode();
	node->val = 21;
	insert(T, node);
	node = initnode();
	node->val = 12;
	insert(T, node);
	node = initnode();
	node->val =34;
	insert(T, node);
	node = initnode();
	node->val = 2;
	insert(T, node);
	node = initnode();
	node->val = 99;
	insert(T, node);
	node = initnode();
	node->val = 45;
	insert(T, node);
	node = initnode();
	node->val = 120;
	insert(T, node);
	node = initnode();
	node->val = 210;
	insert(T, node);
	node = initnode();
	node->val = 97;
	insert(T, node);
	display(T, T->root);
	rbt*node1=rbt_delete(T, search(T, 99));
	printf("\n %d\n", node1->val);
	display(T, T->root);
	
	return 0;
}






