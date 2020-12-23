#include<iostream>
#include<chrono>
using namespace std;
using HZ30 = std::chrono::duration<double, std::ratio<1, 30>>;
using HZ60 = std::chrono::duration<double, std::ratio<1, 60>>;
int main()
{
    std::chrono::seconds sec{3};
    std::chrono::milliseconds ms{3};
    std::chrono::microseconds us = 2 * ms;
    HZ30 hz30{sec};
    HZ60 hz60{hz30};
    HZ60 hz120{22222};
    cout << ms.count() << endl; // 输出:3
    cout << us.count() << endl; // 输出:6000
    cout << hz30.count() << endl; // 输出:90 -- 初始值单位和变量单位 都是duration的时候可以计算出count
    cout << hz60.count() << endl; // 输出:180
    cout << hz120.count() << endl; // 输出:22222

    std::chrono::duration<double, std::ratio<9, 7>> d1{3};
    std::chrono::duration<double, std::ratio<6, 5>> d2{1};
    auto d3 = d1 - d2; // duration<double, std::ration<3, 35>> 分子的最大公约数，分母的最小公倍数到当作duration
    cout << d3.count() << endl; //输出:31

    std::chrono::seconds secX{120};
    cout << std::chrono::duration_cast<chrono::minutes>(secX).count() << endl; // 使用 std::chrono::duration_cast 进行时钟周期的转换
    return 0;
}