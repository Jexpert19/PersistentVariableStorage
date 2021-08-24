#include "gtest/gtest.h"
#include "PersistentStorage/variable.hpp"
#include "DummyEEPROM.hpp"

TEST(variable, write){
    DummyEEPROM<64> dummy{};
    PersistentStorage::PersistentStorage<16> storage{&dummy};
    storage.initalize();

    //PersistentStorage::PersistentVariable<int, 16> myEEMEMVar{&storage};

    PersistentStorage::UniquePersistentVariable<int> intx{};
    PersistentStorage::UniquePersistentVariable<char> inty{};

    ASSERT_EQ(0, intx.KEY);
    ASSERT_EQ(0, inty.KEY);    
}