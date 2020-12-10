// 1.3.3 防止类型收窄(不同编译器表现不一定相同)
#include<iostream>
using namespace std;

int main()
{
    int a = 1.1; // ok
    // int b = {1.1}; // error

    float fa = 1e40;
    // float fb = {1e40}; // errror

    float fc = (unsigned long long)-1;
    //float fd = {(unsigned long long)-1};// errror
    float fe = (unsigned long long)1;
    float ff = {(unsigned long long)1};

    const int x = 1024, y = 1;
    int yy = 1;
    char c = x; // warning [-Woverflow]
    // char d = {x};// error 
    char e = y; 
    char f = {y}; // 因为y是const类型，所有没有报错
    // char g = {yy};// error
    return 0;
}