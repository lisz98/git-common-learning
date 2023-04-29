#ifndef __TEST_THREAD_H__
#define __TEST_THREAD_H__


//线程构造函数使用
void test_create_thread();

//获取线程id
void test_get_threadId();

//线程join
void test_thread_joinable();

//获取底层定义的线程句柄
void test_thread_native_handle();


//windows下获取所有句柄
#ifndef __linux__
#include <Windows.h>
int GetProcessThreadList(DWORD th32ProcessID);
#endif


//返回线程实现支持的并发线程数。应该只把该值当做提示
void test_thread_hardware_concurrency();


#define TEST_MAIN(f)\
int main(int argc,char** argv)\
{\
    f();\
    return 0;\
}\


#endif