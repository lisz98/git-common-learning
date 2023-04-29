#include "test_thread.h"
#include <iostream>
#include <thread>
#include <chrono>

/*******************************************************************/

void f1(int n)
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "正在执行线程1\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
 
void f2(int& n)
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "正在执行线程2\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
 
class foo
{
public:
    void bar()
    {
        for (int i = 0; i < 5; ++i)
        {
            std::cout << "正在执行线程3\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};
 
class baz
{
public:
    void operator()()
    {
        for (int i = 0; i < 5; ++i)
        {
            std::cout << "正在执行线程4\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};
 
void test_create_thread()
{
    int n = 0;
    foo f;
    baz b;
    std::thread t1; // t1 不是线程
    std::thread t2(f1, n + 1); // 按值传递
    std::thread t3(f2, std::ref(n)); // 按引用传递
    std::thread t4(std::move(t3)); // t4 现在运行 f2()。t3 不再是线程
    std::thread t5(&foo::bar, &f); // t5 在对象 f 上运行 foo::bar()
    std::thread t6(b); // t6 在对象 b 的副本上运行 baz::operator()
    t2.join();
    t4.join();
    t5.join();
    t6.join();
    std::cout << "n 的最终值是 " << n << '\n';
    std::cout << "f.n (foo::n) 的最终值是 " << f.n << '\n';
    std::cout << "b.n (baz::n) 的最终值是 " << b.n << '\n';
}
/*******************************************************************/

void test_id()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

//标识与 *this 关联的线程的 std::thread::id 类型值。若无关联的线程，则返回默认构造的 std::thread::id 
void test_get_threadId()
{
    std::thread t1(test_id);
    std::thread::id t1_id = t1.get_id();
 
    std::thread t2(test_id);
    std::thread::id t2_id = t2.get_id();
 
    //std::hex 使cout 使用十六进制输出
    std::cout << "t1's id: " << std::hex << t1_id << '\n';
    std::cout << "t2's id: " << t2_id << '\n';
 
    t1.join();
    t2.join();
}

// TEST_MAIN(test_get_threadId)

/*******************************************************************/

void test_join()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
 
//检查 std::thread 对象是否标识活跃的执行线程。具体而言，若 get_id() != std::thread::id() 则返回 true
void test_thread_joinable(){

    std::thread t; //这创建的不是一个线程
    // std::boolalpha 是为了让cout 按照 true 和 false来输出
    std::cout << "before starting, joinable: " << std::boolalpha << t.joinable()
              << '\n';
 
    t = std::thread(test_join); //创建的是一个线程，可以被join
    std::cout << "after starting, joinable: " << t.joinable() 
              << '\n';
 
    t.join();
    //线程已经结束，t不在是一个活跃的线程
    std::cout << "after joining, joinable: " << t.joinable() 
              << '\n';
}   

// TEST_MAIN(test_thread_join)

/*******************************************************************/


#ifdef __linux__
#include <pthread.h>

std::mutex iomutex;
void test_native_handle(int num)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
 
    sched_param sch;
    int policy; 
    pthread_getschedparam(pthread_self(), &policy, &sch);
    std::lock_guard<std::mutex> lk(iomutex);
    std::cout << "Thread " << num << " is executing at priority "
              << sch.sched_priority << '\n';
}
 
void test_thread_native_handle()
{
    std::thread t1(test_native_handle, 1), t2(test_native_handle, 2);
 
    sched_param sch;
    int policy; 
    //获取当前线程的调度策略
    pthread_getschedparam(t1.native_handle(), &policy, &sch);
    sch.sched_priority = 20;
    //设置当前线程的调度策略
    if (pthread_setschedparam(t1.native_handle(), SCHED_FIFO, &sch)) {
        std::cout << "Failed to setschedparam: " << std::strerror(errno) << '\n';
    }
 
    t1.join(); 
    t2.join();
}
#else
#include <processthreadsapi.h>
#include <tlhelp32.h>

int GetProcessThreadList(DWORD th32ProcessID) //进程的ID
{
    HANDLE hThreadSnap;
    THREADENTRY32 th32;
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, th32ProcessID);
    if (hThreadSnap == INVALID_HANDLE_VALUE)
    {
    return 1;
    }
    th32.dwSize = sizeof(THREADENTRY32);
    if (!Thread32First(hThreadSnap, &th32))
    {
    CloseHandle(hThreadSnap);
    return 1;
    }
    do
    {
    if (th32.th32OwnerProcessID == th32ProcessID)
    {
    printf("ThreadID: %ld\n", th32.th32ThreadID); //显示找到的线程的ID
    }
    }while(Thread32Next(hThreadSnap, &th32));
    CloseHandle(hThreadSnap);
    return 0;
}


void test_native_handle(int num)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "num=" << num <<",test_native_handle thread id=" << GetCurrentThreadId() << std::endl;

}
void test_native_handle_2(int num)
{

    while(true){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "num=" << num <<",test_native_handle thread id=" << GetCurrentThreadId() << std::endl;
    std::cout << "num=" << num <<",test_native_handle thread id=" << GetCurrentThread() << std::endl;
    }
}



void test_thread_native_handle()
{
    std::cout << "test_thread_native_handle" << std::endl;
    std::thread t1(test_native_handle, 1), t2(test_native_handle_2, 2);


    std::cout << "当前所有的句柄...."<< std::endl;
    GetProcessThreadList(GetCurrentProcessId());

    t1.join(); 
    //如果设置线程分离后 TerminateThread 会失去效果
    // t2.detach();
    std::cout << "输入任意按键中止线程2:"<< std::endl;

    getchar();
    //使用句柄强制中止test_native_handle_2
    std::cout << "正在终止...."<< (HANDLE)t2.native_handle() << std::endl;
    TerminateThread((HANDLE)t2.native_handle(), (unsigned long)0x00);
    // ExitThread(*(DWORD*)t2.native_handle());
    std::cout << "结束...."<< std::endl;
    std::cout << "当前所有的句柄...."<< std::endl;
    t2.join();

    //会退出线程，但是并不会销毁掉句柄
    GetProcessThreadList(GetCurrentProcessId());
    while(true);

    
}
// TEST_MAIN(test_thread_native_handle)


/*******************************************************************/

void test_thread_hardware_concurrency()
{
    uint32_t n = std::thread::hardware_concurrency();

    std::cout << n << "  concurrency threads are supported.\n";
}


TEST_MAIN(test_thread_hardware_concurrency)


/*******************************************************************/
#endif
