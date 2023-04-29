/*
    类 unique_lock 是通用互斥包装器，允许延迟锁定、锁定的有时限尝试、递归锁定、所有权转移和与条件变量一同使用。

    类 unique_lock 可移动，但不可复制——它满足可移动构造 (MoveConstructible) 和可移动赋值 (MoveAssignable) 但不满足可复制构造 (CopyConstructible) 或可复制赋值 (CopyAssignable) 。

    类 unique_lock 满足基本可锁定 (BasicLockable) 要求。若 Mutex 满足可锁定 (Lockable) 要求，则 unique_lock 亦满足可锁定 (Lockable) 要求（例如：能用于 std::lock ） ；若 Mutex 满足可定时锁定 (TimedLockable) 要求，则 unique_lock 亦满足可定时锁定 (TimedLockable) 要求。
*/

#include <mutex>
#include <thread>
#include <chrono>
 
struct Box {
    explicit Box(int num) : num_things{num} {}
 
    int num_things;
    std::mutex m;
};
 
void transfer(Box &from, Box &to, int num)
{

    /*
        std::defer_lock : 不获得互斥的所有权 。保证lock能保证上锁。unique_lock只保证解锁
        std::adopt_lock ：假设调用方线程已拥有互斥的所有权。 lock 已经在前面获得过锁，unique_lock只保证解锁
    */
#if 0
    // 仍未实际取锁
    std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
    std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);
 
    // 锁两个 unique_lock 而不死锁
    std::lock(lock1, lock2);   
#else
    std::lock(from.m,to.m);
    std::unique_lock<std::mutex> lock1(from.m,std::adopt_lock);
    std::unique_lock<std::mutex> lock2(to.m,std::adopt_lock);
#endif

    from.num_things -= num;
    to.num_things += num;
 
    // 'from.m' 与 'to.m' 互斥解锁于 'unique_lock' 析构函数
}
 
int main()
{
    Box acc1(100);
    Box acc2(50);
 
    std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
    std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);
 
    t1.join();
    t2.join();
}