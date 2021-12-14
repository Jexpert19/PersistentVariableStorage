#pragma once/*
#include "Storage.hpp"
#include "UniqueKeyGenerator.hpp"
#include "Variable.hpp"

namespace Persistent{
    class VariableStorage{
        private:
        Storage storage;
        UniqueKeyGenerator keyGenerator{};

        VariableStorage(Base *base):storage{base}{ }

        template<typename T>
        Variable<T> makeVariable(){
            Variable<T> var{keyGenerator, &storage};
            return var;
        }
    };
}*/