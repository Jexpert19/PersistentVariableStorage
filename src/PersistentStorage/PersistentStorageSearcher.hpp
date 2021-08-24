#pragma once
#include <stdlib.h>
#include "PersistentStorageBase.hpp"
#include "PersistentStoragePosition.hpp"
#include "error.hpp"
#include "PersistentBlock.hpp"
#include "address.hpp"

namespace PersistentStorage{
    template<size_t BLOCK_SIZE>
    class PersistentStorageSearcher{
        private:
        PersistentStorageBase<BLOCK_SIZE> *storageBase;
        PersistentStoragePosition<BLOCK_SIZE> *position;

        public:
        PersistentStorageSearcher(PersistentStorageBase<BLOCK_SIZE> *storageBase, PersistentStoragePosition<BLOCK_SIZE> *position)
        :storageBase{storageBase}, position{position}{ }

        Error findLatest(PersistentBlockHead* targetHead, persistentAddress_t* out_address){
            BlockPointer ptr{storageBase->EEPROM_SIZE, storageBase->BLOCK_SIZE, position->getReadPosition()};
            PersistentBlockHead head;

            do{
                storageBase->getHead(ptr.address, head);

                if(head.key == targetHead->key){
                    *out_address = ptr.address;
                    return Error::ok;
                }

                ptr.toNextBlock();
            }while(ptr.address != position->getReadPosition());

            return Error::not_found;
            }
    };
}