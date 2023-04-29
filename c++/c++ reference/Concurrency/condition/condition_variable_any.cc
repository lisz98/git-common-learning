/*
    condition_variable_any 类是 std::condition_variable 的泛化。相对于只在 std::unique_lock<std::mutex> 上工作的 std::condition_variable ， 
    condition_variable_any 能在任何满足基本可锁定 (BasicLockable) 要求的锁上工作。
*/

#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <mutex>

#define mycout std::cout << std::this_thread::get_id() << ":"

std::mutex  mtx;
std::string data;
std::condition_variable_any cv;

bool ready=false;
bool processed=false;

/*
    实现一个支持lock 和 unlock的锁定器来使用 std::condition_variable_any
*/
template<class T>
class mylock : public std::lock_guard<T>
{
public:
    mylock(T &t) 
            : std::lock_guard<T>(t),_t(t){}
    ~mylock(){}

    void lock(){
        _t.lock();
    }

    void unlock(){
        _t.unlock();
    }

    T &_t;
};

void worker()
{
    {
        mylock<std::mutex>  lock(mtx);
        cv.wait(lock,[](){
            return ready;
        });
        mycout <<"worker start"<< std::endl;

        data = "ready=" + std::to_string(ready);
        processed = true;
    }

    cv.notify_one();
}

int main()
{
    std::thread thread(worker);

    {
        mylock<std::mutex> lock(mtx);
        ready =true;
        data = "main() signal to worker";
    }
    mycout << data<< std::endl;
    cv.notify_one();

    {
        mylock<std::mutex> lock(mtx);
        cv.wait(lock,[](){
            return processed;
        });
    }
    mycout << "callback " << data << std::endl;

    thread.join();
    return 0;
}

