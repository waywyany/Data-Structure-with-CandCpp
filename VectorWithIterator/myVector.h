#pragma once
#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;
namespace yellow {
namespace stl {
template<typename T>
class Vector {
public:
	Vector();
	~Vector();

	void push_back(const T& value);
	void pop_back();
	void showdata();
	int size() const ;
	int capacity() const;
	void reserve(int size);
	void resize(int size);
	T& at(int index);
	T& operator [](int index);  //[]的重载使得类能够通过去索引获得数据
	bool empty();
	void clear();
	T& front();
	T& back();
	T* data();
	Vector<T>& operator = (const Vector<T>& other);
	class Iterator {  //迭代器，本质上是一个指向vector的data的指针
	public:
		Iterator() : m_pointer(nullptr) {}
		Iterator(T* pointer) : m_pointer(pointer) {}
		~Iterator(){}

		bool operator==(const Iterator& other) {
			return m_pointer == other.m_pointer;
		}
		bool operator!=(const Iterator& other) {
			return m_pointer != other.m_pointer;
		}
		Iterator operator= (const Iterator& other)
		{
			m_pointer = other.m_pointer;
			return *this;
		}
		Iterator & operator ++(){
			m_pointer += 1;
			return *this;
		}
		Iterator operator ++(int){
			Iterator it = *this;
			++(*this);
			return it;
		}
		Iterator operator +(int i) {
			Iterator it = *this;
			it.m_pointer += i;
			return it;
		}
		Iterator & operator +=(int i) {
			m_pointer += i;
			return *this;
		}
		Iterator operator -(int i) {
			Iterator it = *this;
			it.m_pointer -= i;
			return it;
		}
		Iterator& operator -=(int i) {
			m_pointer -= i;
			return *this;
		}
		int operator -(const Iterator& other)const  {
			return m_pointer - other.m_pointer;
		}
		T& operator *() {
			return *m_pointer;
		}
		T* operator ->() {
			return m_pointer;
		}


	private:
		T* m_pointer;
	};

	Iterator begin();
	Iterator end();

	Iterator find(const T& value);
	Iterator insert(const Iterator it, const T& value);
	Iterator insert(const Iterator it, int n, const T& value);

