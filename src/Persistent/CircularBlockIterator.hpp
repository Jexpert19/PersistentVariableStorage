#pragma once
#include "StorageAdapter.hpp"
#include <stdbool.h>

namespace Persistent{
    class CircularBlockIterator{
        private:
        StorageAdapter *storage;
        uint16_t address;
        
        public:
        CircularBlockIterator(StorageAdapter& storage, uint16_t address = 0)
        :storage{&storage}, address{address}{ }

        uint16_t getAddress() const {
            return address;
        }

        void setAddress(uint16_t address){
            this->address = address;
        }

        void toNextBlock(){
            address = (address + storage->blockSize()) & (storage->storageSize() - 1);
        }

        void toPreviousBlock(){
            address = (address - storage->blockSize()) & (storage->storageSize() - 1);
        }

        Block getBlock(){
            Block data{};
            storage->readMemory(&data, address, storage->blockSize());
            return data;
        }

        Block::Head getBlockHead(){
            Block::Head head{};
            storage->readMemory(&head, address, Block::HEADSIZE);
            return head;
        }

        Block::Body getBlockBody(){
            Block::Body body{};
            storage->readMemory(&body, address, Block::BODYSIZE);
            return body;
        }
        
        friend bool operator==(const CircularBlockIterator& it1, const CircularBlockIterator& it2){
            return it1.getAddress() == it2.getAddress();
        }

        friend bool operator!=(const CircularBlockIterator& it1, const CircularBlockIterator& it2){
            return it1.getAddress() != it2.getAddress();
        }
    };
}
