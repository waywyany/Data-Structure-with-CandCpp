#pragma once
#include <iostream>
#include <string>
#include "RBTree.h"

//使用自定义的类或者结构体的时候必须重写比较相关运算符 等号 大小于号，== !=
using namespace std;
static const int TABLE_SIZE = 8;
namespace yellow {
namespace stl {

template<typename T>
class rbNode;

template<typename T>
class TreeNode;

template<typename T>
class HashNode {
public:
	T data;
public:
	HashNode(){}
	HashNode(const T& val): data(val){}
	~HashNode(){}
	virtual void insert(const T& val) = 0;
	virtual bool contains(const T& val) = 0;
	virtual HashNode<T>* getnext()=0;
	virtual void show() = 0;
	virtual void deledata(const T& val) = 0;
};

template<typename T>
struct tableNode {
public:
	HashNode<T>* node;
	int size;   //该位置的元素长度
};

template<typename T>
class ListNode : public HashNode<T> {
public:
	
	ListNode(const T& val):HashNode<T>(val), next(nullptr) {};
	~ListNode();
	void insert(const T& val);
	bool contains(const T& val); //思考，如果这个T的类型是个自定义类型呢
	ListNode<T>* getList();
	HashNode<T>* getnext() ;
	void show();
	void deledata(const T& val);
private:
	ListNode<T>* next;
};



template<typename T>
class Hashset {
public:
	Hashset();
	~Hashset();
	void insert(const T& val);
	int HashCode(const T& val);
	void enlarge();
	bool constain(T data);
	void showTable();
	void deledata(const T& val);
private:
	int cur_capacity;
	const double bound = 0.75;
	tableNode<T>* table;
	int cur_size;    //已经存放的坑的个数
	TreeNode<T>* list2tree(HashNode<T>* node);
	void moveNodes(rbNode<T>* node, rbNode<T>* NIL);
};

template<typename T>
Hashset<T>::Hashset() {
	this->table = new tableNode<T>[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++) {
		table[i].node= nullptr;
		table[i].size = 0;
	}
	this->cur_size = 0;   
	this->cur_capacity = TABLE_SIZE;
}

template<typename T>
Hashset<T>::~Hashset() {
	if (this->table) {
		for (int i = 0; i < this->cur_capacity; ++i) {
			if (table[i].node) delete table[i].node;
			this->table[i].size = 0;
		}
		delete[] this->table;
	}
	this->cur_size = 0;
	this->cur_capacity = 0;
}

template<typename T>
int Hashset<T>::HashCode(const T& val) {
	const char* data = reinterpret_cast<const char*>(&val);
	const size_t size = sizeof(val);

	size_t hash = 2166136261;  // 初始种子值
	size_t prime = 16777619;  // FNV算法中使用的质数

	for (size_t i = 0; i < size; ++i) {
		hash ^= data[i];
		hash *= prime;
	}

	return abs(static_cast<int>(hash)%this->cur_capacity);
}

template<typename T>
TreeNode<T>* Hashset<T>::list2tree(HashNode<T>* node)
{
	ListNode<T>* listnode = dynamic_cast<ListNode<T>*>(node);
	TreeNode<T>* root = new TreeNode<T>();
	while (listnode != nullptr) {
		root->insert(listnode->data);
		listnode = dynamic_cast<ListNode<T>*>(listnode->getnext());
	}
	delete listnode;
	return root;

}

template<typename T>
void Hashset<T>::insert(const T& val) {
	int hash = this->HashCode(val);
	if (this->table[hash].node==nullptr) {  //如果哈希表的该位置没有元素，就在这个坑首放元素
		table[hash].node = new ListNode<T>(val);
		this->cur_size++;
		cout <<"size:" << this->cur_size << endl;
		cout << "current rate: " << this->cur_size * 1.0 / this->cur_capacity << endl;
		if ((this->cur_size*1.0 / this->cur_capacity) > this->bound) {
			this->enlarge();
			//cout << "size: " << this->cur_size << " capacity: " << this->cur_capacity << endl;
		}
		++this->table[hash].size;
	}
	else {
		//hash = this->HashCode(val);
		table[hash].node->insert(val);  //插入元素（插入的容器可能是链表也可能是红黑树）
		++this->table[hash].size;
		ListNode<T>* pnode=dynamic_cast<ListNode<T>*>(table[hash].node);//强制下转型位ListNode
		if (pnode == nullptr) return;
		//这两句的作用是 判断当前这个位置是不是链表，不是的话就不需要额外操作了，return
		//如果是链表，那还需要判断当前链表长度是否过长要不要转化为查询效率更高的红黑树
		if (++this->table[hash].size >8) {   //这里要确保size之后就不会变了，也就是不会再有转化为红黑树的操作了
				TreeNode<T>* treenode = (this->list2tree(this->table[hash].node));  //将该位置的所有元素转化为红黑树
				delete dynamic_cast<ListNode<T>*>(this->table[hash].node);  //删掉原来的链表
				this->table[hash].node = treenode;
				/*cout << "这里发生了红黑树的转变：" << endl;
				this->table[hash].node->show();*/   //用来调试是否发生了红黑树的转换
				return;
		}
	}
}


template<typename T>
void Hashset<T>::deledata(const T& val) {
	if (this->constain(val) == 0)return;
	int hash = this->HashCode(val);
	this->table[hash].node->deledata(val);
}

template<typename T>
bool ListNode<T>::contains(const T& val)
{
	ListNode<T>* temp = this;
	while (temp) {
		if (temp->data == val)return true;
		temp = temp->next;
	}
	return false;
}

template<typename T>
void ListNode<T>::insert(const T& val) 
{
	if (this->contains(val)) return;
	ListNode<T>* node = new ListNode<T>(val);
	node->next = this->next;
	this->next = node;

}

template<typename T>
HashNode<T>* ListNode<T>::getnext() {
	return this->next;
}

template<typename T>
void Hashset<T>::enlarge() {
	this->cur_size = 0;
	int new_capacity = this->cur_capacity*2;  //容器容量翻倍
	int old_capacity = this->cur_capacity;
	tableNode<T>* temp = new tableNode<T>[new_capacity];
	for (int i = 0; i < new_capacity; i++)temp[i].node = nullptr;
	tableNode<T>* old_table = this->table;  //将原本元素暂存一下
	this->table = temp;
	this->cur_capacity = new_capacity;
	for (int i = 0; i < old_capacity; i++) {
		if (old_table[i].node != nullptr) { //如果该位置不为空，有元素的话
			/*ListNode<T>* node = static_cast<ListNode<T>*>(old_table[i].node);
			while (node!=nullptr) {
				this->insert(node->data);
				HashNode<T>* nextnode = node->getnext();  
				node = static_cast<ListNode<T>*>(nextnode);
				
			}*/
			HashNode<T>* node = old_table[i].node;
			// 该位置的元素是红黑树节点
			if (dynamic_cast<TreeNode<T>*>(node) != nullptr) {
				TreeNode<T>* tree = static_cast<TreeNode<T>*>(node);
				moveNodes(tree->getRoot(), tree->getNIL());
			}
			else { //该位置的元素是链表节点
				ListNode<T>* listNode = static_cast<ListNode<T>*>(node);
				while (listNode != nullptr) {
					this->insert(listNode->data);
					listNode = static_cast<ListNode<T>*>(listNode->getnext());
				}
			}
		}
	}
	
	//delete[] temp;
}

template<typename T>
void Hashset<T>::showTable() {  //如果是红黑树会从小到大按顺序排列，链表则是按插入元素排列
	for (int i = 0; i < this->cur_capacity; i++) {
		if (this->table[i].node == nullptr) {
			cout <<  "table [" << i << "] : no element"<<endl;
		}
		else {
			cout << "table [" << i << "] : ";
			this->table[i].node->show();
		}
	}
}

template<typename T>
void ListNode<T>::show() {
	ListNode<T>* node = this;
	while (node != nullptr) {
		cout << node->data << " ";
		node = node->next;
	}
	printf("\n");
}

template<typename T>
bool Hashset<T>::constain(T data) {
	int hash = this->HashCode(data);
	if (this->table[hash].node != nullptr) {
		return this->table[hash].node->contains(data);
	}
	return false;
}

template<typename T>
ListNode<T>::~ListNode() {  //析构函数存在问题，我用循环遍历删除链表就报错
	delete next;
	
}

template<typename T>
void ListNode<T>::deledata(const T& val) {
	ListNode<T>* temp = this;
	while (temp->next != nullptr) {
		if (temp->next->data == val) {
			ListNode<T>* node = temp->next;
			temp->next = node->next;
			delete node;
			return;
		}
		temp = temp->next;
	}
}


template<typename T>
void Hashset<T>::moveNodes(rbNode<T>* node, rbNode<T>* NIL) {
	if (node != NIL) {
		moveNodes(node->left, NIL);
		this->insert(node->data);
		moveNodes(node->right, NIL);
		delete node;
	}
}


}
}


