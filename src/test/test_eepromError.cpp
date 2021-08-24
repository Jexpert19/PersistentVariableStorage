#include "gtest/gtest.h"
#include "PersistentStorage/error.hpp"

TEST(eepromError, eepromErrorToPstr){
    EXPECT_STREQ("", PersistentStorage::eepromErrorToPstr(PersistentStorage::Error::ok));
    EXPECT_STREQ("Not found", PersistentStorage::eepromErrorToPstr(PersistentStorage::Error::not_found));
    EXPECT_STREQ("Corrupted", PersistentStorage::eepromErrorToPstr(PersistentStorage::Error::corrupted));
}