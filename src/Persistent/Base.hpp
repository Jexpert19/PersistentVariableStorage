#pragma once
#include <stdlib.h>
#include "Block.hpp"
#include "Error.hpp"

namespace Persistent{
    class Base{
        private:
        const size_t STORAGE_SIZE;      //constexpr???

        public:
        // Sizes must be a power of 2
        Base(const size_t STORAGE_SIZE)
        :STORAGE_SIZE{STORAGE_SIZE} {    }

        constexpr size_t storageSize() const {return STORAGE_SIZE;}
        constexpr size_t blocksCount() const {return storageSize() / sizeof(Block);}
        constexpr uint16_t firstBlockAddress() const {return 0;}
        constexpr uint16_t lastBlockAddress() const {return storageSize() - sizeof(Block);}

        virtual void read(void* data_out, uint16_t address, size_t __n) = 0;
        virtual void write(const void* data_in, uint16_t address, size_t __n) = 0;
    };
}