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

    //ʹ�ù�������������ָ��
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
    // �ã����� shared_ptr ����ͬһ����
    std::shared_ptr<Good> good0 = std::make_shared<Good>();
    std::shared_ptr<Good> good1 = good0->getptr();
    std::cout << "good1.use_count() = " << good1.use_count() << '\n';
}
 
 
void misuseGood()
{
    // �������� shared_from_this ��û�� std::shared_ptr ռ�е�����
    try {
        Good not_so_good;
        std::shared_ptr<Good> gp1 = not_so_good.getptr();
    } catch(std::bad_weak_ptr& e) {
        // δ������Ϊ��C++17 ǰ��/�׳� std::bad_weak_ptr ��C++17 ��
        std::cout << e.what() << '\n';    
    }
}
 
 
void testBest()
{
    // ��ã�ͬ�ϵ��޷�ջ��������
    std::shared_ptr<Best> best0 = Best::create();
    std::shared_ptr<Best> best1 = best0->getptr();
    std::cout << "best1.use_count() = " << best1.use_count() << '\n';
 
    // Best stackBest; // <- ����ͨ�����룬��Ϊ Best::Best() Ϊ˽�С�
}
 
 
void testBad()
{
    // Bad, each shared_ptr thinks it's the only owner of the object
    std::shared_ptr<Bad> bad0 = std::make_shared<Bad>();
    std::shared_ptr<Bad> bad1 = bad0->getptr();
    std::cout << "bad1.use_count() = " << bad1.use_count() << '\n';
} // UB�� Bad �Ķ���ɾ��
 
 
int main()
{
    testGood();
    misuseGood();
 
    testBest();
 
    testBad();
}