#include "dummy_BlockStorage.hpp"

const uint8_t EEPROM_INIT_VALUE = 0xFF;

uint8_t dummyStorage[DUMMY_STORAGE_SIZE];

void dummyReadMemory(void* data_out, uint16_t address, size_t size) {
  memcpy(data_out, &dummyStorage[address], size);
}

void dummyWriteMemory(const void* data_in, uint16_t address, size_t size) {
  memcpy(&dummyStorage[address], data_in, size);
}

Persistent::BlockStorage getDummyBlockStorage(){
  memset(&dummyStorage, EEPROM_INIT_VALUE, sizeof(dummyStorage));

  return Persistent::BlockStorage{DUMMY_STORAGE_SIZE, dummyReadMemory, dummyWriteMemory};
}