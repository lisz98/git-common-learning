
/*
    提供一种支持递归调用上锁的函数
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
 
std::thread::id getThreadId()
{
    return std::this_thread::get_id();
}

class X {
    std::recursive_mutex m;
    std::string shared;
  public:
    void fun1() {
      std::lock_guard<std::recursive_mutex> lk(m);
      shared = "fun1";
      std::cout << getThreadId() <<" in fun1, shared variable is now " << shared << '\n';
    }
    void fun2() {
      std::lock_guard<std::recursive_mutex> lk(m);
      shared = "fun2";
      std::cout << getThreadId() <<" in fun2, shared variable is now " << shared << '\n';
      fun1(); // 递归锁在此处变得有用
      std::cout << getThreadId() <<" back in fun2, shared variable is " << shared << '\n';
    };
};
 
int main() 
{
    X x;
    std::thread t1(&X::fun1, &x);
    std::thread t2(&X::fun2, &x);
    t2.join();
    t1.join();
}