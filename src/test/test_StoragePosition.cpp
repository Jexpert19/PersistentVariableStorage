#include "gtest/gtest.h"
#include "Persistent/Position.hpp"
#include "dummy_EEPROM.hpp"

#define BLOCK_SIZE 16

uint16_t readPositionFromSentienlPattern(std::array<bool, 4> arr);

TEST(PersistentStoragePosition, initalizeFromEEPROM){
    ASSERT_EQ(48, readPositionFromSentienlPattern({0,0,0,0}));
    ASSERT_EQ(0,  readPositionFromSentienlPattern({1,0,0,0}));
    ASSERT_EQ(16, readPositionFromSentienlPattern({1,1,0,0}));
    ASSERT_EQ(32, readPositionFromSentienlPattern({1,1,1,0}));
    ASSERT_EQ(48, readPositionFromSentienlPattern({1,1,1,1}));
    ASSERT_EQ(0,  readPositionFromSentienlPattern({0,1,1,1}));
    ASSERT_EQ(16, readPositionFromSentienlPattern({0,0,1,1}));
    ASSERT_EQ(32, readPositionFromSentienlPattern({0,0,0,1}));
}

uint16_t getPositionFromDummy(DummyEEPROM<64>& eeprom);

uint16_t readPositionFromSentienlPattern(std::array<bool, 4> arr){
    DummyEEPROM<64> dummy{};
    uint16_t address = 0;
    
    for(auto sentinel : arr){
        Persistent::Block::Head head{.sentinel=sentinel, .overwritable=0, .checksum=0, .key=0};
        dummy.write(&head, address, sizeof(Persistent::Block::Head));

        address += BLOCK_SIZE;
    }

    return getPositionFromDummy(dummy);
}

uint16_t getPositionFromDummy(DummyEEPROM<64>& eeprom){
    Persistent::Position position{&eeprom};

    return position.getReadPosition();
}