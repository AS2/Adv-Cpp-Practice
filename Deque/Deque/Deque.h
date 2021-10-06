// Deque.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <utility>
#include "memoryAllocator.h"

template<class elemType, class memoryAllocatorClass = memoryAllocator>
class deque {
private:
  memoryAllocatorClass allocator;

  struct element {
    elemType value;
    element* prev, * next;
  };
  element *begin, *end;
  unsigned int size;
public:

  class dequeIterator {
  private:
    element* elem;
  public:
    dequeIterator(const deque& dq) : elem(dq->begin) {};

    dequeIterator(element* el) : elem(el) {};

    dequeIterator& operator=(const dequeIterator& di) {
      elem = di->elem;
      return *this;
    };

    void Next(void) {
      if (elem == nullptr)
        throw std::exception("Iterator is out of range");
      elem = elem->next;
    }

    void Prev(void) {
      if (elem == nullptr)
        throw std::exception("Iterator is out of range");
      elem = elem->prev;
    }

    bool operator!= (const dequeIterator& di) {
      return elem != di.elem ? 1 : 0;
    }

    bool operator== (const dequeIterator& di) {
      return elem == di.elem ? 1 : 0;
    }

    elemType& GetElement() {
      if (elem == nullptr)
        throw std::exception("Get value from null iterator");

      return elem->value;
    }
  };


  // default constructor
  deque() : begin(nullptr), end(nullptr), size(0) {};

  // initializer list constructor
  deque(std::initializer_list<elemType> valueList) : begin(nullptr), end(nullptr), size(0) {
    for (auto& val : valueList)
      PushEnd(val);
  };

  // copy constructor
  deque(const deque& dq) : begin(nullptr), end(nullptr), size(0) {
    for (dequeIterator di = dq.Begin(); di != dq.End(); di.Next())
      PushEnd(di.GetElement());
  };

  // rValue reference constructor
  deque(deque&& dq) : begin(nullptr), end(nullptr), size(0) {
    begin = dq.begin;
    end = dq.end;
    size = dq.size;

    dq.begin = dq.end = nullptr;
    dq.size = 0;
  };

  // copy operator=
  deque& operator=(const deque& dq) {
    Clear();
    begin = end = nullptr;
    size = 0;

    for (dequeIterator di = dq.Begin(); di != dq.End(); di.Next())
      PushEnd(di.GetElement());
    return *this;
  }

  // rValue reference operator=
  deque& operator=(deque&& dq) {
    Clear();
    begin = end = nullptr;
    size = 0;

    begin = dq.begin;
    end = dq.end;
    size = dq.size;

    dq.begin = dq.end = nullptr;
    dq.size = 0;
    return *this;
  }

  bool isEmpty() const {
    return begin == nullptr ? 1 : 0;
  }

  unsigned int Size() const {
    return size;
  }

  void PushBegin(const elemType& value) {
    element* newElem = (element*)allocator.alloc(sizeof(element));
    if (newElem == nullptr)
      throw std::exception("Not enought memory for new element");

    newElem->prev = nullptr;
    newElem->value = value;

    newElem->next = begin;
    
    if (begin != nullptr)
      begin->prev = newElem;

    begin = newElem;
    if (end == nullptr)
      end = newElem;

    size++;
  }

  void PushBegin(elemType&& value) {
    element* newElem = (element*)allocator.alloc(sizeof(element));
    if (newElem == nullptr)
      throw std::exception("Not enought memory for new element");

    newElem->prev = nullptr;
    newElem->value = std::move(value);

    newElem->next = begin;

    if (begin != nullptr)
      begin->prev = newElem;

    begin = newElem;
    if (end == nullptr)
      end = newElem;

    size++;
  }

  void PushEnd(const elemType& value) {
    element* newElem = (element*)allocator.alloc(sizeof(element));
    if (newElem == nullptr)
      throw std::exception("Not enought memory for new element");

    newElem->prev = end;
    newElem->value = value;
    newElem->next = nullptr;

    if (end != nullptr)
      end->next = newElem;

    end = newElem;
    if (begin == nullptr)
      begin = newElem;

    size++;
  }

  void PushEnd(elemType&& value) {
    element* newElem = (element*)allocator.alloc(sizeof(element));
    if (newElem == nullptr)
      throw std::exception("Not enought memory for new element");

    newElem->prev = end;
    newElem->value = std::move(value);
    newElem->next = nullptr;

    if (end != nullptr)
      end->next = newElem;

    end = newElem;
    if (begin == nullptr)
      begin = newElem;

    size++;
  }

  deque& operator+(const elemType& value) {
    PushEnd(value);
    return *this;
  }

  deque& operator+(elemType&& value) {
    PushEnd(value);
    return *this;
  }

  elemType& GetBegin(void) {
    if (end == nullptr && begin == nullptr)
      throw std::exception("Trying get begin element from empty list");
    else
      return begin->value;
  }

  void DeleteBegin(void) {
    // if empty
    if (end == nullptr && begin == nullptr)
      return;
    else {
      element* elemToDelete = begin;
      begin = begin->next;

      // deleted last elem
      if (begin == nullptr)
        end = nullptr;
      else
        begin->prev = nullptr;

      allocator.clear((unsigned char*)elemToDelete);
      size--;
    }
  }

  elemType& GetEnd(void) {
    // if empty
    if (end == nullptr && begin == nullptr)
      throw std::exception("Trying get begin element from empty list");
    else
      return end->value;
  }

  void DeleteEnd(void) {
    // if empty
    if (end == nullptr && begin == nullptr)
      return;
    else {
      element* elemToDelete = end;
      end = end->prev;

      // deleted last elem
      if (end == nullptr)
        begin = nullptr;
      else
        end->next = nullptr;

      allocator.clear((unsigned char*)elemToDelete);
      size--;
    }
  }

  void AddDeque(const deque& dq) {
    for (dequeIterator di = dq->Begin(); di != dq->End(); di.Next())
      PushEnd(di.GetElement());
  }

  void AddDeque(deque&& dq) {
    if (dq->begin == nullptr)
      return;
    else if (begin == nullptr) {
      begin = dq.begin;
      end = dq.end;

      dq.begin = dq.end = nullptr;
    }
    else {
      end->next = dq.begin;
      dq.begin->prev = end;
      end = dq.end;
      size += dq.size;

      dq.begin = dq.end = nullptr;
    }
  }

  deque& operator+(const deque& dq) {
    for (dequeIterator di = dq.Begin(); di != dq.End(); di.Next())
      PushEnd(di.GetElement());

    return *this;
  }

  deque& operator+(deque&& dq) {
    if (dq.begin == nullptr)
      return *this;
    else if (begin == nullptr) {
      begin = dq.begin;
      end = dq.end;

      dq.begin = dq.end = nullptr;
    }
    else {
      end->next = dq.begin;
      dq.begin->prev = end;
      end = dq.end;
      size += dq.size;

      dq.begin = dq.end = nullptr;
    }

    return *this;
  }

  const elemType& operator[](const unsigned int index) const {
    if (index >= size)
      throw std::exception("Index out of deque range");

    element* tmp = begin;
    for (unsigned int i = 0; i < index; i++)
      tmp = tmp->next;

    return tmp->value;
  }

  dequeIterator Begin() const {
    return dequeIterator(begin);
  }

  dequeIterator End() const {
    return dequeIterator(nullptr);
  }

  void Clear(void) {
    while (!isEmpty())
      DeleteBegin();
  }

  ~deque() {
    Clear();
  }
};

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
