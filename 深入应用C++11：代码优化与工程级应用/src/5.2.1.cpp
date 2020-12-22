#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;

std::mutex g_lock;

void func(int i){   
    g_lock.lock();
    cout << "enter threadid:" << std::this_thread::get_id() << " i = " << i << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "leave threadid:" << std::this_thread::get_id() << endl;
    g_lock.unlock();
}

void func1(int i){   
    std::lock_guard<std::mutex> lock(g_lock); // 使用std::lock_guard 简化lock、unlock的写法
    cout << "enter threadid:" << std::this_thread::get_id() << " i = " << i << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "leave threadid:" << std::this_thread::get_id() << endl;
}
int main()
{
    // 三个线程t1,t2,t3的打印顺序不一定
    std::thread t1(func,1);
    std::thread t2(func,2);
    std::thread t3(func,3);
    t1.join();
    t2.join();
    t3.join();
    printf("=========================\n");
    std::thread t11(func1,1);
    std::thread t22(func1,2);
    std::thread t33(func1,3);
    t11.join();
    t22.join();
    t33.join();
}