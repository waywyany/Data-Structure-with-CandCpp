#pragma once

#include <iostream>
#include <stdexcept>
using namespace std;
namespace yellow {
namespace stl {
template<typename T>
class Stack {
public:
	Stack();
	~Stack();
	void push_back(const T& val);
	void show();
	bool empty();
	T gettop();
	void pop();
private:
	T* data;
	int top;
	int size; //标明数组的容量，当top==size时意味着要进行扩容了
};


template<typename T>
Stack<T>::Stack() {
	this->data = nullptr;
	this->top = -1;
	this->size = 0;
}
template<typename T>
Stack<T>::~Stack() {
	if (this->data != nullptr) {
		delete[] data;
		data = nullptr;
	}
	this->size = 0;
	this->top = 0;
}

template<typename T>
void Stack<T>::push_back(const T& val) {
	if (this->size == 0) {
		size = 2;
		this->data = new T[size];
		this->data[++top] = val;
		return;
	}
	if ((this->top + 1) == size) {
		// is full   need to big big
		this->size *= 2;
		T* temp = new T[size];
		for (int i = 0; i <= top; i++) {
			temp[i] = this->data[i];
		}
		temp[++top] = val;
		if (this->data != nullptr) {
			delete[] this->data;
			data = nullptr;
		}
		data = temp;
	}
	else {
		top++;
		this->data[top] = val;
	}
}

template<typename T>
void Stack<T>::show() {
	cout << "size: " << this->size << " top: " << this->top << endl;
	for (int i = 0; i <= top; i++) {
		
		cout << data[i] << endl;
	}
}

template<typename T>
bool Stack<T>::empty() {
	return top == -1;
}

template<typename T>
T Stack<T>::gettop() {
	return this->data[top];
}

template<typename T>
void Stack<T>::pop() {
	if (!this->empty()) {
		top--;
	}

}



}
}