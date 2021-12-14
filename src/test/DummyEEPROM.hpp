#pragma once
#include <string.h>
#include "Persistent/StorageAdapter.hpp"

template<size_t T_SIZE>
class DummyEEPROM : public Persistent::StorageAdapter{
    private:
    const uint8_t EEPROM_INIT_VALUE = 0xFF;

    public:
    uint8_t dummyStorage[T_SIZE];

    DummyEEPROM()
    :StorageAdapter{T_SIZE}{
        memset(&dummyStorage, EEPROM_INIT_VALUE, sizeof(dummyStorage));
    }

    void readMemory(void* data_out, uint16_t address, size_t size) override{
        memcpy(data_out, &dummyStorage[address], size);
    }

    void writeMemory(const void* data_in, uint16_t address, size_t size) override{
        memcpy(&dummyStorage[address], data_in, size);
    }
};