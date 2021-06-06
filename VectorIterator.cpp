#include "MyVector.h"

template<class T>
MyVector<T>::VectorIterator::VectorIterator(T* ptr) {
	_ptr = ptr;
}

template<class T>
MyVector<T>::VectorIterator::VectorIterator(const MyVector::VectorIterator& copy) {
	_ptr = copy._ptr;
}

template<class T>
class MyVector<T>::VectorIterator MyVector<T>::VectorIterator::operator=(const MyVector<T>::VectorIterator& copy) {
	if (this != &copy) {
		_ptr = copy._ptr;
	}
	return *this;
}

template<class T>
T& MyVector<T>::VectorIterator::operator*() {
	return *_ptr;
}

template<class T>
T* MyVector<T>::VectorIterator::operator->() {
	return _ptr;
}

template<class T>
class MyVector<T>::VectorIterator& MyVector<T>::VectorIterator::operator++() {
	++_ptr;
	return *this;
}

template<class T>
class MyVector<T>::VectorIterator& MyVector<T>::VectorIterator::operator--() {
	--_ptr;
	return *this;
}

template<class T>
class MyVector<T>::VectorIterator MyVector<T>::VectorIterator::operator++(int) {
	VectorIterator tmp = *this;
	++(*this);
	return tmp;
}

template<class T>
class MyVector<T>::VectorIterator MyVector<T>::VectorIterator::operator--(int) {
	VectorIterator tmp = *this;
	--(*this);
	return tmp;
}

template<class T>
bool MyVector<T>::VectorIterator::operator!=(const MyVector::VectorIterator& other) {
	return _ptr != other._ptr;
}

template<class T>
bool MyVector<T>::VectorIterator::operator==(const MyVector::VectorIterator& other) {
	return _ptr == other._ptr;
}

template<class T>
std::ptrdiff_t MyVector<T>::VectorIterator::operator-(const MyVector::VectorIterator& other) {
	return _ptr - other._ptr;
}
