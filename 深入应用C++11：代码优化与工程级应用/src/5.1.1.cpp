// 5.1.1 线程创建
// !!! VSCODE 使用mingw64 g++编译失败（error: 'thread' is not a member of 'std'），使用cl.exe 编译成功！！
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