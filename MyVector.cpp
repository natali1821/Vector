#include "MyVector.h"

template<class T>
MyVector<T>::MyVector(size_t size, ResizeStrategy strategy, float coef) {
	_size = size;
	_resizeStrategy = strategy;
	_coef = coef;
	if (!_size) {
		_capacity = 1;
		_data = new T[_capacity];
		return;
	}
	switch(_resizeStrategy) {
	case(ResizeStrategy::Additive):
		_capacity = ceil(_size + _coef);
		break;
	case(ResizeStrategy::Multiplicative):
		_capacity = ceil(_size * _coef);
		break;
	}
	_data = new T[_capacity];
	for(size_t i = 0; i < _size; ++i) {
		_data[i] = T();
	}
}

template<class T>
MyVector<T>::MyVector(size_t size, const T& value, ResizeStrategy strategy, float coef) {
	_size = size;
	_resizeStrategy = strategy;
	_coef = coef;
	if (!_size) {
		_capacity = 1;
		_data = new T[_capacity];
		return;
	}
	switch(_resizeStrategy) {
	case(ResizeStrategy::Additive):
		_capacity = ceil(_size + _coef);
		break;
	case(ResizeStrategy::Multiplicative):
		_capacity = ceil(_size * _coef);
		break;
	}
	_data = new T[_capacity];
	for (size_t i = 0; i < _size; ++i) {
		_data[i] = value;
	}
}

template<class T>
MyVector<T>::MyVector(const MyVector<T>& copy) {
	_size = copy.size();
	_capacity = copy.capacity();
	_resizeStrategy = copy._resizeStrategy;
	_coef = copy._coef;
	_data = nullptr;
	if (size()) {
		_data = new T[capacity()];
		for (size_t i = 0; i < size(); ++i) {
			_data[i] = copy.at(i);
		}
	}
}

template<class T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept {
	_data = std::exchange(other._data, nullptr);
	_size = std::exchange(other._size, 0);
	_capacity = std::exchange(other._capacity, 0);
	_coef = std::exchange(other._coef, 0);
	_resizeStrategy = other._resizeStrategy;
}

template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& copy){
	if (this != &copy) {
		_size = copy.size();
		_capacity = copy.capacity();
		_coef = copy._coef;
		_resizeStrategy = copy._resizeStrategy;
		delete[] _data;
		_data = new T[capacity()];
		for (size_t i = 0; i < size(); ++i) {
			_data[i] = copy.at(i);
		}
	}
	return *this;
}

template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) noexcept {
	if (this != &other) {
		delete[] _data;
		_data = std::exchange(other._data, nullptr);
		_size = std::exchange(other._size, 0);
		_capacity = std::exchange(other._capacity, 0);
		_coef = std::exchange(other._coef, 0);
		_resizeStrategy = other._resizeStrategy;
	}
	return *this;
}

template<class T>
MyVector<T>::~MyVector() {
	if (_data) {
		delete[] _data;
		_data = nullptr;
	}
	_size = 0;
	_capacity = 0;
	_coef = 0;
}

template<class T>
size_t MyVector<T>::capacity() const {
	return _capacity;
}

template<class T>
size_t MyVector<T>::size() const {
	return _size;
}

template<class T>
float MyVector<T>::loadFactor() const {
	return (float)_size / _capacity;
}

template<class T>
class MyVector<T>::VectorIterator MyVector<T>::begin() {
	return MyVector<T>::VectorIterator(&_data[0]);
}

template<class T>
class MyVector<T>::ConstVectorIterator MyVector<T>::cbegin() const {
	return MyVector<T>::ConstVectorIterator(&_data[0]);
}

template<class T>
class MyVector<T>::VectorIterator MyVector<T>::end(){
	return MyVector<T>::VectorIterator(&_data[size()]);
}

template<class T>
class MyVector<T>::ConstVectorIterator MyVector<T>::cend() const{
	return MyVector<T>::ConstVectorIterator(&_data[size()]);
}

template<class T>
T& MyVector<T>::at(const size_t idx) {
	if (idx >= size()) {
		throw std::out_of_range("Called at(idx) : idx >= size of vector ");
	}
	return _data[idx];
}

template<class T>
const T& MyVector<T>::at(const size_t idx) const {
	if (idx >= size()) {
		throw std::out_of_range("Called at(idx) : idx >= size of vector ");
	}
	return _data[idx];
}

template<class T>
T& MyVector<T>::operator[](const size_t idx) {
	return at(idx);
}

template<class T>
const T& MyVector<T>::operator[](const size_t idx) const {
	return at(idx);
}

template<class T>
void MyVector<T>::reserve(const size_t capacity) {
	if (capacity > _capacity) {
		T* tmp = new T[capacity];
		for (size_t i = 0; i < size(); ++i) {
			tmp[i] = _data[i];
		}
		delete[] _data;
		_data = tmp;
		_capacity = capacity;
	}
}

