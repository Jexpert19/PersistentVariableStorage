#pragma once
#include "Base.hpp"
#include "BlockPointer.hpp"

namespace Persistent{
    class Iterator{
        private:
        Base* base;
        BlockPointer ptr;

        public:
        Iterator(Base& base)
        :base{&base} { }

        template<typename T>
        friend T& operator*(Iterator& it){
            
        }

        friend Iterator& operator++(){

            return *this;
        }

        /*friend Iterator& operator++(int){
            auto& oldVal = this;
            return oldVal;
        }*/

        friend Iterator& operator--(){

        }

        /*friend Iterator& operator--(int){

        }*/

        friend Iterator& operator==(const Iterator& it1, const Iterator& it2){

        }

        friend Iterator& operator!=(const Iterator& it1, const Iterator& it2){
            
        }
    };

    class HeadIterator : public Iterator<Block::Head>{
        
    };
}