/*#include "gtest/gtest.h"
#include "DummyEEPROM.hpp"
#include "Persistent/Position.hpp"
#include "Persistent/Searcher.hpp"
#include <array>

#include <iostream>
using namespace std;

#define DUMMY_EEPROM_SIZE 64
#define DUMMY_EEPROM_BLOCKS DUMMY_EEPROM_SIZE / Persistent::BLOCKSIZE_BYTES

void prepareDummy(DummyEEPROM<DUMMY_EEPROM_SIZE>& dummy, std::array<Persistent::Block::Head, DUMMY_EEPROM_BLOCKS> heads);
uint16_t testFindLatestFrom(DummyEEPROM<DUMMY_EEPROM_SIZE>& dummy, Persistent::Block::Head head);

TEST(PersistentStorageSearcher, findLatest){
  DummyEEPROM<DUMMY_EEPROM_SIZE> dummy{};

  prepareDummy(dummy, {{{0,0,0,13}, {0,0,0,14}}});
  ASSERT_EQ(16, testFindLatestFrom(dummy, {0,0,0,14}));

  prepareDummy(dummy, {{{1,0,0,14}, {0,0,0,14}}});
  ASSERT_EQ(0, testFindLatestFrom(dummy, {0,0,0,14}));

  prepareDummy(dummy, {{{1,0,0,14}, {1,0,0,14}}});
  ASSERT_EQ(16, testFindLatestFrom(dummy, {0,0,0,14}));
}

void prepareDummy(DummyEEPROM<DUMMY_EEPROM_SIZE>& dummy, std::array<Persistent::Block::Head, DUMMY_EEPROM_BLOCKS> heads){
  uint16_t addr = 0;
  for(auto e : heads){
    dummy.write(&e, addr, sizeof(e));
    addr += Persistent::BLOCKSIZE_BYTES;
  }
}

uint16_t testFindLatestFrom(DummyEEPROM<DUMMY_EEPROM_SIZE>& dummy, Persistent::Block::Head head){
  Persistent::Position position{&dummy};
  Persistent::Searcher searcher{&dummy, &position};

  uint16_t result;
  if(searcher.findLatest(&head, &result) != Persistent::Error::ok){
    uint16_t error = 0;
    return error;
  }

  return result;
}*/