#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include "address.hpp"
#include "BlockPointer.hpp"
#include "error.hpp"
#include "PersistentBlock.hpp"
#include "PersistentStorageBase.hpp"
#include "PersistentStorageInterface.hpp"
#include "PersistentStoragePosition.hpp"
#include "PersistentStorageSearcher.hpp"
#include "PersistentStorageWriter.hpp"
#include "variable.hpp"

// the basic algorithm:
// https://sites.google.com/site/dannychouinard/Home/atmel-avr-stuff/eeprom-longevity

namespace PersistentStorage{
    template<size_t BLOCK_SIZE>
    class PersistentStorage{
        private:
        PersistentStorageBase<BLOCK_SIZE> storageBase;
        PersistentStoragePosition<BLOCK_SIZE> position{&storageBase};
        PersistentStorageSearcher<BLOCK_SIZE> searcher{&storageBase, &position};
        PersistentStorageWriter<BLOCK_SIZE> blockWrite{&storageBase, &position, &searcher};

        public:
        PersistentStorage(PersistentStorageInterface *storage)
        :storageBase{storage}{
            storage->init();
        }

        void initalize(){
            position.initalizeFromStorage();
        }



        Error read(const uint8_t KEY, PersistentBlock<BLOCK_SIZE> &data){
            PersistentBlockBody<BLOCK_SIZE> body;
            PersistentBlockHead target_head{.sentinel=0, .overwritable=0, .KEY=KEY, .checksum=0}, head;
            persistentAddress_t target_address;

            Error e =    searcher.findLatest(&target_head, &target_address);
            if(e != Error::ok){
                return e;
            }

            storageBase.get_head(target_address, &head);
            if(head.overwritable == true){
                return Error::not_found;
            }

            storageBase.getBlock(target_address, &data);

            return Error::ok;
        }

        Error write(const uint8_t KEY, PersistentBlock<BLOCK_SIZE> &data){
            blockWrite.write_to_next_writable_block(data);

            return Error::ok;
        }

        void remove(const uint8_t KEY){
            PersistentBlock<BLOCK_SIZE> block = {
                .head={
                .sentinel=0,
                .overwritable=true,
                .KEY=KEY,
                .checksum=0
            },
            .body={0}
            };
            blockWrite.write_to_next_writable_block(&block);
        }

        void complete_format(){
            const uint8_t eeprom_format_value = 0xFF;

            uint8_t formated_block[storageBase.BLOCK_SIZE];
            memset(formated_block, eeprom_format_value, sizeof(formated_block));

            for(persistentAddress_t address = 0; address < storageBase.BLOCKS_COUNT; address += storageBase.BLOCK_SIZE){
                storageBase.eeprom_write(formated_block, address, sizeof(formated_block));
            }
        }
    };
}