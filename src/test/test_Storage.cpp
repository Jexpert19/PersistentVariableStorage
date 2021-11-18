#include "gtest/gtest.h"
#include "Persistent/VariableStorage.hpp"
#include "dummy_EEPROM.hpp"

TEST(persistentStorage, write){
    DummyEEPROM<64> dummy{};
    Persistent::Storage storage{&dummy};

    Persistent::Block test_block{
        .head={},
        .body={
            .data={175}
        }
    };

    storage.write(45, test_block);

    Persistent::Block res_block{};

    storage.read(45, res_block);

    ASSERT_EQ(175, res_block.body.data[0]);
}