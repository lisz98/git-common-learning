/*
    类模板 std::promise 提供存储值或异常的设施，之后通过 std::promise 对象所创建的 std::future 对象异步获得结果。
    注意 std::promise 只应当使用一次。
*/

#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

template<class itr>
void accumulate(itr first,itr last,std::promise<int> accumulae_promise)
{
    int sum = std::accumulate(first,last,0);
    accumulae_promise.set_value(sum);
}

void do_work(std::promise<void(*)(void)> func)
{   

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << std::this_thread::get_id() << ":do_work" << std::endl;
    func.set_value([](){
        std::cout << std::this_thread::get_id() << ":new function" << std::endl;
    });
}


int main()
{
       // 演示用 promise<int> 在线程间传递结果。
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future();
    std::thread work_thread(accumulate<std::vector<int>::iterator>, numbers.begin(), numbers.end(),
                            std::move(accumulate_promise));
 
    // future::get() 将等待直至该 future 拥有合法结果并取得它
    // 无需在 get() 前调用 wait()
    //accumulate_future.wait();  // 等待结果
    // 假异步，代码流程还是同步走下去，但是实际相当于从这个函数片段跳到了线程中执行，最后回到主函数中执行
    std::cout << "result=" << accumulate_future.get() << '\n';
    work_thread.join();  // wait for thread completion
 
    // 演示用 promise<void> 在线程间对状态发信号
    std::promise<void(*)(void)> barrier;
    std::future<void(*)(void)> barrier_future = barrier.get_future();
    std::thread new_work_thread(do_work, std::move(barrier));
    // 在线程中设置的函数，返回到主线程中执行
    (*barrier_future.get())();
    new_work_thread.join(); 

    //数据不会马上到达就绪态，会在线程销毁结束以后到达就绪态
    using namespace std::chrono_literals;
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread([&p] {
          std::this_thread::sleep_for(1s);
          p.set_value_at_thread_exit(9);
    }).detach();
    std::cout << "Waiting..." << std::flush;
    f.wait();
    std::cout << "Done!\nResult is: " << f.get() << '\n';
}
