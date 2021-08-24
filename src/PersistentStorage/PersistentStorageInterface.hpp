#pragma once
#include "address.hpp"
#include <stdlib.h>

namespace PersistentStorage{
    class PersistentStorageInterface{
        public:
        const size_t SIZE;

        PersistentStorageInterface(const size_t size)
        :SIZE{size} { }

        virtual void init() = 0;
        virtual void read(void* data_out, persistentAddress_t address, size_t __n) = 0;
        virtual void write(const void* data_in, persistentAddress_t address, size_t __n) = 0;
    };
}
