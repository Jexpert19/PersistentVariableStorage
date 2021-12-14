/*#include "gtest/gtest.h"
#include "Persistent/VariableStorage.hpp"
#include "DummyEEPROM.hpp"

TEST(variable, write){
    DummyEEPROM<64> dummy{};
    Persistent::VariableStorage storage{&dummy};

    struct Big{
        char data[32];
    };
    Big big{"Hello World, I'm a big struct!"};
    auto persistentBig = storage.makeVariable<Big>();
    persistentBig.write(big);

    auto persistentInt = storage.makeVariable<int>();
    persistentInt.write(35);

    auto resBig = persistentBig.read();
    ASSERT_STREQ(big.data, resBig.data);

    auto resInt = persistentInt.read();
    ASSERT_EQ(35, resInt);
}*/