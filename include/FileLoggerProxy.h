#pragma once

#include "GetCurDateTimeSingleton.h"
#include "FileLoggerSingleton.h"

class FileLoggerProxy : public FileLoggerSingleton
{
public:
    static FileLoggerProxy& getInstance() {
        static FileLoggerProxy theInstance;
        return theInstance;
    }

    void OpenLogFile(const std::string& FN) override;
    void CloseLogFile() override;
    void WriteToLog(const std::string& str) override;
    void WriteToLog(const std::string& str, int n) override;
    void WriteToLog(const std::string& str, double d) override;
private:
    FileLoggerProxy() {}
    ~FileLoggerProxy() {}
    FileLoggerProxy(const FileLoggerProxy& root) = delete;
    FileLoggerProxy& operator=(const FileLoggerProxy&) = delete;
    FileLoggerProxy(FileLoggerProxy&& root) = delete;
    FileLoggerProxy& operator=(FileLoggerProxy&&) = delete;
};


