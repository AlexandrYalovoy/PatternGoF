#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "GetCurDateTimeSingleton.h"
#include "Bomb.h"

class FileLoggerSingleton {
public:
    static FileLoggerSingleton& getInstance() {
        static FileLoggerSingleton theInstance;
        return theInstance;
    }

    virtual void OpenLogFile(const std::string& FN);
    virtual void CloseLogFile();
    virtual void WriteToLog(const std::string& str);
    virtual void WriteToLog(const std::string& str, int n);
    virtual void WriteToLog(const std::string& str, double d);
protected:
    std::ofstream logOut;
protected:
    FileLoggerSingleton() {}
    ~FileLoggerSingleton() {}
    FileLoggerSingleton(const FileLoggerSingleton& root) = delete;
    FileLoggerSingleton& operator=(const FileLoggerSingleton&) = delete;
    FileLoggerSingleton(FileLoggerSingleton&& root) = delete;
    FileLoggerSingleton& operator=(FileLoggerSingleton&&) = delete;
};



