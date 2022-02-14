#include "gtest/gtest.h"
#include "Persistent/CircularIterator.hpp"

/*
TEST(CircularIterator, increase){
  DummyEEPROM<64> dummyStorage{};
  Persistent::CircularIterator it{Persistent::CircularBlockIterator(dummyStorage)};

  it.toNextBlock();

  ASSERT_EQ(16, it.getAddress());
}*/