#pragma once
#include "Block.hpp"
#include <iostream>

namespace Persistent{
  class BlockStorage {
    private:
      const size_t STORAGE_SIZE;   //constexpr or better non const???

    public:
      typedef void (*readMemoryFunction)(void* data_out, uint16_t address, size_t __n);
      readMemoryFunction readMemory;

      typedef void (*writeMemoryFunction)(const void* data_in, uint16_t address, size_t __n);
      writeMemoryFunction writeMemory;

      // Sizes must be a power of 2
      BlockStorage(const size_t STORAGE_SIZE, readMemoryFunction readMemory, writeMemoryFunction writeMemory)
      :STORAGE_SIZE{STORAGE_SIZE}, readMemory{readMemory}, writeMemory{writeMemory} {  }

      constexpr size_t storageSize() const {return STORAGE_SIZE;}
      constexpr size_t blockSize() const {return sizeof(Block);}
      constexpr size_t blocksCount() const {return storageSize() / sizeof(Block);}
  };
}