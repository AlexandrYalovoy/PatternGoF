#include "TestFileLogger.h"

void TestFileLogger::OpenLogFile(const std::string &FN) {
    logOut.open(FN, std::ios_base::out);
}

void TestFileLogger::CloseLogFile() {
    if (logOut.is_open())
    {
        logOut.close();
    }
}

void TestFileLogger::WriteToLog(const std::string &str) {
    if (logOut.is_open()) {
        logOut << GetCurDateTimeSingleton::getInstance().GetCurDateTime() <<
               " - " << str << " TestFileLoggerSingleton" << std::endl;
    }
}

void TestFileLogger::WriteToLog(const std::string &str, int n) {
    if (logOut.is_open()) {
        logOut << GetCurDateTimeSingleton::getInstance().GetCurDateTime() <<
               " - " << str << n << " TestFileLoggerSingleton" << std::endl;
    }
}

void TestFileLogger::WriteToLog(const std::string &str, double d) {
    if (logOut.is_open()) {
        logOut << GetCurDateTimeSingleton::getInstance().GetCurDateTime() <<
               " - " << str << d << " TestFileLoggerSingleton" << std::endl;
    }
}

