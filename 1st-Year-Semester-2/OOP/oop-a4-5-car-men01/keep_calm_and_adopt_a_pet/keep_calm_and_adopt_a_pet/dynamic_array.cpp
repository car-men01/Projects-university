//#include "dynamic_array.h"
//
///// <summary>
///// Resizes the dynamic array
///// </summary>
//void DynamicArray::resize()
//{
//	this->capacity = this->capacity * 2;
//	TElem* array = new TElem[this->capacity];
//	for (int i = 0; i < this->size; i++) {
//		array[i] = this->elements[i];
//	}
//	delete[] this->elements;
//	this->elements = array;
//}
//
///// <summary>
///// The default constructor of the dynamic array
///// </summary>
///// <param name="capacity"> The capacity of the dynamic array </param>
//DynamicArray::DynamicArray(int capacity)
//{
//	this->capacity = capacity;
//	this->size = 0;
//	this->elements = new TElem[capacity];
//}
//
///// <summary>
///// The copy constructor of the dynamic array
///// </summary>
///// <param name="arr"> The dynamic array </param>
//DynamicArray::DynamicArray(const DynamicArray& arr)
//{
//	this->capacity = arr.capacity;
//	this->size = arr.size;
//	this->elements = new TElem[this->capacity];
//	for (int i = 0; i < arr.size; i++)
//		this->elements[i] = arr.elements[i];
//}
//
///// <summary>
///// The assignment operator of the dynamic array
///// </summary>
///// <param name="arr"> The dynamic array </param>
///// <returns> A copy of the array </returns>
//DynamicArray& DynamicArray::operator=(const DynamicArray& arr)
//{
//	delete[] elements;
//	this->capacity = arr.capacity;
//	this->size = arr.size;
//	this->elements = new TElem[this->capacity];
//	for (int i = 0; i < arr.size; i++)
//		this->elements[i] = arr.elements[i];
//	return *this;
//}
//
///// <summary>
///// The destructor of the dynamic array
///// </summary>
//DynamicArray::~DynamicArray()
//{
//	delete[] this->elements;
//}
//
///// <summary>
///// Adds an element to the dynamic array
///// </summary>
///// <param name="element"> The element to be added </param>
//void DynamicArray::add(TElem element)
//{
//	if (this->size == this->capacity) {
//		this->resize();
//	}
//	this->elements[this->size] = element;
//	this->size++;
//}
//
///// <summary>
///// Removes an element from the dynamic array at the given index
///// </summary>
///// <param name="index"> The index from where to remove the element </param>
//void DynamicArray::remove(int index)
//{
//	for (int i = index; i < this->size - 1; i++) {
//		this->elements[i] = this->elements[i + 1];
//	}
//	this->size--;
//}
//
///// <summary>
///// Updates an element from the dynamic array at the given index
///// </summary>
///// <param name="element"> The element to update with </param>
///// <param name="index"> The index of the element to be updated </param>
//void DynamicArray::update(TElem element, int index)
//{
//	this->elements[index] = element;
//}
//
///// <summary>
///// Gets the size of the dynamic array
///// </summary>
///// <returns> The size of the dynamic array </returns>
//int DynamicArray::get_size()
//{
//	return this->size;
//}
//
///// <summary>
///// Gets the capacity of the dynamic array
///// </summary>
///// <returns> The capacity of the dynamic array </returns>
//int DynamicArray::get_capacity()
//{
//	return this->capacity;
//}
//
///// <summary>
///// Gets the element from the dynamic array at the given index
///// </summary>
///// <param name="index"> The index of the element </param>
///// <returns> The element from the given index </returns>
//TElem DynamicArray::get_elem(int index)
//{
//	return this->elements[index];
//}
//
///// <summary>
///// Gets the elements of the dynamic array
///// </summary>
///// <returns> A dynamic array with the elements </returns>
//TElem* DynamicArray::get_elements()
//{
//	return this->elements;
//}
