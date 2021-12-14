#pragma once/*
#include <stdlib.h>
#include <stdbool.h>
#include "Version.hpp"
#include "Error.hpp"
#include "Position.hpp"
#include "Searcher.hpp"
#include "Writer.hpp"

// the basic algorithm:
// https://sites.google.com/site/dannychouinard/Home/atmel-avr-stuff/eeprom-longevity

namespace Persistent{
    class Storage : public Base{
        private:
        Position position{*this};
        Searcher searcher{*this, position};
        Writer writer{*this, position, searcher};

        public:
        Storage(Base& base) :Base{base} {}

        template<typename T>
        Error read(const uint8_t KEY, T &data);
        Error write(const uint8_t KEY, Block &data);
        void remove(const uint8_t KEY);

        // What if contents are modified between iterator uses
        Iterator logBegin(); // Pointing to latest element.    both bidirectional??? or just forward
        Iterator logBegin(const uint8_t KEY);
        
        // Pointing behind last element!?
        Iterator logEnd();
        Iterator logEnd(const uint8_t KEY);
        

        //iteratorclass rend(const uint8_t KEY);   // Pointing to oldest element.    rend or end???


        void complete_format();
    };
}*/