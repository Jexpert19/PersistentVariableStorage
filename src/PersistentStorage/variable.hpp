#include <stdint.h>
#include <stdlib.h>
#include "PersistentStorage.hpp"

#include <string.h>

namespace PersistentStorage{
    template<typename T>
    class UniquePersistentVariable{
        public:
        UniquePersistentVariable()
        :KEY{nextKey++}{}
        
        public:
        const uint8_t KEY;
        T value;

        private:
        inline static uint8_t nextKey = 0;
    };

    template<typename T, size_t T_BLOCK_SIZE>
    class PersistentVariable{
        private:
        PersistentStorage<T_BLOCK_SIZE> *storage;
        bool AUTOMATIC_SYNCHONIZATION;
        UniquePersistentVariable<T> variable;

        public:
        PersistentVariable(PersistentStorage<T_BLOCK_SIZE> *persistentStorage, bool AUTOMATIC_SYNCHONIZATION = true)
        :storage{persistentStorage}, AUTOMATIC_SYNCHONIZATION{AUTOMATIC_SYNCHONIZATION}{ }

        void write(const T& value) override{
            variable.value = value;

            if(AUTOMATIC_SYNCHONIZATION){
                writeToPersistentStorage();
            }
        }

        T& read() const override{
            return variable.value;
        }

        void writeToPersistentStorage() const override{
            writeToPersistentStorage(variable.KEY, variable.value);
        }

        void getFromPersistentStorage() override{
            variable.value = getFromPersistentStorage(variable.KEY);
        }

        private:

        void writeToPersistentStorage(const uint8_t KEY, T& value){
            PersistentBlock<T_BLOCK_SIZE> block{};
            memcpy(block.body, &value, sizeof(T));
            storage->write(KEY, block);
        }

        T getFromPersistentStorage(const uint8_t KEY){
            PersistentBlock<T_BLOCK_SIZE> block{};
            storage->read(KEY, block);
            T var{};
            memcpy(&var, block.body, sizeof(T));
            return var;
        }
    };

    template<typename T, size_t T_BLOCK_SIZE, size_t T_SIZE>
    class PersistentArray{
        private:
        PersistentStorage<T_BLOCK_SIZE> *storage;
        bool AUTOMATIC_SYNCHONIZATION;
        UniquePersistentVariable<T> variables[T_SIZE];

        public:

        PersistentArray(PersistentStorage<T_BLOCK_SIZE> *persistentStorage, bool AUTOMATIC_SYNCHONIZATION = true)
        :storage{persistentStorage}, AUTOMATIC_SYNCHONIZATION{AUTOMATIC_SYNCHONIZATION}{ }

        void write(const T& value, const size_t INDEX) override{
            variables[INDEX].value = value;

            if(AUTOMATIC_SYNCHONIZATION){
                writeToPersistentStorage();
            }
        }

        T& read(const size_t INDEX) const override{
            return variables[INDEX].value;
        }

        void writeToPersistentStorage(const size_t INDEX) const override{
            writeToPersistentStorage(variables[INDEX].KEY, variables[INDEX].value);
        }

        void getFromPersistentStorage(const size_t INDEX) override{
            variables[INDEX].value = getFromPersistentStorage(variables[INDEX].KEY);
        }
        
        private:

        void writeToPersistentStorage(const uint8_t KEY, T& value){
            PersistentBlock<T_BLOCK_SIZE> block{};
            memcpy(block.body, &value, sizeof(T));
            storage->write(KEY, block);
        }

        T getFromPersistentStorage(const uint8_t KEY){
            PersistentBlock<T_BLOCK_SIZE> block{};
            storage->read(KEY, block);
            T var{};
            memcpy(&var, block.body, sizeof(T));
            return var;
        }
    };
}