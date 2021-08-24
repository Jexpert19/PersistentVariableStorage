#pragma once
#include "PersistentStorageBase.hpp"
#include "address.hpp"

namespace PersistentStorage{
    class BlockPointer{
        private:
        size_t storageSize;
        size_t blockSize;

        public:
        persistentAddress_t address;

        BlockPointer(size_t storageSize, size_t blockSize, persistentAddress_t address = 0)
        :storageSize{storageSize}, blockSize{blockSize}, address{address}{ }

        void toNextBlock(){
            address = (address + blockSize) & (storageSize - 1);
        }

        void toPreviousBlock(){
            address = (address - blockSize) & (storageSize - 1);
        }
    };
}
