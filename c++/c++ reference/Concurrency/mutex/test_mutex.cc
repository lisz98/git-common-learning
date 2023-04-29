#include "test_mutex.h"

/*******************************************************************/
#if 1
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

std::map<std::string,std::string> g_pages;
std::mutex g_pages_mutex;

void test_save_page(const std::string &url)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string result = "fake content";

    std::lock_guard<std::mutex> guard(g_pages_mutex);
    g_pages[url] = result;
}

void test_mutex()
{
    std::thread t1(test_save_page,"http://foo");
    std::thread t2(test_save_page,"http://bar");
    t1.join();
    t2.join();

    for (const auto &pair : g_pages) {
        std::cout << pair.first << " => " << pair.second << '\n';
    }

}

TEST_MAIN(test_mutex)
#endif
/*******************************************************************/


/*******************************************************************/
