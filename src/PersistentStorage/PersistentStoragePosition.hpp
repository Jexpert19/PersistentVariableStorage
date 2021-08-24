#pragma once
#include <stdbool.h>
#include "PersistentStorageBase.hpp"
#include "BlockPointer.hpp"

namespace PersistentStorage{
    template<size_t BLOCK_SIZE>
    class PersistentStoragePosition{
        private:
        PersistentStorageBase<BLOCK_SIZE>* base;
        BlockPointer readPosition;
        bool sentinelWriteValue{0};

        public:
        PersistentStoragePosition(PersistentStorageBase<BLOCK_SIZE>* base)
        :base{base},
        readPosition{base->EEPROM_SIZE, base->BLOCK_SIZE}{ }

        void initalizeFromStorage(){
            BlockPointer ptr{base->EEPROM_SIZE, base->BLOCK_SIZE, base->FIRST_BLOCK};
            PersistentBlockHead previousHead, currentHead;
        
            base->getHead(ptr.address, previousHead);    

            do{
                ptr.toNextBlock();   

                base->getHead(ptr.address, currentHead);

                if(previousHead.sentinel != currentHead.sentinel){
                    ptr.toPreviousBlock();
                    readPosition.address = ptr.address;
                    sentinelWriteValue = previousHead.sentinel;
                    return;
                }

                previousHead = currentHead;
            }while(ptr.address != base->LAST_BLOCK);

            readPosition.address = base->LAST_BLOCK;
            sentinelWriteValue = !currentHead.sentinel;
        }

        persistentAddress_t getReadPosition(){
            return readPosition.address;
        }

        persistentAddress_t getWritePosition(){
            BlockPointer ptr{readPosition};
            ptr.toNextBlock();
            return ptr.address;
        }

        bool getSentinelWriteValue(){
            return sentinelWriteValue;
        }

        void toNextBlock(){
            persistentAddress_t old = readPosition.address;
            readPosition.toNextBlock();

            // Update sentinel
            if(readPosition.address < old){
                sentinelWriteValue ^= true;
            }
        }
    };
}