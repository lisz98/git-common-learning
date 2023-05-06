#include "timestamp.h"
#include <inttypes.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace SZ;

TimeStamp::TimeStamp(int64_t microSeconds)
    :time_since_epoch_(microSeconds)
{

}

std::string TimeStamp::toString(const std::string &format) const
{
    const struct std::tm *tm = std::localtime(&time_since_epoch_);
    if(tm){
        return (std::stringstream()<< std::put_time(tm,format.data())).str();
    }
    return std::string();
}

bool TimeStamp::before(const TimeStamp &t)
{
    return toUTC() < t.toUTC();
}
bool TimeStamp::after(const TimeStamp &t)
{
    return toUTC() > t.toUTC();
}
bool TimeStamp::equals(const TimeStamp &t)
{
    return toUTC() == t.toUTC();
}

TimeStamp TimeStamp::now()
{
    return std::move(TimeStamp(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())));
}