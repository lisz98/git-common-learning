/*
    condition_variable 类是同步原语，能用于阻塞一个线程，或同时阻塞多个线程，直至另一线程修改共享变量（条件）并通知 condition_variable 。
    condition_variable 必须要配合 std::unique_lock<std::mutex> 使用来实现，信号量效果
*/

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
 
void worker_thread()
{
    // 等待直至 main() 发送数据
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return ready;});
 
    // 等待后，我们占有锁。
    std::cout << "Worker thread is processing data\n";
    data += " after processing";
 
    // 发送数据回 main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";
 
    // 通知前完成手动解锁，以避免等待线程才被唤醒就阻塞（细节见 notify_one ）
    lk.unlock();
    cv.notify_one();
}
 
int main()
{
    std::thread worker(worker_thread);
 
    data = "Example data";
    // 发送数据到 worker 线程
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();
 
    // 等候 worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return processed;});
    }
    std::cout << "Back in main(), data = " << data << '\n';
 
    worker.join();
}