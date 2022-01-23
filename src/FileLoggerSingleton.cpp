#include "FileLoggerSingleton.h"
#include "GetCurDateTimeSingleton.h"

void FileLoggerSingleton::OpenLogFile(const std::string& FN)
{
    logOut.open(FN, std::ios_base::out);
}

void FileLoggerSingleton::CloseLogFile()
{
    if (logOut.is_open())
    {
        logOut.close();
    }
}

void FileLoggerSingleton::WriteToLog(const std::string& str)
{
    if (logOut.is_open()) {
        logOut << GetCurDateTimeSingleton::getInstance().GetCurDateTime() <<
               " - " << str << " Singleton" << std::endl;
    }
}

void FileLoggerSingleton::WriteToLog(const std::string& str, int n)
{
    if (logOut.is_open()) {
        logOut << GetCurDateTimeSingleton::getInstance().GetCurDateTime() <<
               " - " << str << n << " Singleton" << std::endl;
    }
}

void FileLoggerSingleton::WriteToLog(const std::string& str, double d)
{
    if (logOut.is_open()) {
        logOut << GetCurDateTimeSingleton::getInstance().GetCurDateTime() <<
               " - " << str << d << " Singleton" << std::endl;
    }
}
