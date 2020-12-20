// 5.1.1 线程创建
#include<iostream>
#include<thread>
#include<future>
using namespace std;

void func()
{
    cout << __FUNCTION__ << endl;
}

int main()
{
    std::thread t(func);
    t.join();
    return 0;
}