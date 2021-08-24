#include "gtest/gtest.h"
#include "PersistentStorage/PersistentStorage.hpp"
#include "DummyEEPROM.hpp"

TEST(persistentStorage, write){
    DummyEEPROM<64> dummy{};
    PersistentStorage::PersistentStorage<16> storage{&dummy};
    storage.initalize();


    //storage.write(35);

    //storage.read();
}