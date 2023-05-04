/*
����ģ�� std::async �첽�����к��� f���п����ڿ������̳߳�һ���ֵķ����߳��У������������ս����иú������ý���� std::future��

std::launch::async	�������̣߳����첽ִ������
std::launch::deferred	���÷��߳����״���������ʱִ�����񣨶�����ֵ��


*/

#include <future>
#include <iostream>
#include <mutex>
#include <numeric>
#include <string>
#include <vector>

std::mutex m;

struct X
{
    void foo(int i, const std::string& str)
    {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << ' ' << i << '\n';
    }
 
    void bar(const std::string& str)
    {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << '\n';
    }
 
    int operator()(int i)
    {
        std::lock_guard<std::mutex> lk(m);
        std::cout << i << '\n';
        return i + 10;
    }
};

template<typename RandomIt>
int parallel_sum(RandomIt beg,RandomIt end)
{
    auto len = end - beg;
    if(len < 1000){
        return std::accumulate(beg,end,0);
    }

    RandomIt mid = beg + len /2 ;
    auto handle = std::async(std::launch::async,
            parallel_sum<RandomIt>,mid,end);
    
    int sum = parallel_sum(beg,mid);
    return sum + handle.get();
}

int main()
{
    std::vector<int> v(10000, 1);
    std::cout << "��Ϊ " << parallel_sum(v.begin(), v.end()) << '\n';
 
    X x;
    // ��Ĭ�ϲ��Ե��� x.foo(42, "Hello") ��
    // ����ͬʱ��ӡ "Hello 42" ���ӳ�ִ��
    auto a1 = std::async(&X::foo, &x, 42, "Hello");
    // �� deferred ���Ե��� x.bar("world!")
    // ���� a2.get() �� a2.wait() ʱ��ӡ "world!"
    auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
    // �� async ���Ե��� X()(43) ��
    // ͬʱ��ӡ "43"
    auto a3 = std::async(std::launch::async, X(), 43);
    a2.wait();                     // ��ӡ "world!"
    std::cout << a3.get() << '\n'; // ��ӡ "53"
} // �� a1 �ڴ˵�δ��ɣ��� a1 �����������ڴ˴�ӡ "Hello 42"