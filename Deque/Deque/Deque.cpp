﻿// Deque.cpp: определяет точку входа для приложения.
//
#include <iostream>

#include "Deque.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
template <class elemType, class memoryAllocatorClass = memoryAllocator>
void UsersPrintDeque(const deque<elemType, memoryAllocatorClass>& dq) {
	for (deque<int>::dequeIterator dI = dq.Begin(); dI != dq.End(); dI.Next())
		std::cout << dI.GetElement() << " ";
	std::cout << std::endl;
}

template <class elemType, class memoryAllocatorClass = memoryAllocator>
void UsersPrintDequeLikeAMassive(const deque<elemType, memoryAllocatorClass>& dq) {
	for (unsigned int i = 0; i < dq.Size(); i++)
		std::cout << dq[i] << " ";
	std::cout << std::endl;
}

template <class elemType, class memoryAllocatorClass = memoryAllocator>
void GetReverseDequeFromBegin(deque<elemType, memoryAllocatorClass>& dq) {
	deque<elemType, memoryAllocatorClass> dqReversed;

	while (!dq.isEmpty()) {
		dqReversed.PushBegin(dq.GetBegin());
		dq.DeleteBegin();
	}

	dq = dqReversed;
}

template <class elemType, class memoryAllocatorClass = memoryAllocator>
void GetReverseDequeFromEnd(deque<elemType, memoryAllocatorClass>& dq) {
	deque<elemType, memoryAllocatorClass> dqReversed;

	while (!dq.isEmpty()) {
		dqReversed.PushEnd(dq.GetEnd());
		dq.DeleteEnd();
	}

	dq = dqReversed;
}

template <class elemType, class memoryAllocatorClass = memoryAllocator>
deque<elemType, memoryAllocatorClass> SumTwo(deque<elemType, memoryAllocatorClass>& dq1, deque<elemType, memoryAllocatorClass>& dq2) {
	deque<elemType, memoryAllocatorClass> dq = dq1 + dq2;
	return dq;
}

void TestProcedure(void) {
	deque<int> d1;
	std::cout << "Check default constructor and iterators' working with empty deque: " << std::endl;
	UsersPrintDeque(d1);
	std::cout << std::endl;

	deque<int> d2{ 1, 15, 2, 14, 3, 13 };
	std::cout << "Check initializer list constructor: " << std::endl;
	UsersPrintDeque(d2);
	std::cout << std::endl;

	std::cout << "Check copy constructor[orig and new deques]: " << std::endl;
	deque<int> d3(d2);
	UsersPrintDeque(d2);
	UsersPrintDeque(d3);
	std::cout << std::endl;

	std::cout << "Check move constructor: " << std::endl;
	deque<int> d4(SumTwo(d2, d3));
	//deque<int> d4(deque<int>({ 1, 15, 2, 14, 3, 13 }));
	UsersPrintDeque(d4);
	std::cout << std::endl;

	std::cout << "Check copy operator= [orig and new deques]: " << std::endl;
	d3 = d2;
	UsersPrintDeque(d2);
	UsersPrintDeque(d3);
	std::cout << std::endl;

	std::cout << "Check move operator= (with sum, which returned rvalue): " << std::endl;
	d3 = SumTwo(d2, d3);
	UsersPrintDeque(d3);
	std::cout << std::endl;

	// check operations
	std::cout << "Check reverse with 'GetBegin()', 'DeleteBegin()', 'AddBegin()' and 'isEmpty()' methods and iterators' methods: " << std::endl;
	UsersPrintDeque(d4);
	GetReverseDequeFromBegin(d4);
	UsersPrintDeque(d4);
	std::cout << std::endl;

	std::cout << "Check reverse with 'GetEnd()', 'DeleteEnd()', 'AddEnd()' and 'isEmpty()' methods and iterators' methods: " << std::endl;
	UsersPrintDeque(d2);
	GetReverseDequeFromEnd(d2);
	UsersPrintDeque(d2);
	std::cout << std::endl;

	std::cout << "Check operator[] and 'Size()' methods: " << std::endl;
	deque<char> charDq = deque<char>{ 'h', 'e', 'h', 'e', ' ' } + deque<char>{'h', 'a', 'h', 'a', '!'};
	UsersPrintDequeLikeAMassive(charDq);
	std::cout << std::endl;
}

int main() {
	TestProcedure();
	_CrtDumpMemoryLeaks();
	return 0;
}
