#include "gtest/gtest.h"
#include "Persistent/CircularBlockIterator.hpp"
#include "DummyEEPROM.hpp"

TEST(CircularBlockIterator, increase){
    DummyEEPROM<64> dummyStorage{};
    Persistent::CircularBlockIterator it{dummyStorage};

    it.toNextBlock();

    ASSERT_EQ(16, it.getAddress());
}

TEST(CircularBlockIterator, increaseAtEnd){
    DummyEEPROM<64> dummyStorage{};
    Persistent::CircularBlockIterator it{dummyStorage, 48};

    it.toNextBlock();

    ASSERT_EQ(0, it.getAddress());
}


TEST(CircularBlockIterator, decrease){
    DummyEEPROM<64> dummyStorage{};
    Persistent::CircularBlockIterator it{dummyStorage, 32};

    it.toPreviousBlock();

    ASSERT_EQ(16, it.getAddress());
}


TEST(CircularBlockIterator, decreaseAtBegin){
    DummyEEPROM<64> dummyStorage{};
    Persistent::CircularBlockIterator it{dummyStorage, 0};

    it.toPreviousBlock();

    ASSERT_EQ(48, it.getAddress());
}