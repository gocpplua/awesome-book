#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;

std::timed_mutex tmutex;

void work(){
    while (true)
    {
        if(tmutex.try_lock_for(std::chrono::milliseconds(1000))){
            // 获取到
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
            std::cout << std::this_thread::get_id() << " not time out" << endl;
            tmutex.unlock(); // 这个unlock一定要加上，否则线程就会死锁
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << std::this_thread::get_id() << " time out" << endl;
        }   
    }
}

int main(){
    std::thread t1(work);
    std::thread t2(work);
    t1.join();
    t2.join();
}