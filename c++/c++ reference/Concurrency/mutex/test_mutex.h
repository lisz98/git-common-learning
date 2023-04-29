#ifndef __TEST_MUTEX_H__
#define __TEST_MUTEX_H__

/*
    mutex 类是能用于保护共享数据免受从多个线程同时访问的同步原语。
*/

void test_mutex();



#define TEST_MAIN(f)\
int main(int argc,char** argv)\
{\
    f();\
    return 0;\
}\

#endif