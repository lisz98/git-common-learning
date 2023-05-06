#include <iostream>
#include <utility>
#include <vector>
#include <string>
 
int main()
{
    std::string str = "Hello";
    std::vector<std::string> v;
 
    // ʹ�� push_back(const T&) ���أ�
    // ��ʾ���ǽ��������� str �ĳɱ�
    v.push_back(str);
    std::cout << "After copy, str is \"" << str << "\"\n";
 
    // ʹ����ֵ���� push_back(T&&) ���أ�
    // ��ʾ�������ַ���������
    // str �����ݱ��ƶ��� vector
    // ��������Ƚϵͣ���Ҳ��ζ�� str ���ڿ���Ϊ�ա�
    v.push_back(std::move(str));
    std::cout << "After move, str is \"" << str << "\"\n";
 
    std::cout << "The contents of the vector are \"" << v[0]
                                         << "\", \"" << v[1] << "\"\n";
}