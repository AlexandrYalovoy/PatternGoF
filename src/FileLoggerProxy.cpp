#include "FileLoggerProxy.h"

void FileLoggerProxy::OpenLogFile(const std::string &FN) {
    FileLoggerSingleton::getInstance().OpenLogFile(FN);
}

void FileLoggerProxy::CloseLogFile() {
    FileLoggerSingleton::getInstance().CloseLogFile();
}

void FileLoggerProxy::WriteToLog(const std::string &str) {
    FileLoggerSingleton::getInstance().WriteToLog(str);
}

void FileLoggerProxy::WriteToLog(const std::string &str, int n) {
    FileLoggerSingleton::getInstance().WriteToLog(str, n);
}

void FileLoggerProxy::WriteToLog(const std::string &str, double d) {
    FileLoggerSingleton::getInstance().WriteToLog(str, d);
}
