#ifndef __TEST_JTHREAD_H__
#define __TEST_JTHREAD_H__

/*
    我的编译器还不支持我实现下面的功能hhh，下次再说
*/

/*******************************************************************/

//返回与线程的停止状态关联的 stop_source 对象
void test_jthread_get_stop_source();

/*******************************************************************/

//返回与线程的共享停止状态关联的 stop_token
void test_jthread_get_stop_token();
/*******************************************************************/

//请求执行经由线程的共享停止状态停止
void test_jthread_request_stop();
/*******************************************************************/

#define TEST_MAIN(f)\
int main(int argc,char** argv)\
{\
    f();\
    return 0;\
}\


#endif