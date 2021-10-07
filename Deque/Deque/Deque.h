#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include "memoryAllocator.h"

/**
@brief Double linked list class
@detailed Double linked list class, which intitialized by element type
and memory allocation class, which must include methods 'void * alloc(unsigned int size)'
and 'void clear(void *ptr)'
@tparam elemType elements type
@tparam memoryAllocatorClass memory allocation strategy
*/
template<class elemType, class memoryAllocatorClass = memoryAllocator>
class deque {
private:
  /**
  @brief memory allocator
  */
  memoryAllocatorClass allocator;

  /**
  @brief one deque element struct
  */
  struct element {
    elemType value;         ///< element value
    element *prev,          ///< pointer to prev element
            *next;          ///< pointer to next element
  };

  element *begin,     ///< deque begin
          *end;       ///< deque end
  unsigned int size;  ///< elements count
public:

  /**
   @brief deque iterator
   */
  class dequeIterator {
  private:
    element* elem;      ///< pointer to deque element
  public:
    /**
    * constructor by deque begin
    * @param[in] dq - deque const reference to create iterator for
    */
    dequeIterator(const deque& dq) : elem(dq->begin) {};

    /**
    * constructor by element
    * @param[in] el - element pointer to iterator
    */
    dequeIterator(element* el) : elem(el) {};

    /**
    * copy operator= for iterator
    * @param[in] di - deque iterator const reference 
    */
    dequeIterator& operator=(const dequeIterator& di) {
      elem = di->elem;
      return *this;
    };

    /**
    * Shift iterator to next element
    * @warning throw exception if iterator contatin 'nullptr' pointer
    */
    void Next(void) {
      if (elem == nullptr)
        throw std::exception("Iterator is out of range");
      elem = elem->next;
    }

    /**
    * Shift iterator to prev element
    * @warning throw exception if iterator contatin 'nullptr' pointer
    */
    void Prev(void) {
      if (elem == nullptr)
        throw std::exception("Iterator is out of range");
      elem = elem->prev;
    }

    /**
    * Operator != for deque iterators
    * @param[in] di - deque iterator const reference to comparsion
    */
    bool operator!= (const dequeIterator& di) {
      return elem != di.elem ? 1 : 0;
    }

    /**
    * Operator != for deque iterators
    * @param[in] di - deque iterator const reference to comparsion
    */
    bool operator== (const dequeIterator& di) {
      return elem == di.elem ? 1 : 0;
    }

    /**
    * Returns value of deque iterator's element
    * @warning throw exception if iterator contatin 'nullptr' pointer
    */
    elemType& GetElement() {
      if (elem == nullptr)
        throw std::exception("Get value from null iterator");

      return elem->value;
    }
  };


  /**
    * Default deque constructor
    */
  deque() : begin(nullptr), end(nullptr), size(0) {};

  /**
    * Deque constructor with initializer list
    * @param[in] valueList - list of 'elemType' values
    */
  deque(std::initializer_list<elemType> valueList) : begin(nullptr), end(nullptr), size(0) {
    for (auto& val : valueList)
      PushEnd(val);
  };

  /**
    * Copy constructor
    * @param[in] dq - deque const reference to copy
    */
  deque(const deque& dq) : begin(nullptr), end(nullptr), size(0) {
    for (dequeIterator di = dq.Begin(); di != dq.End(); di.Next())
      PushEnd(di.GetElement());
  };

  /**
    * Move constructor
    * @param[in] dq - deque rvalue reference to move
    */
  deque(deque&& dq) : begin(nullptr), end(nullptr), size(0) {
    begin = dq.begin;
    end = dq.end;
    size = dq.size;

    dq.begin = dq.end = nullptr;
    dq.size = 0;
  };

  /**
    * Copy operator=
    * @param[in] dq - deque const reference to copy
    * @return deque reference
    */
  deque& operator=(const deque& dq) {
    if (&dq != this) {
      Clear();
      begin = end = nullptr;
      size = 0;

      for (dequeIterator di = dq.Begin(); di != dq.End(); di.Next())
        PushEnd(di.GetElement());
    }
    return *this;
  }

  /**
    * Move operator=
    * @param[in] dq - deque rValue reference to move
    * @return deque reference
    */
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

  /**
    * Check is deque empty method
    * @return 1 - deque is empty, 0 - deque is not empty
    */
  bool isEmpty() const {
    return begin == nullptr ? 1 : 0;
  }

  /**
    * Get deque size method
    * @return deque count elements
    */
  unsigned int Size() const {
    return size;
  }

  /**
    * Push element to deque begin
    * @warning Throw exception if not enought memory for new element
    * @param[in] value - const reference to value
    */
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

  /**
    * Push element to deque begin (with move semantic)
    * @warning Throw exception if not enought memory for new element
    * @param[in] value - rValue reference to value
    */
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

