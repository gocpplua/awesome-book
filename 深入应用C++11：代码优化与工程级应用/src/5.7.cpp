// 5.7 线程异步操作函数async
#include<iostream>
#include<future>
#include<thread>
using namespace std;

int main()
{
    // async立即创建，deferred延时创建，直到调用future的get/wait
    auto f1 = std::async(std::launch::async, [](){
        return 8;
    });

    cout << f1.get() << endl;

    // 如果是deferred，那么主线程先等3s，然后执行f2.wait的时候，创建此线程函数，再等5秒后创建f3
    // 如果是async，那么主线程等3s 的同时此线程函数创建，等5秒后创建f3
     auto f2 = std::async(std::launch::deferred, [](){
         cout << "88" << endl;
         std::this_thread::sleep_for(std::chrono::seconds(5));
        return;
    });

    std::this_thread::sleep_for(std::chrono::seconds(3));
    f2.wait(); // 等待与当前std::future 对象相关联的共享状态的标志变为 ready。

     auto f3 = std::async(std::launch::async, [](){
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 8;
    });
    cout << "waiting...." << endl;
    std::future_status status;
    do
    {
        status = f3.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::ready)
        {
            cout << "ready...." << endl;
        }
        else if (status == std::future_status::deferred)
        {
            cout << "deferred...." << endl;
        }
        else if (status == std::future_status::timeout)
        {
            cout << "timeout...." << endl;
        }
        
    } while (status != std::future_status::ready);
    cout << "f3:" << f3.get() << endl;
}