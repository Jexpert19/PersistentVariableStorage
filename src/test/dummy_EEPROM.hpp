#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Persistent/Base.hpp"

template<size_t T_SIZE>
class DummyEEPROM : public Persistent::Base{
    private:
    const uint8_t EEPROM_INIT_VALUE = 0xFF;

    public:
    uint8_t dummyStorage[T_SIZE];

    DummyEEPROM()
    :Base{T_SIZE}{
        memset(&dummyStorage, EEPROM_INIT_VALUE, sizeof(dummyStorage));
    }

    void read(void* data_out, uint16_t address, size_t size) override{
        memcpy(data_out, &dummyStorage[address], size);
    }

    void write(const void* data_in, uint16_t address, size_t size) override{
        memcpy(&dummyStorage[address], data_in, size);
    }
};