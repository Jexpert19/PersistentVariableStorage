#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Block.hpp"
#include "Storage.hpp"

namespace Persistent{
    template<typename T>
    class Variable{
        private:
        static constexpr uint16_t BLOCKS_RESERVED = (sizeof(T)-1)/Block::BODYSIZE + 1;
        const uint8_t FIRST_UNIQUE_KEY;
        Storage* persistentStorage;

        public:
        Variable(UniqueKeyGenerator& keyGenerator, Storage& persistentStorage)
        :FIRST_UNIQUE_KEY{keyGenerator.getKeys(BLOCKS_RESERVED)},
        persistentStorage{&persistentStorage} {}

        void writeToPersistentStorage(const void* data) {
            for(uint16_t n=0; n < BLOCKS_RESERVED; ++n){
                Block block{};
                memcpy(block.body.data, (uint8_t*)data+n*Block::BODYSIZE, getSizeofDataBlock(n));
                persistentStorage->write(FIRST_UNIQUE_KEY+n, block);
            }
        }

        void getFromPersistentStorage(void* data){
            for(uint16_t n=0; n < BLOCKS_RESERVED; ++n){
                Block block{};
                persistentStorage->read(FIRST_UNIQUE_KEY+n, block);
                memcpy((uint8_t*)data + n*Block::BODYSIZE, block.body.data, getSizeofDataBlock(n));
            }
        }

        void removeFromStorage(){
            for(uint16_t n=0; n < BLOCKS_RESERVED; ++n){
                persistentStorage->remove(FIRST_UNIQUE_KEY+n);
            }
        }

        private:

        size_t getSizeofDataBlock(uint8_t blockIndex){
            if(!isLastBlock(blockIndex)){
                return Block::BODYSIZE;
            }
            else{
                return lastBlockSize();
            }
        }

        bool isLastBlock(uint8_t blockIndex){
            return blockIndex == BLOCKS_RESERVED-1;
        }

        uint8_t lastBlockSize(){
            if(dataFitsPerfectly()){
                return Block::BODYSIZE;
            }
            else{
                return sizeof(T) % Block::BODYSIZE;
            }
        }

        bool dataFitsPerfectly(){
            return sizeof(T) == Block::BODYSIZE;
        }
    };

    template<typename T>
    class VariableWithRam : public Variable<T>{
        private:
        Storage* persistentStorage;
        bool AUTOMATIC_WRITES;
        bool isDeleted;
        T volatile_data;

        public:
        Variable(UniqueKeyGenerator& keyGenerator, Storage *persistentStorage, bool AUTOMATIC_WRITES = true)
        :FIRST_UNIQUE_KEY{keyGenerator.getKeys(BLOCKS_RESERVED)},
        persistentStorage{persistentStorage},
        AUTOMATIC_WRITES{AUTOMATIC_WRITES},
        volatile_data{0}{

        }

        void write(const T& value){
            isDeleted = false;
            volatile_data = value;

            if(AUTOMATIC_WRITES){
                writeToPersistentStorage();
            }
        }

        const T& read() const {
            return volatile_data;
        }

        void remove(){
            isDeleted = true;
            removeFromStorage();
        }
    };
}