/*
类模板 std::future 提供访问异步操作结果的机制：

（通过 std::async 、 std::packaged_task 或 std::promise 创建的）异步操作能提供一个 std::future 对象给该异步操作的创建者。
然后，异步操作的创建者能用各种方法查询、等待或从 std::future 提取值。若异步操作仍未提供值，则这些方法可能阻塞。
异步操作准备好发送结果给创建者时，它能通过修改链接到创建者的 std::future 的共享状态（例如 std::promise::set_value ）进行。
注意， std::future 所引用的共享状态不与另一异步返回对象共享（与 std::shared_future 相反）
*/


#include <iostream>
#include <future>
#include <thread>
 
int main()
{
    // 来自 packaged_task 的 future
    std::packaged_task<int()> task([](){ return 7; }); // 包装函数
    std::future<int> f1 = task.get_future();  // 获取 future
    std::thread(std::move(task)).detach(); // 在线程上运行
 
    // 来自 async() 的 future
    std::future<int> f2 = std::async(std::launch::async, [](){ return 8; });
 
    // 来自 promise 的 future
    std::promise<int> p;
    std::future<int> f3 = p.get_future();
    std::thread( [&p]{ p.set_value_at_thread_exit(9); }).detach();
 
    std::cout << "Waiting..." << std::flush;
    f1.wait();
    f2.wait();
    f3.wait();
    std::cout << "Done!\nResults are: "
              << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
}