#pragma once
#include <stdint.h>

struct LogEntry{
    uint32_t eventTimeStamp;
    uint8_t level;
    uint8_t msgId;
    uint8_t additionalData;// ????
};


class LogVariable{
    enum class LogLevel{
        error,
        warning,
        info,
        debug
    };


    void write(LogEntry logEntry){

    }

    iterator readLog();
};