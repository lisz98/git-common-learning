/*
函数模板 std::async 异步地运行函数 f（有可能在可能是线程池一部分的分离线程中），并返回最终将保有该函数调用结果的 std::future。

std::launch::async	运行新线程，以异步执行任务
std::launch::deferred	调用方线程上首次请求其结果时执行任务（惰性求值）


*/

#include <future>
#include <iostream>
#include <mutex>
#include <numeric>
#include <string>
#include <vector>

std::mutex m;

struct X
{
    void foo(int i, const std::string& str)
    {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << ' ' << i << '\n';
    }
 
    void bar(const std::string& str)
    {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << '\n';
    }
 
    int operator()(int i)
    {
        std::lock_guard<std::mutex> lk(m);
        std::cout << i << '\n';
        return i + 10;
    }
};

template<typename RandomIt>
int parallel_sum(RandomIt beg,RandomIt end)
{
    auto len = end - beg;
    if(len < 1000){
        return std::accumulate(beg,end,0);
    }

    RandomIt mid = beg + len /2 ;
    auto handle = std::async(std::launch::async,
            parallel_sum<RandomIt>,mid,end);
    
    int sum = parallel_sum(beg,mid);
    return sum + handle.get();
}

int main()
{
    std::vector<int> v(10000, 1);
    std::cout << "和为 " << parallel_sum(v.begin(), v.end()) << '\n';
 
    X x;
    // 以默认策略调用 x.foo(42, "Hello") ：
    // 可能同时打印 "Hello 42" 或延迟执行
    auto a1 = std::async(&X::foo, &x, 42, "Hello");
    // 以 deferred 策略调用 x.bar("world!")
    // 调用 a2.get() 或 a2.wait() 时打印 "world!"
    auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
    // 以 async 策略调用 X()(43) ：
    // 同时打印 "43"
    auto a3 = std::async(std::launch::async, X(), 43);
    a2.wait();                     // 打印 "world!"
    std::cout << a3.get() << '\n'; // 打印 "53"
} // 若 a1 在此点未完成，则 a1 的析构函数在此打印 "Hello 42"