template<class T>
void MyVector<T>::pushBack(const T& value) {
	//insert(size(), value)
	if (isLoaded()) {
		reallocVector(size());
	}
	_data[size()] = value;
	++_size;
}

template<class T>
void MyVector<T>::pushFront(const T& value) {
	insert(0, value);
}

template<class T>
void MyVector<T>::insert(const size_t idx, const T& value) {
	if (idx > size()) {
		throw std::out_of_range("Called insert(idx) : idx > size");
	}
	if (isLoaded()) {
		reallocVector(size());
	}
	T* tmp = new T[capacity()];
	for (size_t i = 0; i < idx; ++i) {
		tmp[i] = _data[i];
	}
	tmp[idx] = value;
	for (size_t i = idx; i < size(); ++i) {
		tmp[i + 1] = _data[i];
	}
	delete[] _data;
	_data = tmp;
	++_size;
}

template<class T>
void MyVector<T>::insert(const size_t idx, const MyVector<T>& value) {
	if (idx > size()) {
		throw std::out_of_range("Called insert(idx) : idx > size");
	}
	size_t newSize = size() + value.size();
	if (newSize > capacity()) {
		reallocVector(newSize);
	}
	size_t i = 0, j = 0;
	T* tmp = new T[capacity()];
	for (i; i < idx; ++i) {
		tmp[i] = _data[i];
	}
	for (i, j; j < value.size(); ++i, ++j) {
		tmp[i] = value.at(j);
	}
	for (i, j = idx; j < size(); ++i, ++j) {
		tmp[i] = _data[j];
	}
	delete[] _data;
	_data = tmp;
	_size = newSize;
}

template<class T>
void MyVector<T>::insert(MyVector<T>::ConstVectorIterator it, const T& value) {
	size_t idx = 0;
	for (MyVector<T>::ConstVectorIterator tmp = cbegin(); tmp != cend(); ++tmp) {
		++idx;
		if (tmp == it) {
			break;
		}
	}
	insert(idx, value);
}

template<class T>
void MyVector<T>::insert(MyVector<T>::ConstVectorIterator it, const MyVector<T>& value) {
	size_t idx = 0;
	for (MyVector<T>::ConstVectorIterator tmp = cbegin(); tmp != cend(); ++tmp) {
		++idx;
		if (tmp == it) {
			break;
		}
	}
	insert(idx, value);
}

template<class T>
void MyVector<T>::popBack() {
	//erase(size(), value);
	--_size;
}

template<class T>
void MyVector<T>::popFront() {
	erase(0, 1);
}

template<class T>
void MyVector<T>::erase(const size_t pos) {
	erase(pos, 1);
}

template<class T>
void MyVector<T>::erase(const size_t pos, size_t len) {
	if (pos >= size()) {
		throw std::out_of_range("Called erase(pos) : pos >= size");
	}
	if (!size()) {
		return;
	}
	if (len > size() - pos) {
		len = size() - pos;
	}
	size_t sizeTmp = size() - len;
	T* tmp = new T[capacity()];
	for (size_t i = 0; i < pos; ++i) {
		tmp[i] = _data[i];
	}
	for (size_t i = pos; i < sizeTmp; ++i) {
		tmp[i] = _data[i + len];
	}
	delete[] _data;
	_data = tmp;
	_size = sizeTmp;
}

template<class T>
class MyVector<T>::ConstVectorIterator MyVector<T>::find(const T& value, bool isBegin) {
	MyVector<T>::ConstVectorIterator it = cbegin();
	for (MyVector<T>::ConstVectorIterator tmp = cbegin(); tmp != cend(); ++tmp) {
		if (*tmp == value) {
			it = tmp;
			if (isBegin) {
				break;
			}
		}
	}
	if (*it != value) {
		return cend();
	}
	return it;
}

template<class T>
void MyVector<T>::resize(const size_t newSize, const T& value) {
	if (newSize < 0) {
		throw std::invalid_argument("Invalid size");
	}
	if (newSize > size() && newSize <= capacity()) {
		for (size_t i = size(); i < newSize; ++i) {
			_data[i] = value;
		}
	}
	else if (newSize > capacity()) {
		size_t oldSize = size();
		reallocVector(newSize);
		for (size_t i = oldSize; i < size(); i++) {
			_data[i] = value;
		}
	}
	_size = newSize;
}

template<class T>
void MyVector<T>::clear() {
	_size = 0;
}

template<class T>
void MyVector<T>::reallocVector(const size_t newSize) {
	switch(_resizeStrategy) {
	case(ResizeStrategy::Additive):
		_capacity = ceil(newSize + _coef);
		break;
	case(ResizeStrategy::Multiplicative):
		_capacity = ceil(newSize * _coef);
	break;
	}
	T* tmp = new T[capacity()];
	for (size_t i = 0; i < size(); ++i) {
		tmp[i] = _data[i];
	}
	delete[] _data;
	_data = tmp;
	_size = newSize;
}

template<class T>
bool MyVector<T>::isLoaded() const{
	return (loadFactor() == 1);
}
