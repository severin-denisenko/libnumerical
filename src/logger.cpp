//
// Created by Severin on 15.09.2022.
//

#include "logger.h"

namespace numerical{
    void Logger::Log(numerical::Logger::LoggerLevel level, const std::string &message) {
        std::string LogLevelStrings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]:  ", "[INFO]:  "};

        if(level == 0 || level == 1){
            std::cerr << LogLevelStrings[level] << message << std::endl;
        } else {
            std::cout << LogLevelStrings[level] << message << std::endl;
        }

        if (level == 0){
            exit(1);
        }
    }
}

