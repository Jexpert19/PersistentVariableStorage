#include "gtest/gtest.h"
#include "Persistent/Error.hpp"

TEST(eepromError, eepromErrorToPstr){
  EXPECT_STREQ("", Persistent::eepromErrorToPstr(Persistent::Error::ok));
  EXPECT_STREQ("Not found", Persistent::eepromErrorToPstr(Persistent::Error::not_found));
  EXPECT_STREQ("Corrupted", Persistent::eepromErrorToPstr(Persistent::Error::corrupted));
}