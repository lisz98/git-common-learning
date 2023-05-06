/*
std::weak_ptr ��һ������ָ�룬���Ա� std::shared_ptr ����Ķ�����ڷ�ӵ���ԣ������������á��ڷ��������õĶ���ǰ������ת��Ϊ std::shared_ptr��

std::weak_ptr ���������ʱ����Ȩ�ĸ����ĳ������ֻ�д���ʱ����Ҫ�����ʣ�������ʱ���ܱ�����ɾ��ʱ������ʹ�� std::weak_ptr �����ٸö�����Ҫ�����ʱ����Ȩʱ������ת��Ϊ std::shared_ptr����ʱ���ԭ���� std::shared_ptr �����٣���ö���������ڽ����ӳ��������ʱ�� std::shared_ptr ͬ��������Ϊֹ��

std::weak_ptr ����һ�÷��Ǵ�� std::shared_ptr ������Ķ�����ɵĻ�״���á������ֻ���������������ָ���е��ⲿ����ָ�룩���� shared_ptr ���ü����޷��ִ��㣬���ڴ汻й¶������е�ָ��֮һΪ��ָ���Ա���������
*/

#include <iostream>
#include <memory>

std::weak_ptr<int> gw;

void observe()
{
    std::cout << "Use_count ==" << gw.use_count() << ": ";
    if(auto spt = gw.lock()){
        std::cout << *spt <<"\n";
    }else{
        std::cout << "gw is expired\n";
    }
}

int main()
{
    {
        auto sp = std::make_shared<int>(42);
	    gw = sp;
 
	    observe();
    }
 
    observe();    
}