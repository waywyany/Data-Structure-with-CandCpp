#pragma once
#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;
namespace yellow {
namespace stl {

template<typename T>
struct linklist {
	T data;
	struct linklist* next;
};
template<typename T>
class ListStack {
public:
	ListStack();
	~ListStack();
	void push_back(T data);
	void pop();
	T top();
	bool empty();
	void show();
private:
	linklist<T>* _top;
};

template<typename T>
ListStack<T>::ListStack() {
	this->_top = nullptr;
}

template<typename T>
ListStack<T>::~ListStack() {
	linklist<T>* temp = this->_top;
	while (this->_top) {
		_top = _top->next;
		delete temp;
		temp = this->_top;
	}
	this->_top = nullptr;
}

template<typename T>
void ListStack<T>::push_back(T data) {
	linklist<T>* node = new linklist<T>;
	node->data = data;
	node->next = this->_top;
	_top = node;
}

template<typename T>
bool ListStack<T>::empty() {
	return _top == nullptr;
}

template<typename T>
void ListStack<T>::pop() {
	if (this->empty())return;
	if (this->_top->next)_top = nullptr;
	else {
		linklist<T>* node = _top;
		_top = _top->next;
		delete node;
	}
}

template<typename T>
T ListStack<T>::top() {
	return _top->data;
}

template<typename T>
void ListStack<T>::show() {
	if (empty())return;
	linklist<T>* node = _top;
	while (node) {
		cout << node->data << endl;
		node = node->next;
	}
}

}
}