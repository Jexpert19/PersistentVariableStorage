#include "gtest/gtest.h"
#include "dummy_BlockStorage.hpp"

TEST(BlockStorage, iteratorIncrease){
  Persistent::BlockStorage dummyStorage = getDummyBlockStorage();
  Persistent::BlockStorageObject::ConstIterator it{dummyStorage};

  ++it;

  ASSERT_EQ(16, it.getAddress());
}

TEST(BlockStorage, iteratorIncreaseAtEnd){
  Persistent::BlockStorage dummyStorage = getDummyBlockStorage();
  Persistent::BlockStorageObject::ConstIterator it{dummyStorage, 48};

  ++it();

  ASSERT_EQ(0, it.getAddress());
}


TEST(BlockStorage, iteratorDecrease){
  Persistent::BlockStorage dummyStorage = getDummyBlockStorage();
  Persistent::BlockStorageObject::ConstIterator it{dummyStorage, 32};

  --it();

  ASSERT_EQ(16, it.getAddress());
}


TEST(BlockStorage, iteratorDecreaseAtBegin){
  Persistent::BlockStorage dummyStorage = getDummyBlockStorage();
  Persistent::BlockStorageObject::ConstIterator it{dummyStorage, 0};

  --it;

  ASSERT_EQ(48, it.getAddress());
}

TEST(BlockStorage, writeRead){
  Persistent::BlockStorage dummyStorage = getDummyBlockStorage();
  Persistent::BlockStorageObject::Iterator it{dummyStorage, 0};

  Persistent::Block test_data{};

  

  auto res = it.getBlock();

  //ASSERT_EQ(48, res);
}