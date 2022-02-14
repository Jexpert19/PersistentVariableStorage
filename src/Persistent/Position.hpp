#pragma once
#include "BlockStorage.hpp"
#include <stdbool.h>

namespace Persistent{
  class Position{
    private:
    BlockStorage::Iterator readPosition;
    bool sentinelWriteValue{0};

    public:
    Position(BlockStorage& storage)
    :readPosition{storage}{
      initalizeFromStorage();
    }

    private:
    void initalizeFromStorage(){
      Block::Head previousHead, currentHead;
      previousHead = readPosition.getBlockHead();
      auto end = readPosition;

      // Search sentienl change
      do{
        readPosition.toNextBlock();

        currentHead = readPosition.getBlockHead();

        if(previousHead.sentinel != currentHead.sentinel){
          readPosition.toPreviousBlock();
          sentinelWriteValue = previousHead.sentinel;
          return;
        }

        previousHead = currentHead;
      }
      while(readPosition != end);

      // No sentinel change found
      readPosition.toPreviousBlock();
      sentinelWriteValue = !currentHead.sentinel;
    }

    public:
    uint16_t getReadPosition(){
      return readPosition.getAddress();
    }

    uint16_t getWritePosition(){
      auto it{readPosition};
      it.toNextBlock();
      return it.getAddress();
    }

    bool getSentinelWriteValue(){
      return sentinelWriteValue;
    }

    void toNextBlock(){
      readPosition.toNextBlock();

      // One full iteration through memory
      if(readPosition.getAddress() == 0){
        sentinelWriteValue ^= true;
      }
    }
  };
}