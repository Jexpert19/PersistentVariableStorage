#pragma once
#include "Base.hpp"

namespace Persistent{
    class BlockPointer{
        private:
        size_t storageSize;
        size_t blockSize;
        uint16_t address;
        
        public:
        BlockPointer(size_t storageSize, size_t blockSize, uint16_t address = 0)
        :storageSize{storageSize}, blockSize{blockSize}, address{address}{ }

        uint16_t getAddress(){
            return address;
        }

        void setAddress(uint16_t address){
            this->address = address;
        }

        void toNextBlock(){
            address = (address + blockSize) & (storageSize - 1);
        }

        void toPreviousBlock(){
            address = (address - blockSize) & (storageSize - 1);
        }
    };
}
