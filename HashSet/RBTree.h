
#pragma once


#include <iostream>
#include <string.h>
#include "HashClass.h"
using namespace std;
namespace yellow {
namespace stl {
enum RBTColor {
	RED,
	BLACK
};

template<typename T>
class HashNode;

template<typename T>
class rbNode {
public:
	T data;
	RBTColor color;
	rbNode<T>* parent;
	rbNode<T>* left;
	rbNode<T>* right;
	rbNode():color(BLACK), parent(nullptr), left(nullptr), right(nullptr) {}
	rbNode(T val) :data(val), color(BLACK), parent(nullptr), left(nullptr), right(nullptr) {}
};

template<typename T>
class TreeNode :public HashNode<T> {
private:
	rbNode<T>* root;
	rbNode<T>* NIL; //表示空的节点；
	void insert(rbNode<T>* z);
	void leftshow(rbNode<T>* node);
	rbNode<T>* minitree(rbNode<T>* node);
	rbNode<T>* maxtree(rbNode<T>* node);
	rbNode<T>* successor(rbNode<T>* node);
	void dele_fixup(rbNode<T>* x);
	rbNode<T>* rbNode_delete(rbNode<T>* z);
public:

	TreeNode() {
		this->NIL = new rbNode<T>();
		this->root = this->NIL;
	}
	~TreeNode();
	rbNode<T>* getRoot() { return this->root; }
	rbNode<T>* getNIL() { return this->NIL; }
	void leftRotate(rbNode<T>* x);
	void rightRotate(rbNode<T>* x);
	void fixup(rbNode<T>* z);
	void insert(const T& val) {
		rbNode<T>* node = new rbNode<T>(val);
		this->insert(node);
	};
	rbNode<T>* deleData(T data);
	bool contains(const T& val);
	HashNode<T>* getnext() { return NULL; }
	
	void leftshow() { leftshow(this->root); };
	rbNode<T>* search(T target);
	void show();
	void deledata(const T& data);
};

template<typename T>
void TreeNode<T>::leftRotate(rbNode<T>* x) {
	rbNode<T>* y = x->right;
	x->right = y->left;
	if (x->right != this->NIL) {
		x->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == this->NIL) {
		this->root = y;
	}
	else if (y->data < y->parent->data) {
		y->parent->left = y;
	}
	else {
		y->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

template<typename T>
void TreeNode<T>::rightRotate(rbNode<T>* x) {
	rbNode<T>* y = x->left;
	x->left = y->right;
	if (x->left != this->NIL) {
		x->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == this->NIL) {
		this->root = y;
	}
	else if (y->data < y->parent->data) {
		y->parent->left = y;
	}
	else {
		y->parent->right = y;
	}
	y->right = x;
	x->parent = y;
}

template<typename T>
void TreeNode<T>::fixup(rbNode<T>* z) {
	while (z->parent->color == RED) {
		if (z->parent->parent->left == z->parent) {
			rbNode<T>* u = z->parent->parent->right;
			if (u->color == RED) {
				z->parent->color = BLACK;
				u->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else {
				if (z->parent->right == z) {//进行左旋使得z->parent->left==z
					z = z->parent;
					this->leftRotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				this->rightRotate(z->parent->parent);
			}
		}
		else {
			rbNode<T>* u = z->parent->parent->left;
			if (u->color == RED) {
				z->parent->color = BLACK;
				u->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else {
				if (z->parent->left == z) {
					z = z->parent;
					this->rightRotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				this->leftRotate(z->parent->parent);
			}
		}
	}
	this->root->color = BLACK;
}

template<typename T>
void TreeNode<T>::insert(rbNode<T>* z) {
	rbNode<T>* pre = this->NIL;
	rbNode<T>* cur = this->root;
	while (cur != this->NIL) {
		pre = cur;
		if (z->data < cur->data) {
			cur = cur->left;
		}
		else if (z->data > cur->data) {
			cur = cur->right;
		}
		else return;   //已存在同样的元素
	}
	z->parent = pre;
	if (pre == this->NIL) {
		this->root = z;
	}
	else {
		if (pre->data > z->data) {
			pre->left = z;
		}
		else pre->right = z;
	}
	z->left = z->right = this->NIL;
	z->color = RED;
	this->fixup(z);
}

template<typename T>
rbNode<T>* TreeNode<T>::minitree(rbNode<T>* node) {
	while (node->left != this->NIL){node = node->left;}
	return node;
}

template<typename T>
rbNode<T>* TreeNode<T>::maxtree(rbNode<T>* node) {
	while (node->right != this->NIL) node = node->right;
	return node;
}

template<typename T>
rbNode<T>* TreeNode<T>::successor(rbNode<T>* node) {
	rbNode<T>* y = node->parent;
	if (node->right != this->NIL) return this->minitree(node->right);
	while ((y != this->NIL) && (node == y->right)) {
		node = y;
		y = y->parent;
	}
	return y;
}

template<typename T>
void TreeNode<T>::dele_fixup(rbNode<T>* x) {
	while ((x != this->root) && (x->color == BLACK)) {
		if (x == x->parent->left) {
			rbNode<T>* w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				this->leftRotate(x->parent);
				w = w->parent->right;
			}
			if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
				w->color = RED;
				x = x->parent;
			}

			else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					this->rightRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				this->leftRotate(x->parent);
				x = this->root;
			}
		}
		else {
			rbNode<T>* w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				this->rightRotate(x->parent);
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
					this->leftRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				this->rightRotate(x->parent);
				x = this->root;
			}
		}
	}
	x->color = BLACK;
}

template<typename T>
rbNode<T>* TreeNode<T>::rbNode_delete(rbNode<T>* z) {
	rbNode<T>* y = this->NIL;
	rbNode<T>* x = this->NIL;
	if ((z->left == this->NIL) || (z->right == this->NIL)) {
		y = z;
	}
	else {
		y = this->successor(z);
	}
	if (y->left != this->NIL) x = y->left;
	else if (y->right != this->NIL) x = y->right;
	x->parent = y->parent;
	if (y->parent == this->NIL) this->root = x;
	else if (y == y->parent->left) y->parent->left = x;
	else y->parent->right = x;
	if (y != z) z->data = y->data;
	if (y->color == BLACK) this->dele_fixup(x);

	return y;
}

template<typename T>
rbNode<T>* TreeNode<T>::search(T target) {
	rbNode<T>* node = this->root;
	while (node != this->NIL) {
		if (target < node->data) node = node->left;
		else if (target > node->data) node = node->right;
		else return node;
	}
	return this->NIL;
}

template<typename T>
bool TreeNode<T>::contains(const T& val) {
	rbNode<T>* node = this->search(val);
	if (node == this->NIL) return false;
	else return true;
}

template<typename T>
rbNode<T>* TreeNode<T>::deleData(T data) {
	return this->rbNode_delete(this->search(data));
}

template<typename T>
void TreeNode<T>::show() {
	this->leftshow(this->root);
	printf("\n");
}

template<typename T>
void TreeNode<T>::leftshow(rbNode<T>* node) {
	if (node != this->NIL) {
		leftshow(node->left);
		cout << node->data << "  ";
		leftshow(node->right);
	}
}

template<typename T>
void TreeNode<T>::deledata(const T& val) {
	this->deleData(val);
}


template<typename T>
TreeNode<T>::~TreeNode() {
	auto deleteNode = [](rbNode<T>* node, rbNode<T>* NIL) {
		if (node != NIL) {
			deleteNode(node->left, NIL);
			deleteNode(node->right, NIL);
			delete node;
		}
		};
	deleteNode(this->root, this->NIL);
	delete this->NIL;
}
}
}

