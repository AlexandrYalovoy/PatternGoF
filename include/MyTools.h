#pragma once

#include <string>

namespace MyTools {

void OpenLogFile(const std::string& FN);

void CloseLogFile();

void WriteToLog(const std::string& str);

void WriteToLog(const std::string& str, int n);

void WriteToLog(const std::string& str, double d);

}; // namespace MyTools
