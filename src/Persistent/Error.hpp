#pragma once
extern "C"{
    #include "wrapper/avr/pgmspace.h"
}

namespace Persistent{
    enum class Error{
        ok,
        not_found,
        corrupted
    };

    PGM_P eepromErrorToPstr(Error error);
}