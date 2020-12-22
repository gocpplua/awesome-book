#include<iostream>
#include<thread>
#include <sstream>
using namespace std;
void func()
{
    std::this_thread::sleep_for(std::chrono::seconds(10));
    cout << "time out" << endl;
}

// C++11线程库std::thread中提取线程id
// 它重载了<<输出运算符，这个还是std::thread::id的一个友元函数,用stringstream把_M_thread拿到。当然你可以用std::cout直接输出
typedef unsigned long long ULL;
std::string getThreadIdOfString(const std::thread::id & id)
{
    std::stringstream sin; // #include <sstream>
    sin << id;
    return sin.str();
}

ULL getThreadIdOfULL(const std::thread::id & id)
{
    return std::stoull(getThreadIdOfString(id));
}

int main()
{
    std::thread t(func);
    cout << t.get_id() << endl;
    t.join();
    cout << std::thread::hardware_concurrency() << endl;
    cout << getThreadIdOfULL(t.get_id()) << endl;
    return 0;
}