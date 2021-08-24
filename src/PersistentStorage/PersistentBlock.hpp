#pragma once
#include <stdint.h>
#include <stdlib.h>

namespace PersistentStorage{
    struct PersistentBlockHead{
        // Flag to find current reading pos.
        bool sentinel :1;

        // Indicates that this block can be overwritten
        bool overwritable :1;

        uint8_t key :8;
   
        // Not used right now
        uint8_t checksum :6;
    };

    template<size_t T_SIZE>
    struct PersistentBlockBody{
        uint8_t data[T_SIZE];
    };

    template<size_t T_SIZE>
    struct PersistentBlock{
        PersistentBlockHead head;
        PersistentBlockBody<T_SIZE> body;
    };
}