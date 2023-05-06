#include <memory>
#include <iostream>

struct Good : std::enable_shared_from_this<Good>
{
    std::shared_ptr<Good> getptr()
    {
        return shared_from_this();
    }
};

struct Best : std::enable_shared_from_this<Best>
{
    std::shared_ptr<Best> getptr()
    {
        return shared_from_this();
    }

    //使用工厂函数来创建指针
    static std::shared_ptr<Best> create()
    {
        return std::shared_ptr<Best>(new Best());
    }
private:
    Best() = default;
};

struct Bad
{
    std::shared_ptr<Bad> getptr(){
        return std::shared_ptr<Bad>(this);
    }
    ~Bad() { std::cout << "Bad::~Bad() called\n";}
};

void testGood()
{
    // 好：二个 shared_ptr 共享同一对象
    std::shared_ptr<Good> good0 = std::make_shared<Good>();
    std::shared_ptr<Good> good1 = good0->getptr();
    std::cout << "good1.use_count() = " << good1.use_count() << '\n';
}
 
 
void misuseGood()
{
    // 坏：调用 shared_from_this 但没有 std::shared_ptr 占有调用者
    try {
        Good not_so_good;
        std::shared_ptr<Good> gp1 = not_so_good.getptr();
    } catch(std::bad_weak_ptr& e) {
        // 未定义行为（C++17 前）/抛出 std::bad_weak_ptr （C++17 起）
        std::cout << e.what() << '\n';    
    }
}
 
 
void testBest()
{
    // 最好：同上但无法栈分配它：
    std::shared_ptr<Best> best0 = Best::create();
    std::shared_ptr<Best> best1 = best0->getptr();
    std::cout << "best1.use_count() = " << best1.use_count() << '\n';
 
    // Best stackBest; // <- 不会通过编译，因为 Best::Best() 为私有。
}
 
 
void testBad()
{
    // Bad, each shared_ptr thinks it's the only owner of the object
    std::shared_ptr<Bad> bad0 = std::make_shared<Bad>();
    std::shared_ptr<Bad> bad1 = bad0->getptr();
    std::cout << "bad1.use_count() = " << bad1.use_count() << '\n';
} // UB： Bad 的二次删除
 
 
int main()
{
    testGood();
    misuseGood();
 
    testBest();
 
    testBad();
}