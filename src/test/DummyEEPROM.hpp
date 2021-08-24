#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "PersistentStorage/PersistentStorageInterface.hpp"

template<size_t T_SIZE>
class DummyEEPROM : public PersistentStorage::PersistentStorageInterface{
    private:
    const uint8_t EEPROM_INIT_VALUE = 0xFF;

    public:
    uint8_t dummyStorage[T_SIZE];

    DummyEEPROM()
    :PersistentStorageInterface{T_SIZE} { }

    void init() override{
        memset(&dummyStorage, EEPROM_INIT_VALUE, sizeof(dummyStorage));
    }

    void read(void* data_out, uint16_t address, size_t size) override{
        memcpy(data_out, &dummyStorage[address], size);
    }

    void write(const void* data_in, uint16_t address, size_t size) override{
        memcpy(&dummyStorage[address], data_in, size);
    }
};