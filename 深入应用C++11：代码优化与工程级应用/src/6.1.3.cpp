#include<iostream>
#include<chrono>
#include <iomanip>      // std::put_time
using namespace std;

int main(){
    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now(); //代表真实世界的挂钟时间，具体时间依赖系统
    std::time_t timeT1 = std::chrono::system_clock::to_time_t(t1);
    cout << std::put_time(std::localtime(&timeT1), "%Y-%m-%d %X") << endl;
    std::chrono::system_clock::time_point t2 = std::chrono::system_clock::now();
    std::cout << (t2 - t1).count() << " tick count" << endl;
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " micro" << endl;

    cout << "===========" << endl;

    std::chrono::steady_clock::time_point tt1 = std::chrono::steady_clock::now(); //不能被调整的时钟，并不一定代表真实时间，保证先后调用now()得到的时间不会递减
    cout << "hello world" << endl;
    std::chrono::steady_clock::time_point tt2 = std::chrono::steady_clock::now();
    std::cout << (tt2 - tt1).count() << " tick count" << endl;
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tt2 - tt1).count() << " micro" << endl;
    return 0;
}