#ifndef  __SZ_BASE_TIMESTAMP__H__
#define __SZ_BASE_TIMESTAMP__H__

#include <stdint.h>
#include <string>

namespace SZ
{

/**
 * @brief 时间戳类 ，使用UTC 标准
 * 
 * UTC（Coodinated Universal Time），协调世界时，又称世界统一时间、世界标准时间、国际协调时间。
 * 由于英文（CUT）和法文（TUC）的缩写不同，作为妥协，简称UTC。
 */

class TimeStamp
{
public:
    //毫秒转换成分的系数
    static const int microSecondsPerSeconds = 1000 * 1000 ;

    explicit TimeStamp(int64_t microSeconds);

    std::string toString(const std::string &format = "%Y-%m-%d %H:%M:%S") const; 
    int64_t toUTC() const { return time_since_epoch_; }

    bool before(const TimeStamp &t);
    bool after(const TimeStamp &t);
    bool equals(const TimeStamp &t);

    bool valid() const { return time_since_epoch_ > 0; }

    static TimeStamp now();
    
private:
    int64_t time_since_epoch_;
};

inline bool operator<(TimeStamp t1,TimeStamp t2)
{
    return t1.before(t2);
}

inline bool operator==(TimeStamp t1,TimeStamp t2)
{
    return t1.equals(t2);
}

};

#endif