#include "GetCurDateTimeSingleton.h"

#include <map>

std::string GetCurDateTimeSingleton::GetCurDateTime()
{
    auto cur = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(cur);
    char buf[64] = { 0 };
    ctime_r(&time, buf);
    buf[strlen(buf) - 1] = '\0';
    return std::string(buf);
}

void GetCurDateTimeSingleton::Start()
{
    m_beg = clock_t::now();
}

void GetCurDateTimeSingleton::SaveTime()
{
    storage_time.push_back(std::chrono::duration_cast<second_t>(clock_t::now() -
                                                                m_beg).count());
}

double GetCurDateTimeSingleton::Calculating()
{
    auto res = std::accumulate(storage_time.begin(), storage_time.end(), 0.0);
    return res / storage_time.size();
}