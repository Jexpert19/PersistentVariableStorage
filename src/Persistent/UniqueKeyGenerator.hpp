#pragma once
#include <stdint.h>

namespace Persistent{
  class UniqueKeyGenerator{
    private:
    uint8_t nextKey = 0;

    public:
    uint8_t getKeys(uint8_t n){
      uint8_t key = nextKey;
      nextKey += n;
      return key;
    }
  };
}