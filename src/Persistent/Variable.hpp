#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Block.hpp"

namespace Persistent{
    template<typename T>
    class Variable{
        private:
        static constexpr uint16_t BLOCKS_RESERVED = (sizeof(T)-1)/Block::BODYSIZE + 1;
        const uint8_t FIRST_UNIQUE_KEY;
        Storage* persistentStorage;
        bool AUTOMATIC_WRITES;
        bool notExisting;
        T volatile_data;

        public:
        Variable(UniqueKeyGenerator& keyGenerator, Storage *persistentStorage, bool AUTOMATIC_WRITES = true)
        :FIRST_UNIQUE_KEY{keyGenerator.getKeys(BLOCKS_RESERVED)},
        persistentStorage{persistentStorage},
        AUTOMATIC_WRITES{AUTOMATIC_WRITES},
        volatile_data{0}{

        }

        void write(const T& value){
            volatile_data = value;

            if(AUTOMATIC_WRITES){
                writeToPersistentStorage();
            }
        }

        const T& read() const {
            return volatile_data;
        }

        void writeToPersistentStorage() {
            for(uint16_t n=0; n < BLOCKS_RESERVED; ++n){
                Block data{};
                memcpy(data.body.data, (uint8_t*)&volatile_data+n*Block::BODYSIZE, getSizeofDataBlock(n));
                persistentStorage->write(FIRST_UNIQUE_KEY+n, data);
            }
        }

        void getFromPersistentStorage(){
            for(uint16_t n=0; n < BLOCKS_RESERVED; ++n){
                Block block{};
                persistentStorage->read(FIRST_UNIQUE_KEY+n, block);
                memcpy((uint8_t*)&volatile_data + n*Block::BODYSIZE, block.body.data, getSizeofDataBlock(n));
            }
        }

        void removeFromStorage(){

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
}