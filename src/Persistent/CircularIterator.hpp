#pragma once
#include "BlockStorage.hpp"
#include <string.h>
/*
namespace Persistent{
  
  class CircularIterator{
    private:
    CircularBlockIterator blockIt;

    public:
    CircularIterator(CircularBlockIterator blockIt)
    :blockIt{blockIt} { }

    uint16_t getAddress() const {
      return blockIt.getAddress();
    }

    void setAddress(uint16_t address){
      blockIt.setAddress(address);
    }

    void toNextBlock(){
      // Move to last block of one object
      while(!blockIt.getBlockHead().blockSequenceEnd){
        blockIt.toNextBlock();
      }

      // To next object
      blockIt.toNextBlock();
    }

    void toPreviousBlock(){
      // Check if the previous object is bigger than one block
      blockIt.toPreviousBlock();
      blockIt.toPreviousBlock();

      // Previous object is one block wide
      if(blockIt.getBlockHead().blockSequenceEnd){
        blockIt.toNextBlock();
        return;
      }

      // Previous object is bigger than one block
      do{
        blockIt.toPreviousBlock();
      } while(!blockIt.getBlockHead().blockSequenceEnd);
      blockIt.toNextBlock();
    }

    template<typename T>
    T getData(){
      T data;
      Block block;
      uint16_t n = 0;
      
      do{
        block = blockIt.getBlock();
        memcpy(((char*)data + n*sizeof(block)), &block, Block::BODYSIZE);
        blockIt.toNextBlock();
        n++;
      } while(!blockIt.getBlockHead().blockSequenceEnd);

      // Reset block iterator
      for(uint16_t i=0; i < n; i++){
        blockIt.toPreviousBlock();
      }

      return data;
    }

    Block::Head getDataHead(){
      return blockIt.getBlockHead();
    }
    
    friend bool operator==(const CircularIterator& it1, const CircularIterator& it2){
      return it1.getAddress() == it2.getAddress();
    }

    friend bool operator!=(const CircularIterator& it1, const CircularIterator& it2){
      return it1.getAddress() != it2.getAddress();
    }
  };
}*/