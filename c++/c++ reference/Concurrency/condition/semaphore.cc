/*
    c++ 11未支持信号量
    自己通过 condition_variable & mutex 来实现一个信号量
*/
#include <thread>
#include <stdint.h>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <functional>

template<std::ptrdiff_t MaxValue = UINT32_MAX -1>
class Semaphore
{
public:
    constexpr explicit Semaphore(std::ptrdiff_t count =1)
            :_count( (count > max()) ? max() : count){}
    ~Semaphore(){

    }
    void release(std::ptrdiff_t update=1){
        std::unique_lock<std::mutex> lock(_mtx);
        _count += update;
        if(update < 0 || _count > max()){
            return ;
        }
        while(--update >=0){
            _cv.notify_one();
        }
    }
    void acquire(){
        std::unique_lock<std::mutex> lock(_mtx);
        _cv.wait(lock,std::bind(&Semaphore::wait,this));
        --_count;
    }
    bool try_acquire() noexcept{
        std::unique_lock<std::mutex> lock(_mtx);
        if(_count > 0){
            _cv.wait(lock);
            --_count;
            return true;
        }
        return false;
    }
    template<class Rep,class Period>
    bool try_acquire(const std::chrono::duration<Rep,Period> & wait_time){
        std::unique_lock<std::mutex> lock(_mtx);
        bool ret = _cv.wait_for(lock,wait_time,std::bind(&Semaphore::wait,this));
        --_count;
        return ret;
    }
    template<class Clock, class Duration>
    bool try_acquire_until(const std::chrono::time_point<Clock, Duration>& abs_time){
        std::unique_lock<std::mutex> lock(_mtx);
        bool ret =  _cv.wait_until(lock,abs_time,std::bind(&Semaphore::wait,this));    
        --_count;
        return ret;
    } 
private:
    //内部计数器最大值
    static constexpr  std::ptrdiff_t max() noexcept { return  MaxValue; }
    bool wait(){
        return _count > 0;
    }


    std::mutex              _mtx;
    std::condition_variable _cv;
    std::ptrdiff_t          _count;

    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;
};

Semaphore<10> sem(1);

void worker(int id)
{
    sem.acquire();
    for(int i =0 ; i <100; ++i)
    {
        std::cout << std::this_thread::get_id() <<":"<< id <<","<< i << std::endl;
    }
    sem.release();

}

void test_Seamphore()
{
    std::thread thread[3]={
        std::thread(worker,1),
        std::thread(worker,2),
        std::thread(worker,3)
    };
    for(int i=0; i< 3;++i)
    {
        thread[i].join();
    }
}
int main()
{
    test_Seamphore();
    return 0;
}