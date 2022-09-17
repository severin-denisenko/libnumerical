//
// Created by Severin on 15.09.2022.
//

#ifndef LIBNUMERICAL_LOGGER_H
#define LIBNUMERICAL_LOGGER_H

#include <string>
#include <iostream>

#if DEBUG_BUILD == 1
    #define LOG_LEVEL_WARNING_ENABLED 1
    #define LOG_LEVEL_INFO_ENABLED 1
#endif

#define FATAL(message) numerical::Logger::Log(numerical::Logger::LOG_LEVEL_FATAL, message);
#define ERROR(message) numerical::Logger::Log(numerical::Logger::LOG_LEVEL_ERROR, message);

#if LOG_LEVEL_INFO_ENABLED == 1
#define INFO(message) numerical::Logger::Log(numerical::Logger::LOG_LEVEL_INFO, message);
#else
#define INFO(message)
#endif

#if LOG_LEVEL_WARNING_ENABLED == 1
#define WARNING(message) numerical::Logger::Log(numerical::Logger::LOG_LEVEL_WARNING, message);
#else
#define WARNING(message)
#endif

namespace numerical{
    class Logger{
    public:
        enum LoggerLevels{
            LOG_LEVEL_FATAL = 0,
            LOG_LEVEL_ERROR = 1,
            LOG_LEVEL_WARNING = 2,
            LOG_LEVEL_INFO = 3
        };

        typedef LoggerLevels LoggerLevel;

        static void Log(LoggerLevel level, const std::string& message);
    };
}

#endif //LIBNUMERICAL_LOGGER_H
