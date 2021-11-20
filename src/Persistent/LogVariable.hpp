#pragma once
#include <stdint.h>
#include "Variable.hpp"

namespace Log{
    struct LogEntry{
        uint32_t eventTimeStamp;
        uint8_t level;
        uint8_t msgId;
        uint8_t additionalData[];// ????
    };

    
    class LogVariable : public Variable{

        public:

        enum class LogLevel{
            error,
            warning,
            info,
            debug
        };

        void write(LogLevel logLevel, const char* msgId, uint8_t* additionalData = nullptr){

        }

        Iterator readLog();
    };

    class Log{

        public:
        void printLog(){

        }
    };
}


