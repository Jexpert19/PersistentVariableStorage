#include "gtest/gtest.h"
#include "PersistentStorage/PersistentStoragePosition.hpp"
#include "DummyEEPROM.hpp"

#define BLOCK_SIZE 16

persistentAddress_t PositionFromSentienlPattern(std::array<bool, 4> arr);

TEST(PersistentStoragePosition, initalizeFromEEPROM){
    ASSERT_EQ(48, PositionFromSentienlPattern({0,0,0,0}));
    ASSERT_EQ(0,  PositionFromSentienlPattern({1,0,0,0}));
    ASSERT_EQ(16, PositionFromSentienlPattern({1,1,0,0}));
    ASSERT_EQ(32, PositionFromSentienlPattern({1,1,1,0}));
    ASSERT_EQ(48, PositionFromSentienlPattern({1,1,1,1}));
    ASSERT_EQ(0,  PositionFromSentienlPattern({0,1,1,1}));
    ASSERT_EQ(16, PositionFromSentienlPattern({0,0,1,1}));
    ASSERT_EQ(32, PositionFromSentienlPattern({0,0,0,1}));
}

persistentAddress_t getPositionFromDummy(DummyEEPROM<64>& eeprom);

persistentAddress_t PositionFromSentienlPattern(std::array<bool, 4> arr){
    DummyEEPROM<64> dummy{};
    persistentAddress_t address = 0;
    
    for(auto sentinel : arr){
        PersistentStorage::PersistentBlockHead head{.sentinel=sentinel, .overwritable=0, .key=0, .checksum=0};
        dummy.write(&head, address, sizeof(PersistentStorage::PersistentBlockHead));

        address += BLOCK_SIZE;
    }

    return getPositionFromDummy(dummy);
}

persistentAddress_t getPositionFromDummy(DummyEEPROM<64>& eeprom){
    PersistentStorage::PersistentStorageBase<BLOCK_SIZE> base{&eeprom};
    PersistentStorage::PersistentStoragePosition<BLOCK_SIZE> position{&base};

    position.initalizeFromStorage();

    return position.getReadPosition();
}