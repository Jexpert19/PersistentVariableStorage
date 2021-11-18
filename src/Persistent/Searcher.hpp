#pragma once
#include <stdlib.h>
#include "Base.hpp"
#include "Position.hpp"
#include "Error.hpp"
#include "Block.hpp"

namespace Persistent{
    class Searcher{
        private:
        Base *storageBase;
        Position *position;

        public:
        Searcher(Base *storageBase, Position *position)
        :storageBase{storageBase}, position{position}{ }

        Error findLatest(Block::Head* targetHead, uint16_t* out_address){
            BlockPointer ptr{storageBase->storageSize(), sizeof(Block), position->getReadPosition()};
            Block::Head head;

            do{
                storageBase->read(&head, ptr.getAddress(), Block::HEADSIZE);

                if(head.key == targetHead->key){
                    *out_address= ptr.getAddress();
                    return Error::ok;
                }

                ptr.toNextBlock();
            }while(ptr.getAddress()!= position->getReadPosition());

            return Error::not_found;
            }
    };
}