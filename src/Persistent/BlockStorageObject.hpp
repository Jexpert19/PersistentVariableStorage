#pragma once
#include "BlockStorage.hpp"

namespace Persistent{
  class BlockStorageObject{
    private:
      BlockStorage *storage;
      uint16_t address;
      bool blockBuffered;
      Block bufferedBlock;

    public:
      BlockStorageObject(BlockStorage& storage, uint16_t address = 0)
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

        void setBlock(Block &block){
          storage->writeMemory(&block, getAddress(), storage->blockSize());
        }

        void setBlockHead(){

        }

    class ConstIterator{
      private:
        Block bufferedBlock;
        bool blockBuffered = false;

      public:
        ConstIterator()
        { }
        
        friend bool operator==(const ConstIterator& it1, const ConstIterator& it2){
          return it1.getAddress() == it2.getAddress();
        }

        friend bool operator!=(const ConstIterator& it1, const ConstIterator& it2){
          return it1.getAddress() != it2.getAddress();
        }
    };

    class Iterator{
      private:
        

      public:
        Iterator(BlockStorage& storage, uint16_t address = 0)
        :ConstIterator{storage, address} {  }

        
    };
  };
}