#pragma once
#include <stdint.h>
#include <stdlib.h>
#include "LibConfig.hpp"

namespace Persistent{
    struct Block{
        struct Head{
            // Flag to find current reading pos.
            bool sentinel :1;

            // Block will not be found by searcher
            // and could be overwritten if needed
            bool deleted :1;

            bool blockSequenceEnd :1;

            // Not used right now
            uint8_t checksum :5;

            uint8_t key :8;
        }head;

        struct Body{
            uint8_t data[BLOCKSIZE_BYTES - sizeof(head)];
        }body;

        static constexpr size_t HEADSIZE = sizeof(head);
        static constexpr size_t BODYSIZE = sizeof(body);
    };
}