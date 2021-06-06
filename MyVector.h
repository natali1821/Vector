#pragma once
#include <iostream>
#include <exception>
#include <math.h>
#include <utility>

// стратегия изменения capacity
enum class ResizeStrategy {
	Additive,
	Multiplicative
};

template<class T>
class MyVector
{
public:
	// реализовать итераторы
	class VectorIterator{
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type 	= std::ptrdiff_t;
		using value_type        = T;
		using pointer           = T*;
		using reference         = T&;

		VectorIterator(T* ptr);
		VectorIterator(const VectorIterator& copy);
		VectorIterator operator=(const VectorIterator& copy);

		reference operator*();
		pointer operator->();

		VectorIterator& operator++();
		VectorIterator& operator--();
		VectorIterator operator++(int);
		VectorIterator operator--(int);

		bool operator!=(const VectorIterator& other);
		bool operator==(const VectorIterator& other);

		difference_type operator-(const VectorIterator& other);
	private:
		T* _ptr;
	};

	class ConstVectorIterator{
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type   = std::ptrdiff_t;
		using value_type        = const T;
		using pointer            = const T*;
		using reference          = const T&;

		ConstVectorIterator(T* ptr);
		ConstVectorIterator(const ConstVectorIterator& copy);
		ConstVectorIterator operator=(const ConstVectorIterator& copy);

		reference operator*() const;
		pointer operator->() const;

		ConstVectorIterator& operator++();
		ConstVectorIterator& operator--();
		ConstVectorIterator operator++(int);
		ConstVectorIterator operator--(int);

		bool operator!=(const ConstVectorIterator& other) const;
		bool operator==(const ConstVectorIterator& other) const;

		difference_type operator-(const ConstVectorIterator& other);
	private:
		T* _ptr;
	};

	// заполнить вектор значениями T()
	MyVector(size_t size = 0,
			 ResizeStrategy = ResizeStrategy::Multiplicative,
			 float coef = 1.5f);
	// заполнить вектор значениями value
	MyVector(size_t size,
			 const T& value,
			 ResizeStrategy = ResizeStrategy::Multiplicative,
			 float coef = 1.5f);

	MyVector(const MyVector<T>& copy);
	MyVector& operator=(const MyVector<T>& copy);

	MyVector(MyVector<T>&& other) noexcept;
	MyVector& operator=(MyVector<T>&& other) noexcept;
	~MyVector();

	size_t capacity() const;
	size_t size() const;
	float loadFactor() const;

	VectorIterator begin();
	ConstVectorIterator cbegin() const;
	VectorIterator end();
	ConstVectorIterator cend() const;

	// доступ к элементу,
	// должен работать за O(1)
	T& at(const size_t idx);
	const T& at(const size_t idx) const;
	T& operator[](const size_t idx);
	const T& operator[](const size_t idx) const;

	// добавить в конец,
	// должен работать за amort(O(1))
	void pushBack(const T& value);
	// вставить,
	// должен работать за O(n)
	void pushFront(const T& value);
	void insert(const size_t idx, const T& value);     // версия для одного значения
	void insert(const size_t idx, const MyVector<T>& value);      // версия для вектора
	void insert(ConstVectorIterator it, const T& value);  // версия для одного значения
	void insert(ConstVectorIterator it, const MyVector<T>& value);   // версия для вектора

	// удалить с конца,
	// должен работать за amort(O(1))
	void popBack();
	// удалить
	// должен работать за O(n)
	void popFront();
	void erase(const size_t pos);
	void erase(const size_t pos, size_t len);            // удалить len элементов начиная с i

	// найти элемент,
	// должен работать за O(n)
	// если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
	// если искомого элемента нет, вернуть end
	ConstVectorIterator find(const T& value, bool isBegin = true);

	// зарезервировать память (принудительно задать capacity)
	void reserve(const size_t newCapacity);

	// изменить размер
	// если новый размер больше текущего, то новые элементы забиваются value
	// если меньше - обрезаем вектор
	void resize(const size_t newSize, const T& value = T());

	// очистка вектора, без изменения capacity
	void clear();

	void reallocVector(const size_t newSize = size());
	bool isLoaded() const;
private:
	T* _data;
	size_t _size;
	size_t _capacity;
	ResizeStrategy _resizeStrategy;
	float _coef;
};
