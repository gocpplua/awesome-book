// 5.1.1 �̴߳���
// !!! VSCODE ʹ��mingw64 g++����ʧ�ܣ�error: 'thread' is not a member of 'std'����ʹ��cl.exe ����ɹ�����
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