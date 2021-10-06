#pragma once

#include <cstdlib>

class memoryAllocator {
public:
  void* alloc(const int& sizeOfMemoryBlock) {
    return (unsigned char*)malloc(sizeOfMemoryBlock);
  }

  void clear(void* ptrToClear) {
    free(ptrToClear);
  }
};