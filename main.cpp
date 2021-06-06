#include "templates.cpp"

int main()
{
	MyVector<int> first(4, 7, ResizeStrategy::Multiplicative, 2);
	MyVector<int> second(3, 2, ResizeStrategy::Multiplicative, 2);
	first.insert(4, second);
	std::cout << "capacity = " << first.capacity() << std::endl;
	std::cout << "loadFactor = " << first.loadFactor() << std::endl;

	MyVector<int> third(1, ResizeStrategy::Multiplicative, 2 );
	third.pushBack(2);
	third.pushBack(3);
	MyVector<int>::ConstVectorIterator h(third.cbegin());
	third.insert(h, 1);
	//.insert(third.cend(), first);
	std::cout << "capacity = " << third.capacity() << std::endl;
	std::cout << *(third.find(2, true)) << std::endl;
}