  /**
    * Push element to deque end
    * @warning Throw exception if not enought memory for new element
    * @param[in] value - const reference to value
    */
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

  /**
    * Push element to deque end (with move semantic)
    * @warning Throw exception if not enought memory for new element
    * @param[in] value - rValue reference to value
    */
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

  /**
    * Add element to deque end 'operator+'
    * @warning Throw exception if not enought memory for new element
    * @param[in] value - const reference to value
    * @return deque reference
    */
  deque& operator+(const elemType& value) {
    PushEnd(value);
    return *this;
  }

  /**
    * Add element to deque end 'operator+' (with move semantic)
    * @warning Throw exception if not enought memory for new element
    * @param[in] value - rValue reference to value
    * @return deque reference
    */
  deque& operator+(elemType&& value) {
    PushEnd(value);
    return *this;
  }

  /**
    * Get element from deque begin
    * @warning Throw exception if trying get element from empty deque
    * @return element from begin
    */
  elemType& GetBegin(void) {
    if (end == nullptr && begin == nullptr)
      throw std::exception("Trying get begin element from empty list");
    else
      return begin->value;
  }

  /**
    * Delete element from deque begin
    */
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

  /**
    * Get element from deque end
    * @warning Throw exception if trying get element from empty deque
    * @return element from end
    */
  elemType& GetEnd(void) {
    // if empty
    if (end == nullptr && begin == nullptr)
      throw std::exception("Trying get begin element from empty list");
    else
      return end->value;
  }

  /**
    * Delete element from deque end
    */
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

  /**
    * Add second deque list to first end method
    * @param[in] dq - const reference deque to add in end
    */
  void AddDeque(const deque& dq) {
    if (&dq == this) {
      deque<elemType, memoryAllocatorClass> newDeque(dq);
      for (dequeIterator di = newDeque.Begin(); di != newDeque.End(); di.Next())
        PushEnd(di.GetElement());
      newDeque.Clear();
    }
    else {
      for (dequeIterator di = dq.Begin(); di != dq.End(); di.Next())
        PushEnd(di.GetElement());
    }
  }

  /**
    * Add second deque list to first end method (with move semantic)
    * @param[in] dq - deque rValue reference to add in end
    */
  void AddDeque(deque&& dq) {
    if (dq.begin == nullptr)
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

  /**
    * Add second deque list to first end 'operator+'
    * @param[in] dq - deque const reference to add in end
    * @return deque reference as result
    */
  deque& operator+(const deque& dq) {
    if (this == &dq) {
      deque<elemType, memoryAllocatorClass> newDeque(dq);
      for (dequeIterator di = newDeque.Begin(); di != newDeque.End(); di.Next())
        PushEnd(di.GetElement());
      newDeque.Clear();
    }
    else
      for (dequeIterator di = dq.Begin(); di != dq.End(); di.Next())
        PushEnd(di.GetElement());
    return *this;
  }

  /**
    * Add second deque list to first end 'operator+' (with move semantic)
    * @param[in] dq - deque rValue reference to add in end
    * @return deque reference as result
    */
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

  /**
    * Transform deque to vector method
    * @return vector with deque's values
    */
  std::vector<elemType> toVector(void) {
    std::vector<elemType> newVec(size);

    if (newVec.size() != (int)size)
      throw std::exception("Not enough memory to create vector");

    int i = 0;
    for (dequeIterator dI = Begin(); dI != End(); dI.Next())
      newVec[i++] = dI.GetElement();

    return newVec;
  }

  /**
    * Get deque's element by index with operatot[]
    * @warning Don't use 'operator[]' to iterate in deque! Use 'dequeIterator' or 
    * transform deque to vector with 'toVector()' method
    * @return const value reference
    */
  const elemType& operator[](const unsigned int index) const {
    if (index >= size)
      throw std::exception("Index out of deque range");

    element* tmp = begin;
    for (unsigned int i = 0; i < index; i++)
      tmp = tmp->next;

    return tmp->value;
  }

  /**
    * Get deque's begin iterator method
    * @return deque iterator, which pointing to deque begin
    */
  dequeIterator Begin() const {
    return dequeIterator(begin);
  }

  /**
    * Get iterator, which pointing to the next element after the last one
    * @warning Returned iterator will be contain 'nullptr' pointer. Calling methods 'Next()', 'Prev()' and 'GetElement()' will crush programm
    * @return deque iterator, pointing to the next element after the last one
    */
  dequeIterator End() const {
    return dequeIterator(nullptr);
  }

  /**
  * Clear deque elements with choosen allocate strategy
  */
  void Clear(void) {
    while (!isEmpty())
      DeleteBegin();
  }

  /**
  * Deque destructor
  */
  ~deque() {
    Clear();
  }
};