	Iterator erase(const Iterator it);
	Iterator erase(const Iterator first, const Iterator last);
	bool is_basic_type();

private:
	T* m_data;
	int m_size;
	int m_capacity;
};

template<typename T>
Vector<T>::Vector(){
	this->m_data = nullptr;
	this->m_capacity = 0;
	this->m_size = 0;
}

template<typename T>
Vector<T>::~Vector() {
	if (this->m_data) {
		delete[] m_data;
		m_data = nullptr;
	}
	m_capacity = 0;
	m_size = 0;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	if (m_size < m_capacity) {
		m_data[m_size] = value;
		m_size++;
		return;
	}
	if (m_capacity == 0) this->m_capacity = 1;
	else m_capacity *= 2;//容量空间翻倍
	T* data = new T[m_capacity];
	for (int i = 0; i < m_size; i++) {
		data[i] = m_data[i];
	}
	if (m_data != nullptr) {
		delete[] m_data;
		m_data = nullptr;
	}
	m_data = data;
	m_data[m_size] = value;
	m_size++;
	return;
}
template<typename T>
void Vector<T>::showdata() {
	for (int i = 0; i < m_size; i++) {
		cout << m_data[i] << " " << endl;
	}
}

template<typename T>
void Vector<T>::pop_back() {
	if (m_size > 0)m_size--;
}
template<typename T>
int Vector<T>::size() const {
	return m_size;
}

template<typename T>
int Vector<T>::capacity() const {
	return m_capacity;
}

template<typename T>
void Vector<T>::reserve(int size) {
	if (m_capacity > size)return;
	while (m_capacity < size) {
		if (m_capacity == 0)m_capacity = 1;
		else m_capacity *= 2;
	}
	T* data = new T[m_capacity];
	for (int i = 0; i < m_size; i++) {
		data[i] = m_data[i];
	}
	if (m_data != nullptr) {
		delete[] m_data;
		m_data = nullptr;
	}
	m_data = data;
}

template<typename T>
void Vector<T>::resize(int size) {
	if (m_size >= size) {
		m_size = size;
		return;
	}
	if (size <= m_capacity) {
		for (int i = m_size; i < size; i++) m_data[i] = T();
		m_size = size;
		return;
	}
	else {
		while (m_capacity <= size) {
			if (m_capacity == 0)m_capacity = 1;
			else m_capacity *= 2;
		}
		T* data = new T[m_capacity];
		for (int i = 0; i < m_size; i++) {
			data[i] = m_data[i];
		}
		for (int i = m_size; i < size; i++) {
			data[i] = T();
		}
		m_size = size;
		if (m_data != nullptr) {
			delete[] m_data;
			m_data = nullptr;
		}
		m_data = data;
	}

}

template<typename T>
T& Vector<T>::at(int index) {
	if (index < 0 || index >= m_size) {
		throw std::logic_error("out of range");
	}
	else return m_data[index];
}

template<typename T>
T& Vector<T>::operator[](int index) {
	if (index < 0 || index >= m_size) {
		throw std::logic_error("out of range");
	}
	else return m_data[index];
}

template<typename T>
bool Vector<T>::empty() {
	return m_size == 0;
}

template<typename T>
void Vector<T>::clear() {
	m_size = 0;
}

template<typename T>
T& Vector<T>::front() {
	if (m_size <= 0)throw std::logic_error("no element");
	return m_data[0];
}

template<typename T>
T& Vector<T>::back() {
	if (m_size <= 0)throw std::logic_error("no element");
	return m_data[m_size - 1];
}

template<typename T>
T* Vector<T>::data() {
	return this->m_data;
}

template<typename T>
Vector<T>& Vector<T>::operator =(const Vector<T>& other) {
	if (m_capacity < other.m_size) {
		if (m_data != nullptr) {
			delete[] m_data;
			m_data = nullptr;
			m_size = 0;
			m_capacity = 0;
		}
		while (m_capacity < other.m_size) {
			if (m_capacity == 0)m_capacity = 1;
			else m_capacity *= 2;
		}
		m_data = new T[m_capacity]; 
	}
	for (int i = 0; i < other.m_size; i++) {
		m_data[i] = other.m_data[i];
	}
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	return *this;
}

template<typename T>
typename Vector<T>::Iterator Vector<T>:: begin() {
	Vector<T>::Iterator it(m_data);
	return it;
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::end() {
	Vector<T>::Iterator it(m_data+this->m_size);
	return it;
}

template<typename T>
bool Vector<T>::is_basic_type() {
	if (is_pointer<T>::value) return true;
	return(typeid(T) == typeid(bool)) ||
		(typeid(T) == typeid(char)) ||
		(typeid(T) == typeid(unsigned char)) ||
		(typeid(T) == typeid(short)) ||
		(typeid(T) == typeid(unsigned short)) ||
		(typeid(T) == typeid(int)) ||
		(typeid(T) == typeid(unsigned int)) ||
		(typeid(T) == typeid(long)) ||
		(typeid(T) == typeid(unsigned long)) ||
		(typeid(T) == typeid(float)) ||
		(typeid(T) == typeid(double));
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::find(const T& value) {
	for (Vector<T>::Iterator it = begin(); it != end(); it++) {
		if (*it == value) return it;
	}
	return end();
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::insert(const Vector<T>::Iterator it, const T& value) {
	return insert(it, 1, value);
}
template<typename T>
typename Vector<T>::Iterator Vector<T>::insert(const Vector<T>::Iterator it, int n,const T& value) {
	int size = it - begin();
	if(m_size+n<=m_capacity){
		if (this->is_basic_type()) {
			memmove(m_data + size + n, m_data + size, (m_size - size) * sizeof(T));
		}
		else {
			for (int i = m_size; i > size; i--) {
				m_data[i + n - 1] = m_data[i - 1];
			}
		}		
		for (int i = 0; i < n; i++) {
			m_data[size + i] = value;
		}
		m_size += n;
		return Vector<T>::Iterator(m_data + size);
	}
	while (m_size + n > m_capacity) {
		if (m_capacity == 0) m_capacity = 1;
		else m_capacity *= 2;
	}
	T* data = new T[m_capacity];
	if (this->is_basic_type()) {
		memcpy(data, m_data, size * sizeof(T));
	}
	else{
		for (int i = 0; i < size; i++) {
			data[i] = m_data[i];
		}
	}
	for (int i = 0; i < n; i++) {
		data[size + i] = value;
	}
	if (this->is_basic_type()) {
		memcpy(data+size+n,m_data+size,(m_size-size)*sizeof(T));
	}
	else {
		for (int i = size; i < m_size; i++) {
			data[i] = m_data[i];
		}
	}
	if (m_data != nullptr) {
		delete[] m_data;
		m_data = nullptr;
	}
	m_data = data;
	m_size += n;
	return Vector<T>::Iterator(m_data + size);

}


template<typename T>
typename Vector<T>::Iterator Vector<T>::erase(const Vector<T>::Iterator it) {
	if (end() - it == 1) {
		m_size -= 1;
		return end();
	}
	int size = it - begin();
	if (this->is_basic_type()) {
		memmove(m_data + size, m_data + 1, (m_size - size - 1) * sizeof(T));
	}
	else {
		for (int i = size; i < m_size; i++) {
			m_data[i] = m_data[i + 1];
		}
	}
	
	m_size -= 1;
	return it;
}

template<typename T>
typename Vector<T>::Iterator Vector<T>::erase(const Vector<T>::Iterator first, const Vector<T>::Iterator last) {
	int f = first - begin();
	int l = end() - last;
	int n = last - first;
	if (this->is_basic_type()) {
		memmove(m_data + f, m_data + l, (m_size - l) * sizeof(T));
	}
	else {
		for (int i = 0; i < m_size; i++) {
			m_data[f+i] = m_data[l+i];
		}
	}
	
	m_size -= n;
	return first;
}

}
}