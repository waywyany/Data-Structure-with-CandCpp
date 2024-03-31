#pragma once
#include <iostream>
#include <string>
#include "RBTree.h"

//ʹ���Զ��������߽ṹ���ʱ�������д�Ƚ��������� �Ⱥ� ��С�ںţ�== !=
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
	int size;   //��λ�õ�Ԫ�س���
};

template<typename T>
class ListNode : public HashNode<T> {
public:
	
	ListNode(const T& val):HashNode<T>(val), next(nullptr) {};
	~ListNode();
	void insert(const T& val);
	bool contains(const T& val); //˼����������T�������Ǹ��Զ���������
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
	int cur_size;    //�Ѿ���ŵĿӵĸ���
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

	size_t hash = 2166136261;  // ��ʼ����ֵ
	size_t prime = 16777619;  // FNV�㷨��ʹ�õ�����

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
	if (this->table[hash].node==nullptr) {  //�����ϣ��ĸ�λ��û��Ԫ�أ�����������׷�Ԫ��
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
		table[hash].node->insert(val);  //����Ԫ�أ��������������������Ҳ�����Ǻ������
		++this->table[hash].size;
		ListNode<T>* pnode=dynamic_cast<ListNode<T>*>(table[hash].node);//ǿ����ת��λListNode
		if (pnode == nullptr) return;
		//������������� �жϵ�ǰ���λ���ǲ����������ǵĻ��Ͳ���Ҫ��������ˣ�return
		//����������ǻ���Ҫ�жϵ�ǰ�������Ƿ����Ҫ��Ҫת��Ϊ��ѯЧ�ʸ��ߵĺ����
		if (++this->table[hash].size >8) {   //����Ҫȷ��size֮��Ͳ�����ˣ�Ҳ���ǲ�������ת��Ϊ������Ĳ�����
				TreeNode<T>* treenode = (this->list2tree(this->table[hash].node));  //����λ�õ�����Ԫ��ת��Ϊ�����
				delete dynamic_cast<ListNode<T>*>(this->table[hash].node);  //ɾ��ԭ��������
				this->table[hash].node = treenode;
				/*cout << "���﷢���˺������ת�䣺" << endl;
				this->table[hash].node->show();*/   //���������Ƿ����˺������ת��
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
	int new_capacity = this->cur_capacity*2;  //������������
	int old_capacity = this->cur_capacity;
	tableNode<T>* temp = new tableNode<T>[new_capacity];
	for (int i = 0; i < new_capacity; i++)temp[i].node = nullptr;
	tableNode<T>* old_table = this->table;  //��ԭ��Ԫ���ݴ�һ��
	this->table = temp;
	this->cur_capacity = new_capacity;
	for (int i = 0; i < old_capacity; i++) {
		if (old_table[i].node != nullptr) { //�����λ�ò�Ϊ�գ���Ԫ�صĻ�
			/*ListNode<T>* node = static_cast<ListNode<T>*>(old_table[i].node);
			while (node!=nullptr) {
				this->insert(node->data);
				HashNode<T>* nextnode = node->getnext();  
				node = static_cast<ListNode<T>*>(nextnode);
				
			}*/
			HashNode<T>* node = old_table[i].node;
			// ��λ�õ�Ԫ���Ǻ�����ڵ�
			if (dynamic_cast<TreeNode<T>*>(node) != nullptr) {
				TreeNode<T>* tree = static_cast<TreeNode<T>*>(node);
				moveNodes(tree->getRoot(), tree->getNIL());
			}
			else { //��λ�õ�Ԫ��������ڵ�
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
void Hashset<T>::showTable() {  //����Ǻ�������С����˳�����У��������ǰ�����Ԫ������
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
ListNode<T>::~ListNode() {  //���������������⣬����ѭ������ɾ������ͱ���
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


