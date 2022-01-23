#ifndef SBOMBER_TESTFILELOGGER_H
#define SBOMBER_TESTFILELOGGER_H

#include "FileLoggerSingleton.h"

class TestFileLogger : public FileLoggerSingleton {
public:
    static TestFileLogger& getInstance() {
        static TestFileLogger theInstance;
        return theInstance;
    }
    void OpenLogFile(const std::string& FN) override;
    void CloseLogFile() override;
    void WriteToLog(const std::string& str) override;
    void WriteToLog(const std::string& str, int n) override;
    void WriteToLog(const std::string& str, double d) override;
private:
    TestFileLogger() = default;
    ~TestFileLogger() = default;
    TestFileLogger(const TestFileLogger& root) = delete;
    TestFileLogger& operator=(const TestFileLogger&) = delete;
    TestFileLogger(TestFileLogger&& root) = delete;
    TestFileLogger& operator=(TestFileLogger&&) = delete;
};


#endif //SBOMBER_TESTFILELOGGER_H
