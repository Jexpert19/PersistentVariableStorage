#pragma once/*
#include <stdint.h>
#include <ostream>
#include "Variable.hpp"

namespace Log{
  struct LogEntry{
    uint32_t eventTimeStamp;
    uint8_t level;
    uint8_t msgId;
    uint8_t additionalData[];// ????
  };


  class LogableVariable : public Variable<LogEntry>{

  };

  class Log{
    public:

    enum class LogLevel{
      error,
      warning,
      info,
      debug
    };

    void write(LogLevel logLevel, const char* msgId, uint8_t* additionalData = nullptr){

    }

    void printLog(){

    }
  };
}*/