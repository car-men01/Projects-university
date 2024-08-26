#pragma once

template <typename T>
class DynamicVector
{
private:
	T* elems;
	int size;
	int capacity;

public:
	// default constructor for a DynamicVector
	DynamicVector(int capacity = 10);

	// copy constructor for a DynamicVector
	DynamicVector(const DynamicVector& v);
	~DynamicVector();

	// assignment operator for a DynamicVector
	DynamicVector& operator=(const DynamicVector& v);

	/*
		Overloading the subscript operator
		Input: pos - a valid position within the vector.
		Output: a reference to the element o position pos.
	*/
	T& operator[](int pos);

	// Adds an element to the current DynamicVector.
	void add(T e);
	void remove(int pos);
	void update(T e, int pos);

	DynamicVector<T> get_elems();

	int get_size() const;

private:
	// Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
	void resize(int factor = 2);

};

template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elems = new T[capacity];
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T>& v)
{
	this->size = v.size;
	this->capacity = v.capacity;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elems;
}

template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& v)
{
	if (this == &v)
		return *this;

	this->size = v.size;
	this->capacity = v.capacity;

	delete[] this->elems;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];

	return *this;
}

template <typename T>
T& DynamicVector<T>::operator[](int pos)
{
	return this->elems[pos];
}

template <typename T>
void DynamicVector<T>::add(T e)
{
	if (this->size == this->capacity)
		this->resize();
	this->elems[this->size] = e;
	this->size++;
}

template <typename T>
void DynamicVector<T>::remove(int pos)
{
	for (int i = pos; i < this->size - 1; i++)
		this->elems[i] = this->elems[i + 1];
	this->size--;
}

template <typename T>
void DynamicVector<T>::update(T e, int pos)
{
	this->elems[pos] = e;
}


template <typename T>
void DynamicVector<T>::resize(int factor)
{
	this->capacity *= factor;

	T* els = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		els[i] = this->elems[i];

	delete[] this->elems;
	this->elems = els;
}

template <typename T>
int DynamicVector<T>::get_size() const
{
	return this->size;
}

template <typename T>
DynamicVector<T> DynamicVector<T>::get_elems()
{
	return this->elems;
}



//#include "dog.h"
//
//typedef Dog TElem;
//
//class DynamicArray
//{
//private:
//	int size;
//	int capacity;
//	TElem* elements;
//
//	void resize();
//
//public:
//	DynamicArray(int capacity = 10);
//	DynamicArray(const DynamicArray& arr);
//
//	DynamicArray& operator=(const DynamicArray& arr);
//
//	~DynamicArray();
//
//	void add(TElem element);
//	void remove(int index);
//	void update(TElem element, int index);
//
//	int get_size();
//	int get_capacity();
//	TElem get_elem(int index);
//	TElem* get_elements();
//};
