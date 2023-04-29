/*
    std::memory_order 用于指定内存访问，
    来表明如何围绕原子操作排序

    有以下几种方式：
    memory_order_relaxed：
        宽松操作：没有同步或顺序制约，仅对此操作要求原子性（见下方宽松顺序）。
    memory_order_consume：
        有此内存顺序的加载操作，在其影响的内存位置进行消费操作：
        当前线程中依赖于当前加载的该值的读或写不能被重排到此加载前。
        其他释放同一原子变量的线程的对数据依赖变量的写入，为当前线程所可见。
        在大多数平台上，这只影响到编译器优化（见下方释放消费顺序）。
    memory_order_acquire：
        有此内存顺序的加载操作，在其影响的内存位置进行获得操作：
        当前线程中读或写不能被重排到此加载前。其他释放同一原子变量的线程的所有写入，
        能为当前线程所见（见下方释放获得顺序）
    memory_order_release:
    	有此内存顺序的存储操作进行释放操作：
        当前线程中的读或写不能被重排到此存储后。当前线程的所有写入，
        可见于获得该同一原子变量的其他线程（见下方释放获得顺序），
        并且对该原子变量的带依赖写入变得对于其他消费同一原子对象的线程可见（见下方释放消费顺序）
    memory_order_acq_rel:
    	带此内存顺序的读修改写操作既是获得操作又是释放操作。
        当前线程的读或写内存不能被重排到此存储前或后。
        所有释放同一原子变量的线程的写入可见于修改之前，而且修改可见于其他获得同一原子变量的线程。
    memory_order_seq_cst:	
        有此内存顺序的加载操作进行获得操作，存储操作进行释放操作，
        而读修改写操作进行获得操作和释放操作，再加上存在一个单独全序，
        其中所有线程以同一顺序观测到所有修改（见下方序列一致顺序）。            
*/

/**************************************************/

#if 0
#include <thread>
#include <iostream>
#include <atomic>
#include <vector>
//使用宽松的方式实现原子操作，不要求执行的顺序或同步，只保证数据的原子性子和修改顺序的一致性
// std::atomic<int> cnt = {0};
std::atomic<int> cnt = ATOMIC_VAR_INIT(0);

void f(){
    for(int i =0; i <1000; ++i){
        //只保证原子性和修改顺序的一致性,常用于计算器自增，不要求线程执行的顺序或同步
        cnt.fetch_add(1,std::memory_order_relaxed);
    }
}

int main(int argc,char ** argv)
{
    std::vector<std::thread> v;
    for (int n = 0; n < 10; ++n) {
        v.emplace_back(f);
    }
    for (auto& t : v) {
        t.join();
    }
    std::cout << "Final counter value is " << cnt << '\n';    

    return 0;
}
#endif

/**************************************************/
/*
    生产者消费者模型
    memory_order_release，memory_order_acquire一般成对使用

    一旦原子加载完成，能够保证线程B能够观察到线程A写入内存的所有内容
*/
#if 0
#include <iostream>
#include <thread>
#include <atomic>
#include <cassert>
#include <string>

std::atomic<std::string *> ptr;
int data;

void producer()
{
    std::string* p = new std::string("hello");
    data = 42;
    //当store存储数据后使用 memory_order_release，线程中的所有操作对consumer可见
    ptr.store(p,std::memory_order_release);
}

void consumer()
{
    std::string* p2;
    // 保证时序，在 producer 完成生产后，获得ptr中的数据
    while(!(p2 = ptr.load(std::memory_order_acquire)));

    //虽然只获取了ptr中的数据，但是 producer 中的过程对于 consumer 来说都是可见的
    assert(*p2 == "hello");
    assert(data == 42);
    std::cout << *p2 << data;
}

int main(int argc,char ** argv)
{  
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}
#endif
/**************************************************/


/**************************************************/
/*
    演示三个线程间传递性的释放获得顺序
*/
#if 0
#include <thread>
#include <atomic>
#include <cassert>
#include <vector>
#include <iostream>

std::vector<int> data;
std::atomic<int> flag = ATOMIC_VAR_INIT(0);

// 线程的执行顺序 1 -> 2 ->3
void thread_1()
{
    data.push_back(42);
    flag.store(1,std::memory_order_release);
    std::cout << "thread_1" << std::endl;
}

void thread_2()
{
    int expected =1;
    //memory_order_acq_rel 是获取，也是释放
    //这里expected 2若相等则进行交换，若不相等则进行加载
    //可用于做状态机，只有当修改成功后才会返回ture，保证状态能够正常切换
    while(!flag.compare_exchange_strong(expected,2,std::memory_order_acq_rel));
    std::cout << flag.load(std::memory_order_acquire) << std::endl;
    std::cout << "thread_2" << std::endl;
   
}

void thread_3()
{
    while (flag.load(std::memory_order_acquire) < 2);
    assert(data.at(0) == 42); // 决不出错
    std::cout << "thread_3" << std::endl;
}

int main()
{
    std::thread a(thread_1);
    std::thread b(thread_2);
    std::thread c(thread_3);
    a.join(); 
    b.join(); 
    c.join();

    return 0;
}
#endif
/**************************************************/


/**************************************************/
/*
    使用 memory_order_seq_cst 保证线程按照完全顺序来执行，一定不会出现 z 为 0的条件
*/
#if 1
#include <thread>
#include <atomic>
#include <cassert>
#include <iostream>
 
std::atomic<bool> x = {false};
std::atomic<bool> y = {false};
std::atomic<int> z = {0};
 
void write_x()
{
    x.store(true, std::memory_order_seq_cst);
    std::cout << "write_x" << std::endl;
}
 
void write_y()
{
    y.store(true, std::memory_order_seq_cst);
    std::cout << "write_y" << std::endl;
}
 
void read_x_then_y()
{
    //线程必须按照 x -> y 进行观察，如果不是的话可能会引发 z.load() assert
    while (!x.load(std::memory_order_seq_cst));
    if (y.load(std::memory_order_seq_cst)) {
        ++z;
        std::cout << "read_x_then_y" << std::endl;
    }
}
 
void read_y_then_x()
{
    while (!y.load(std::memory_order_seq_cst));
    if (x.load(std::memory_order_seq_cst)) {
        ++z;
        std::cout << "read_y_then_x" << std::endl;
    }
}
 
int main()
{
    std::thread a(write_x);
    std::thread b(write_y);
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join(); b.join(); c.join(); d.join();
    assert(z.load() != 0);  // 决不发生
    std::cout << z.load() << std::endl;
}
#endif
/**************************************************/
