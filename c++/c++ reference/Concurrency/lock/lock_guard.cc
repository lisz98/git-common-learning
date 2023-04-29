/*
    类 lock_guard 是互斥体包装器，为在作用域块期间占有互斥提供便利 RAII 风格机制。

    创建 lock_guard 对象时，它试图接收给定互斥的所有权。控制离开创建 lock_guard 对象的作用域时，销毁 lock_guard 并释放互斥。

    lock_guard 类不可复制
*/

#include <thread>
#include <mutex>
#include <iostream>
 
int g_i = 0;
std::mutex g_i_mutex;  // 保护 g_i
 
void safe_increment()
{
    std::lock_guard<std::mutex> lock(g_i_mutex);
    ++g_i;
 
    std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
 
    // g_i_mutex 在锁离开作用域时自动释放
}
 
int main()
{
    std::cout << "main: " << g_i << '\n';
 
    std::thread t1(safe_increment);
    std::thread t2(safe_increment);
 
    t1.join();
    t2.join();
 
    std::cout << "main: " << g_i << '\n';
}