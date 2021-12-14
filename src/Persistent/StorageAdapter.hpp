#pragma once
#include "Block.hpp"

namespace Persistent{
    class StorageAdapter{
        private:
        const size_t STORAGE_SIZE;      //constexpr???

        public:
        // Sizes must be a power of 2
        StorageAdapter(const size_t STORAGE_SIZE)
        :STORAGE_SIZE{STORAGE_SIZE} {    }

        constexpr size_t storageSize() const {return STORAGE_SIZE;}
        constexpr size_t blockSize() const {return sizeof(Block);}
        constexpr size_t blocksCount() const {return storageSize() / sizeof(Block);}

        virtual void readMemory(void* data_out, uint16_t address, size_t __n) = 0;
        virtual void writeMemory(const void* data_in, uint16_t address, size_t __n) = 0;
    };
}