/*
��ģ�� std::future �ṩ�����첽��������Ļ��ƣ�

��ͨ�� std::async �� std::packaged_task �� std::promise �����ģ��첽�������ṩһ�� std::future ��������첽�����Ĵ����ߡ�
Ȼ���첽�����Ĵ��������ø��ַ�����ѯ���ȴ���� std::future ��ȡֵ�����첽������δ�ṩֵ������Щ��������������
�첽����׼���÷��ͽ����������ʱ������ͨ���޸����ӵ������ߵ� std::future �Ĺ���״̬������ std::promise::set_value �����С�
ע�⣬ std::future �����õĹ���״̬������һ�첽���ض������� std::shared_future �෴��
*/


#include <iostream>
#include <future>
#include <thread>
 
int main()
{
    // ���� packaged_task �� future
    std::packaged_task<int()> task([](){ return 7; }); // ��װ����
    std::future<int> f1 = task.get_future();  // ��ȡ future
    std::thread(std::move(task)).detach(); // ���߳�������
 
    // ���� async() �� future
    std::future<int> f2 = std::async(std::launch::async, [](){ return 8; });
 
    // ���� promise �� future
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