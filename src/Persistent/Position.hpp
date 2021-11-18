#pragma once
#include <stdbool.h>
#include "Base.hpp"
#include "BlockPointer.hpp"

namespace Persistent{
    class Position{
        private:
        Base *base;
        BlockPointer readPosition;
        bool sentinelWriteValue{0};

        public:
        Position(Base *base)
        :base{base},
        readPosition{base->storageSize(), sizeof(Block)}{
            initalizeFromStorage();
        }

        private:
        void initalizeFromStorage(){
            BlockPointer ptr{base->storageSize(), sizeof(Block), base->firstBlockAddress()};
            Block::Head previousHead, currentHead;
        
            base->read(&previousHead, ptr.getAddress(), Block::HEADSIZE);

            do{
                ptr.toNextBlock();   

                base->read(&currentHead, ptr.getAddress(), Block::HEADSIZE);

                if(previousHead.sentinel != currentHead.sentinel){
                    ptr.toPreviousBlock();
                    readPosition.setAddress(ptr.getAddress());
                    sentinelWriteValue = previousHead.sentinel;
                    return;
                }

                previousHead = currentHead;
            }while(ptr.getAddress() != base->lastBlockAddress());

            readPosition.setAddress(base->lastBlockAddress());
            sentinelWriteValue = !currentHead.sentinel;
        }

        public:
        uint16_t getReadPosition(){
            return readPosition.getAddress();
        }

        uint16_t getWritePosition(){
            BlockPointer ptr{readPosition};
            ptr.toNextBlock();
            return ptr.getAddress();
        }

        bool getSentinelWriteValue(){
            return sentinelWriteValue;
        }

        void toNextBlock(){
            uint16_t old = readPosition.getAddress();
            readPosition.toNextBlock();

            // Update sentinel
            if(readPosition.getAddress()< old){
                sentinelWriteValue ^= true;
            }
        }
    };
}