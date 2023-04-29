/*
    notify_all_at_thread_exit 提供机制，通知其他线程给定的线程已完全完成，包括销毁所有 thread_local 对象。它操作如下：

    将先前获得的锁 lk 的所有权转移到内部存储。
    修改执行环境，以令当前线程退出时，如同以下列方式通知 condition_variable cond:
        lk.unlock();
        cond.notify_all();
*/

#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>
 
std::mutex m;
std::condition_variable cv;
 
bool ready = false;
int result;  

thread_local int g_thread_data =0 ;

int function_that_uses_thread_locals()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    g_thread_data =1000;
    return 1;
}
 
void thread_func()
{
    std::unique_lock<std::mutex> lk(m);
    // 用 thread_local 数据赋值给 result
    result = function_that_uses_thread_locals();
    ready = true;
    std::notify_all_at_thread_exit(cv, std::move(lk));
} // 1. 销毁 thread_local 对象， 2. 解锁互斥， 3. 通知 cv
 
int main()
{
    std::thread t(thread_func);
    t.detach();
 
    // 做其他工作
    // .…
 
    // 等待脱附的线程
    std::unique_lock<std::mutex> lk(m);
    while(!ready) {
        cv.wait(lk);
    }
    return 0;
}