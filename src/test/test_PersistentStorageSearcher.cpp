#include "gtest/gtest.h"
#include "DummyEEPROM.hpp"
#include "PersistentStoragePosition.hpp"
#include "PersistentStorage/PersistentStorageSearcher.hpp"
#include <array>

#include <iostream>
using namespace std;

#define DUMMY_EEPROM_SIZE 64
#define DUMMY_EEPROM_BLOCK_SIZE 16
#define DUMMY_EEPROM_BLOCKS DUMMY_EEPROM_SIZE / DUMMY_EEPROM_BLOCK_SIZE

void prepareDummy(DummyEEPROM<DUMMY_EEPROM_SIZE>& dummy, std::array<PersistentStorage::PersistentBlockHead, DUMMY_EEPROM_BLOCKS> heads);
persistentAddress_t testFindLatestFrom(DummyEEPROM<DUMMY_EEPROM_SIZE>& dummy, PersistentStorage::PersistentBlockHead head);

TEST(PersistentStorageSearcher, findLatest){
    DummyEEPROM<DUMMY_EEPROM_SIZE> dummy{};

    prepareDummy(dummy, {{{0,0,13,0}, {0,0,14,0}}});
    ASSERT_EQ(16, testFindLatestFrom(dummy, {0,0,14,0}));

    prepareDummy(dummy, {{{1,0,14,0}, {0,0,14,0}}});
    ASSERT_EQ(0, testFindLatestFrom(dummy, {0,0,14,0}));

    prepareDummy(dummy, {{{1,0,14,0}, {1,0,14,0}}});
    ASSERT_EQ(16, testFindLatestFrom(dummy, {0,0,14,0}));
}

void prepareDummy(DummyEEPROM<DUMMY_EEPROM_SIZE>& dummy, std::array<PersistentStorage::PersistentBlockHead, DUMMY_EEPROM_BLOCKS> heads){
    persistentAddress_t addr = 0;
    for(auto e : heads){
        dummy.write(&e, addr, sizeof(e));
        addr += DUMMY_EEPROM_BLOCK_SIZE;
    }
}

persistentAddress_t testFindLatestFrom(DummyEEPROM<DUMMY_EEPROM_SIZE>& dummy, PersistentStorage::PersistentBlockHead head){
    PersistentStorage::PersistentStorageBase<16> base{&dummy};
    PersistentStorage::PersistentStoragePosition<16> position{&base};
    position.initalizeFromStorage();
    PersistentStorage::PersistentStorageSearcher<16> searcher{&base, &position};

    persistentAddress_t result;
    if(searcher.findLatest(&head, &result) != PersistentStorage::Error::ok){
        persistentAddress_t error = 0;
        return error;
    }

    return result;
}