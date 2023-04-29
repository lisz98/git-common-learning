/*
    recursive_timed_mutex 声明在<share_mutex>中
*/

#include <shared_mutex>
#include <iostream>
#include <thread>
#include <string>
 
std::thread::id getThreadId()
{
    return std::this_thread::get_id();
}

class X {
    typedef std::lock_guard<std::recursive_timed_mutex> lock;
    std::recursive_timed_mutex m;
    std::string shared;
  public:
    void fun1() {
      lock lk(m);
      shared = "fun1";
      std::cout << getThreadId() <<" in fun1, shared variable is now " << shared << '\n';
    }
    void fun2() {
      lock lk(m);
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
