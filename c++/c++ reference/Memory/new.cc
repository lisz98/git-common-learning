/*
即使不包含 <new> 头文件，版本 (1-4) 也会在每个翻译单元隐式声明。版本 (1-8) 可以替换：在程序任意位置定义并在任意源文件的用户提供的拥有相同签名的非成员函数都会替换默认版本。它的声明不需要可见。

对于某个可以替换的分配函数，如果程序中提供了它的多个替换，或它有带 inline 说明符的替换声明，那么程序非良构，不要求诊断。如果替换在全局命名空间以外的命名空间中定义，或它被定义成在全局作用域的静态非成员函数，那么程序非良构。

不抛出版本的标准库实现 (5-8) 直接调用对应的抛出版本 (1-4)。抛出的数组版本的标准库实现 (2,4) 直接调用对应的单对象版本 (1,3)。因此只需要替换抛出单对象分配函数就可以处理所有分配。
*/

#include <cstdio>
#include <cstdlib>
#include <new>
#include <iostream>
 

// #ifndef NEW_HANDLER
// #define NEW_HANDLER
// #endif

// 最小函数集的替换：
 
//对全局使用的 operator new 进行替换
#ifndef NEW_HANDLER
// 无 inline ，由 [replacement.functions]/3 要求
void* operator new(std::size_t sz)
{
    std::printf("已调用全局 new 运算符，大小为 %zu\n", sz);
    if (sz == 0)
        ++sz; // 避免 std::malloc(0)，它可能会在成功时返回 nullptr
 
    if (void *ptr = std::malloc(sz))
        return ptr;
 
    throw std::bad_alloc{}; // 由 [new.delete.single]/3 要求
}
 
void operator delete(void* ptr) noexcept
{
    std::puts("已调用全局 delete 运算符");
    std::free(ptr);
}
#else  //如果自定了new & delete后，就不会进入到这个函数中
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
    //注册一个 new 处理函数,如果未安装则为nullptr

    int* p1 = new int;
    delete p1;
 
    int* p2 = new int[10]; // C++11 中保证调用替换
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