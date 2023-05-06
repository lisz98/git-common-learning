#include "timestamp.h"
#include <iostream>

int main()
{
    std::cout << SZ::TimeStamp::now().toString() << std::endl;

    std::cout << SZ::TimeStamp::now().toUTC() << std::endl;

    return 0;
}