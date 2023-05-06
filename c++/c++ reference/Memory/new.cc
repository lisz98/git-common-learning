/*
��ʹ������ <new> ͷ�ļ����汾 (1-4) Ҳ����ÿ�����뵥Ԫ��ʽ�������汾 (1-8) �����滻���ڳ�������λ�ö��岢������Դ�ļ����û��ṩ��ӵ����ͬǩ���ķǳ�Ա���������滻Ĭ�ϰ汾��������������Ҫ�ɼ���

����ĳ�������滻�ķ��亯��������������ṩ�����Ķ���滻�������д� inline ˵�������滻��������ô�������������Ҫ����ϡ�����滻��ȫ�������ռ�����������ռ��ж��壬�������������ȫ��������ľ�̬�ǳ�Ա��������ô�����������

���׳��汾�ı�׼��ʵ�� (5-8) ֱ�ӵ��ö�Ӧ���׳��汾 (1-4)���׳�������汾�ı�׼��ʵ�� (2,4) ֱ�ӵ��ö�Ӧ�ĵ�����汾 (1,3)�����ֻ��Ҫ�滻�׳���������亯���Ϳ��Դ������з��䡣
*/

#include <cstdio>
#include <cstdlib>
#include <new>
#include <iostream>
 

// #ifndef NEW_HANDLER
// #define NEW_HANDLER
// #endif

// ��С���������滻��
 
//��ȫ��ʹ�õ� operator new �����滻
#ifndef NEW_HANDLER
// �� inline ���� [replacement.functions]/3 Ҫ��
void* operator new(std::size_t sz)
{
    std::printf("�ѵ���ȫ�� new ���������СΪ %zu\n", sz);
    if (sz == 0)
        ++sz; // ���� std::malloc(0)�������ܻ��ڳɹ�ʱ���� nullptr
 
    if (void *ptr = std::malloc(sz))
        return ptr;
 
    throw std::bad_alloc{}; // �� [new.delete.single]/3 Ҫ��
}
 
void operator delete(void* ptr) noexcept
{
    std::puts("�ѵ���ȫ�� delete �����");
    std::free(ptr);
}
#else  //����Զ���new & delete�󣬾Ͳ�����뵽���������
void handler()
{
    std::cout << "Memory allocation failed, terminating\n";
    std::set_new_handler(nullptr);
}
#endif
class test
{

};

int main()
{
    //ע��һ�� new ������,���δ��װ��Ϊnullptr

    int* p1 = new int;
    delete p1;
 
    int* p2 = new int[10]; // C++11 �б�֤�����滻
    delete[] p2;

    test * t = new test;
    delete t;
#ifdef NEW_HANDLER
    std::set_new_handler(handler);
    try {
        while (true) {
            new int[100000000ul];
        }
    } catch (const std::bad_alloc& e) {
        std::cout << e.what() << '\n';
    }
#endif
}