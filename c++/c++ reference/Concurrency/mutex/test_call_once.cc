/*
    std::call_once 函数
    根据std::once_flag，准确执行一次可调用 (Callable) 对象 f，即使同时从多个线程调用
*/

#include <iostream>
#include <mutex>
#include <thread>
#include <exception>
 
std::once_flag flag1, flag2;
 
void simple_do_once()
{
    std::call_once(flag1, [](){ std::cout << "简单样例：调用一次\n"; });
}
 
void may_throw_function(bool do_throw)
{
    if (do_throw)
    {
        std::cout << "抛出:call_once 会重试\n"; // 这会出现不止一次
        throw std::exception();
    }
    std::cout << "没有抛出,call_once 不会再重试\n"; // 保证一次
}
 
void do_once(bool do_throw)
{
    try
    {
        // std::call_once(flag2, may_throw_function, do_throw);
        //当使用 flag1 后，以下函数也不会再执行了
        std::call_once(flag1, may_throw_function, do_throw);
    }
    catch(const std::exception & e){
        std::cout << "error :" << e.what() << "\n";
    }
    catch (...) {}
}
 
int main()
{
    std::thread st1(simple_do_once);
    std::thread st2(simple_do_once);
    std::thread st3(simple_do_once);
    std::thread st4(simple_do_once);
    st1.join();
    st2.join();
    st3.join();
    st4.join();
 
    std::thread t1(do_once, true);
    std::thread t2(do_once, true);
    std::thread t3(do_once, false);
    std::thread t4(do_once, true);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}