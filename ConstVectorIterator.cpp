#include "MyVector.h"

template<class T>
MyVector<T>::ConstVectorIterator::ConstVectorIterator(T* ptr) {
	_ptr = ptr;
}

template<class T>
MyVector<T>::ConstVectorIterator::ConstVectorIterator(const MyVector<T>::ConstVectorIterator& copy) {
	_ptr = copy._ptr;
}

template<class T>
class MyVector<T>::ConstVectorIterator MyVector<T>::ConstVectorIterator::operator=(const MyVector<T>::ConstVectorIterator& copy) {
	if (this != &copy) {
		_ptr = copy._ptr;
	}
	return *this;
};

template<class T>
const T& MyVector<T>::ConstVectorIterator::operator*() const{
	return *_ptr;
}

template<class T>
const T* MyVector<T>::ConstVectorIterator::operator->() const{
	return _ptr;
}

template<class T>
class MyVector<T>::ConstVectorIterator& MyVector<T>::ConstVectorIterator::operator++() {
	++_ptr;
	return *this;
}

template<class T>
class MyVector<T>::ConstVectorIterator& MyVector<T>::ConstVectorIterator::operator--() {
	--_ptr;
	return *this;
}

template<class T>
class MyVector<T>::ConstVectorIterator MyVector<T>::ConstVectorIterator::operator++(int) {
	ConstVectorIterator tmp = *this;
	++(*this);
	return tmp;
}

template<class T>
class MyVector<T>::ConstVectorIterator MyVector<T>::ConstVectorIterator::operator--(int) {
	ConstVectorIterator tmp = *this;
	--(*this);
	return tmp;
}

template<class T>
bool MyVector<T>::ConstVectorIterator::operator!=(const MyVector::ConstVectorIterator& other) const{
	return _ptr != other._ptr;
}

template<class T>
bool MyVector<T>::ConstVectorIterator::operator==(const MyVector::ConstVectorIterator& other) const{
	return _ptr == other._ptr;
}

template<class T>
std::ptrdiff_t MyVector<T>::ConstVectorIterator::operator-(const MyVector::ConstVectorIterator& other) {
	return _ptr - other._ptr;
}
