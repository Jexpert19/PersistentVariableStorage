#pragma once
#include "StorageAdapter.hpp"
#include <stdbool.h>

namespace Persistent{
    class CircularBlockIterator{
        private:
        StorageAdapter *storage;
        uint16_t address;

        Block bufferedBlock;
        bool blockBuffered = false;
        
        public:
        CircularBlockIterator(StorageAdapter& storage, uint16_t address = 0)
        :storage{&storage}, address{address}{ }

        uint16_t getAddress() const {
            return address;
        }

        void setAddress(uint16_t address){
            blockBuffered = false;
            this->address = address;
        }

        void toNextBlock(){
            blockBuffered = false;
            address = (address + storage->blockSize()) & (storage->storageSize() - 1);
        }

        void toPreviousBlock(){
            blockBuffered = false;
            address = (address - storage->blockSize()) & (storage->storageSize() - 1);
        }

        Block getBlock(){
            if(blockBuffered){
                return bufferedBlock;
            }

            Block block{};
            storage->readMemory(&block, address, storage->blockSize());

            bufferedBlock = block;
            blockBuffered = true;

            return block;
        }

        Block::Head getBlockHead(){
            if(blockBuffered){
                return bufferedBlock.head;
            }

            Block::Head head{};
            storage->readMemory(&head, address, Block::HEADSIZE);
            return head;
        }

        Block::Body getBlockBody(){
            if(blockBuffered){
                return bufferedBlock.body;
            }

            Block block{};
            storage->readMemory(&block, address, storage->blockSize());

            bufferedBlock = block;
            blockBuffered = true;

            return block.body;
        }
        
        friend bool operator==(const CircularBlockIterator& it1, const CircularBlockIterator& it2){
            return it1.getAddress() == it2.getAddress();
        }

        friend bool operator!=(const CircularBlockIterator& it1, const CircularBlockIterator& it2){
            return it1.getAddress() != it2.getAddress();
        }
    };
}
