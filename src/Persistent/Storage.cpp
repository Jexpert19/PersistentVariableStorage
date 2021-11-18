#include "Storage.hpp"
#include <string.h>

namespace Persistent{
    Error Storage::read(const uint8_t KEY, Block &data){
        Block::Head target_head{.sentinel=0, .overwritable=0, .checksum=0, .key=KEY}, head;
        uint16_t target_address;

        Error e = searcher.findLatest(&target_head, &target_address);
        if(e != Error::ok){
            return e;
        }

        storageBase->read(&head, target_address, Block::HEADSIZE);
        if(head.overwritable == true){
            return Error::not_found;
        }

        storageBase->read(&data, target_address, sizeof(Block));

        return Error::ok;
    }

    Error Storage::write(const uint8_t KEY, Block &data){
        data.head.key=KEY;
        
        writer.writeToNextWritableBlock(data);

        return Error::ok;
    }

    void Storage::remove(const uint8_t KEY){
        Block block = {
            .head={
            .sentinel=0,
            .overwritable=true,
            .checksum=0,
            .key=KEY
        },
        .body={
            .data={0}
            }
        };
        writer.writeToNextWritableBlock(block);
    }

    void Storage::complete_format(){
        const uint8_t eeprom_format_value = 0xFF;

        uint8_t formated_block[sizeof(Block)];
        memset(formated_block, eeprom_format_value, sizeof(formated_block));

        for(uint16_t address = 0; address < storageBase->blocksCount(); address += sizeof(Block)){
            storageBase->write(formated_block, address, sizeof(formated_block));
        }
    }
}