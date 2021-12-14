#pragma once
#include "CircularBlockIterator.hpp"
#include <iterator>

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

            ###
            blockIt.toNextBlock();
       }

        void toPreviousBlock(){

            ###
            blockIt.toPreviousBlock();
        }

        template<typename T>
        Block getData(){
            ###
        }

        Block::Head getDataHead(){
            blockIt.getBlockHead();
        }
        
        friend bool operator==(const CircularIterator& it1, const CircularIterator& it2){
            return it1.getAddress() == it2.getAddress();
        }

        friend bool operator!=(const CircularIterator& it1, const CircularIterator& it2){
            return it1.getAddress() != it2.getAddress();
        }
    };
}