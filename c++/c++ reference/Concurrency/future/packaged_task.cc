/*
类模板 std::packaged_task 包装任何可调用 (Callable) 目标（函数、 lambda 表达式、 bind 表达式或其他函数对象），使得能异步调用它。其返回值或所抛异常被存储于能通过 std::future 对象访问的共享状态中。

正如 std::function ， std::packaged_task 是多态、具分配器的容器：可在堆上或以提供的分配器分配存储的可调用对象
*/

#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>

int f(int x,int y){
    return std::pow(x,y);
}


//使用lambda方式构造packaged_task
void task_lambda()
{
    //创建一个可调用的目标函数
    std::packaged_task<int(int,int)> task([](int x,int y){
        return std::pow(x,y);
    });

    std::future<int> result = task.get_future();

    task(2,9);

    std::cout << "task_lambda:\t" << result.get() << '\n';

}

//使用std::bind函数来构造packaged_task
void task_bind()
{
    std::packaged_task<int()> task(std::bind(f,2,11));
    std::future<int> result = task.get_future();

    task();

    std::cout << "task_bind:\t" << result.get() << '\n';
}

//在线程中使用packaged_task
void task_thread()
{
    std::packaged_task<int(int,int)> task(f);

    std::future<int> result = task.get_future();

    std::thread task_thread(std::move(task),2,10);

    task_thread.join();
    std::cout << "task_thread:\t" << result.get() << '\n';
}
 
int main()
{
    task_lambda();
    task_bind();
    task_thread();
}