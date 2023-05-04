/*
��ģ�� std::shared_future �ṩ�����첽��������Ļ��ƣ����� std::future �������������̵߳Ⱥ�ͬһ����״̬����ͬ�ڽ����ƶ��� std::future ����ֻ��һ��ʵ����ָ���κ��ض����첽�������std::shared_future �ɸ��ƶ��Ҷ�� shared_future ������ָ��ͬһ����״̬��

��ÿ���߳�ͨ��������� shared_future ���󸱱����ʣ���Ӷ���̷߳���ͬһ����״̬�ǰ�ȫ��
*/

#include <iostream>
#include <future>
#include <chrono>
#include <thread>

int main()
{
    //��������void���ʹ洢ֵ�����ڵ����ź�
    std::promise<void> ready_promise,t1_ready_promise,t2_ready_promise;
    std::shared_future<void> ready_future(ready_promise.get_future());

    std::chrono::time_point<std::chrono::high_resolution_clock> start;


    auto func1 = [&,ready_future]() ->std::chrono::duration<double,std::milli>
    {
        t1_ready_promise.set_value(); //�����ź�֪ͨ Main ���̣��Ѿ�׼������
        std::cout << "ready curThreadId:" << std::this_thread::get_id() << '\n';
        ready_future.wait();  //�ȴ� main ���̷��͵��ź�, ready_promise.set_value();
        return std::chrono::high_resolution_clock::now() -start;
    };

    auto func2 = [&, ready_future]() -> std::chrono::duration<double, std::milli> 
    {
        t2_ready_promise.set_value();
        std::cout << "ready curThreadId:" << std::this_thread::get_id() << '\n';
        ready_future.wait(); // �ȴ����� main() ���ź�
        return std::chrono::high_resolution_clock::now() - start;
    };  

    //�첽ִ�� result1 & result2
    auto result1 = std::async(std::launch::async,func1);
    auto result2 = std::async(std::launch::async,func2);

    // �ȴ��̱߳�Ϊ����
    t1_ready_promise.get_future().wait();
    t2_ready_promise.get_future().wait();

    // �߳��Ѿ�������ȡ��ǰ��ʱ���
    start = std::chrono::high_resolution_clock::now();

    // �� func1 & func2 ���;����ź�
    ready_promise.set_value();

    std::cout << "Thread 1 received the signal "
              << result1.get().count() << " ms after start\n"
              << "Thread 2 received the signal "
              << result2.get().count() << " ms after start\n";   
}