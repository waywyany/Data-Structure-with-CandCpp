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
				if (z->parent->right == z) {//��������ʹ��z->parent->left==z
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

rbt* minitree(rbt_root* T, rbt* node) {   //�ҵ���������������ߵ�Ҳ����ֵ��С�Ĺ������
	while (node->left!=T->nil) {
		node = node->left;
	}
	return node;
}

rbt* maxtree(rbt_root* T, rbt* node) {		//�ҵ��������������ұߵ�Ҳ����ֵ���Ĺ������
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
	while ((x != T->root) && (x->color == BLACK)) {  //���x���Ǹ��ڵ�����Ǻ�ɫ�Ļ�
		if (x == x->parent->left) {  //���x�Ǹ��׽������ӣ�x�ĸ����ǲ�֪��ʲô��ɫ�ģ�ֻ֪��ԭ��ɾ���Ľ���Ǻ�ɫ��
			rbt* w = x->parent->right;  //����x���ֵ�Ҳ���Ǹ��׵��ҽڵ�һ���Ǵ��ڵģ������������ô�ڸ߾Ͳ������
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

			//---------------------------------ֶ�ӵ���ɫ��ȫΪ�� ����һ����һ��һ��-------------------------------------
			else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(T, w);
					w = x->parent->right;
				}
				//�������ֶ��Ϊ�� Ҫ�����ֶ��Ϊ������������
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				leftRotate(T, x->parent);
				x = T->root;
				//�������˼�ǽ��������������Ͳ��ü���while�˽�����
			}
		}
		else {          //x == x->parent->right
			rbt* w = x->parent->left;  //����ڵ���ֵ�
			if (w->color == RED) {  //x�Ǹ��׽���������
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
				x = T->root; //����ѭ��  Ҳ���ǽ����ˣ�
			}
		}
	}
	x->color = BLACK;
}

rbt* rbt_delete(rbt_root* T, rbt* z) {
	rbt* y = T->nil;
	rbt* x = T->nil;
	if ((z->left == T->nil) || (z->right == T->nil)) {   //�ж�ɾ������ǲ���˫�ӽ�� 
		y = z;    //Ҫô���ǣ��к��ӣ���Ҫôֱ��ɾ����û���ӣ� ����ֱ������Ϊһ����   ����y�����Ҫɾ����ֵ
	}
	else {
		y = successor(T, z);   //�����˫�ӽ�㣬��ô��Ҫ��Ҫɾ��������������ֵ��С�Ľ��
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






