/*
类模板 std::shared_future 提供访问异步操作结果的机制，类似 std::future ，除了允许多个线程等候同一共享状态。不同于仅可移动的 std::future （故只有一个实例能指代任何特定的异步结果），std::shared_future 可复制而且多个 shared_future 对象能指代同一共享状态。

若每个线程通过其自身的 shared_future 对象副本访问，则从多个线程访问同一共享状态是安全的
*/

#include <iostream>
#include <future>
#include <chrono>
#include <thread>

int main()
{
    //创建三个void类型存储值，用于当做信号
    std::promise<void> ready_promise,t1_ready_promise,t2_ready_promise;
    std::shared_future<void> ready_future(ready_promise.get_future());

    std::chrono::time_point<std::chrono::high_resolution_clock> start;


    auto func1 = [&,ready_future]() ->std::chrono::duration<double,std::milli>
    {
        t1_ready_promise.set_value(); //发送信号通知 Main 进程，已经准备就绪
        std::cout << "ready curThreadId:" << std::this_thread::get_id() << '\n';
        ready_future.wait();  //等待 main 进程发送的信号, ready_promise.set_value();
        return std::chrono::high_resolution_clock::now() -start;
    };

    auto func2 = [&, ready_future]() -> std::chrono::duration<double, std::milli> 
    {
        t2_ready_promise.set_value();
        std::cout << "ready curThreadId:" << std::this_thread::get_id() << '\n';
        ready_future.wait(); // 等待来自 main() 的信号
        return std::chrono::high_resolution_clock::now() - start;
    };  

    //异步执行 result1 & result2
    auto result1 = std::async(std::launch::async,func1);
    auto result2 = std::async(std::launch::async,func2);

    // 等待线程变为就绪
    t1_ready_promise.get_future().wait();
    t2_ready_promise.get_future().wait();

    // 线程已就绪，获取当前的时间戳
    start = std::chrono::high_resolution_clock::now();

    // 向 func1 & func2 发送就绪信号
    ready_promise.set_value();

    std::cout << "Thread 1 received the signal "
              << result1.get().count() << " ms after start\n"
              << "Thread 2 received the signal "
              << result2.get().count() << " ms after start\n";   
}