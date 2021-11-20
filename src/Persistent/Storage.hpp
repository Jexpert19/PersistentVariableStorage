#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include "BlockPointer.hpp"
#include "Error.hpp"
#include "Block.hpp"
#include "Base.hpp"
#include "Position.hpp"
#include "Searcher.hpp"
#include "Writer.hpp"

// the basic algorithm:
// https://sites.google.com/site/dannychouinard/Home/atmel-avr-stuff/eeprom-longevity

namespace Persistent{
    template<typename T>
    class Iterator{
        private:
        ptrTo???;
        BlockPointer ptr;

        public:
        Iterator(){}

        // Random access iterator?? think not ...
        // is: -> included in operator* ???
        friend T& operator*(Iterator& it){
            
        }

        friend Iterator& operator++(){
            
        }

        friend Iterator& operator++(int){
            
        }

        friend Iterator& operator--(){

        }

        friend Iterator& operator--(int){

        }

        friend Iterator& operator==(const Iterator& it1, const Iterator& it2){

        }

        friend Iterator& operator!=(const Iterator& it1, const Iterator& it2){
            
        }
    };


    class Storage{
        private:
        Base *storageBase;
        Position position{storageBase};
        Searcher searcher{storageBase, &position};
        Writer writer{storageBase, &position, &searcher};

        public:
        Storage(Base *storage)
        :storageBase{storage}{  }

        Error read(const uint8_t KEY, Block &data);
        Error write(const uint8_t KEY, Block &data);
        void remove(const uint8_t KEY);

        // What if contents are modified between iterator uses
        Iterator begin(); // Pointing to latest element.    both bidirectional??? or just forward
        Iterator begin(const uint8_t KEY);
        
        // Pointing behind last element!?
        Iterator end();
        Iterator end(const uint8_t KEY);
        



        //iteratorclass rend(const uint8_t KEY);   // Pointing to oldest element.    rend or end???


        void complete_format();
    };
}