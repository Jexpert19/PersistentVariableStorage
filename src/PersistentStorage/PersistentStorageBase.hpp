#pragma once
#include <stdlib.h>
#include "PersistentStorageInterface.hpp"
#include "PersistentBlock.hpp"
#include "address.hpp"
#include "error.hpp"

namespace PersistentStorage{
    typedef void (*persistentStorageRead_t)(void* data_out, persistentAddress_t address, size_t __n);
    typedef void (*persistentStorageWrite_t)(const void* data_in, persistentAddress_t address, size_t __n);

    template<size_t T_BLOCK_SIZE>
    class PersistentStorageBase{
        private:
        PersistentStorageInterface *storage;

        public:
        const size_t EEPROM_SIZE;
        const size_t BLOCK_SIZE = T_BLOCK_SIZE;
        const size_t BLOCK_HEAD_SIZE = sizeof(struct PersistentBlockHead);
        const size_t BLOCK_BODY_SIZE = BLOCK_SIZE - BLOCK_HEAD_SIZE;
        const uint16_t BLOCKS_COUNT = EEPROM_SIZE / BLOCK_SIZE;
        const persistentAddress_t FIRST_BLOCK = 0;
        const persistentAddress_t LAST_BLOCK = EEPROM_SIZE - BLOCK_SIZE;

        // Sizes must be a power of 2
        PersistentStorageBase(PersistentStorageInterface *storage)
        :storage{storage}, EEPROM_SIZE{storage->SIZE}{
            //storage->init();
        }

        void getHead(persistentAddress_t address, PersistentBlockHead& head){
            storage->read(&head, address, BLOCK_HEAD_SIZE);
        }

        void getBody(persistentAddress_t address, PersistentBlockBody<T_BLOCK_SIZE>& body){
            storage->read(&body, address + BLOCK_HEAD_SIZE, BLOCK_BODY_SIZE);
        }

        void getBlock(persistentAddress_t address, PersistentBlock<T_BLOCK_SIZE>& block){
            storage->read(&block, address, BLOCK_SIZE);
        }

        void writeHead(persistentAddress_t address, PersistentBlockHead& head){
            storage->write(&head, address, BLOCK_HEAD_SIZE);
        }

        void writeBody(persistentAddress_t address, PersistentBlockBody<T_BLOCK_SIZE>& body){
            storage->write(&body, address, BLOCK_BODY_SIZE);
        }

        void writeBlock(persistentAddress_t address, PersistentBlock<T_BLOCK_SIZE>& block){
            storage->write(&block, address, BLOCK_SIZE);
        }
    };
}