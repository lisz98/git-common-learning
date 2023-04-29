#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

/*
    timed_mutex 类是能用于保护数据免受多个线程同时访问的同步原语
    以类似 mutex 的行为， timed_mutex 提供排他性非递归所有权语义
*/

std::timed_mutex mutex;

void test_timeout()
{
    std::lock_guard<std::timed_mutex> lock(mutex);
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void test_timed_mutex()
{
    std::this_thread::sleep_for(std::chrono::microseconds(300));

#if 0
    //失败情况
    if(!mutex.try_lock_for(std::chrono::seconds(2))){
        std::cout << "error ! mutex try_lock_for 2 seconds over...";
    }
#else
    if(mutex.try_lock_for(std::chrono::seconds(4))){
        std::cout << "mutex try_lock_for s!";
    }
#endif
    mutex.unlock();
}

int main()
{
    std::thread t1(test_timed_mutex);
    std::thread t2(test_timeout);

    t1.join();
    t2.join();
    return 0;
}