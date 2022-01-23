#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <numeric>
#include <ctime>
#include <cstring>


class GetCurDateTimeSingleton {
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;
public:
    static GetCurDateTimeSingleton& getInstance() {
        static GetCurDateTimeSingleton theInstance;
        return theInstance;
    }

    std::string GetCurDateTime();
    void Start();
    void SaveTime();
    double Calculating();
private:
    GetCurDateTimeSingleton() {}
    GetCurDateTimeSingleton(const GetCurDateTimeSingleton& root) = delete;
    GetCurDateTimeSingleton& operator=(const GetCurDateTimeSingleton&) = delete;
private:
    std::chrono::time_point<clock_t> m_beg;
    std::vector<double> storage_time;
};


