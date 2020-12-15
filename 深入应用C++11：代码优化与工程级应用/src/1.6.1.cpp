// 1.6.1 lambda 表达式的概念和基本用法

//Lambda表达式完整的声明格式如下：[capture list] (params list) mutable exception-> return type { function body }
// 各项具体含义如下:
// capture list：捕获外部变量列表
// params list：形参列表
// mutable指示符：用来说用是否可以修改捕获的变量
// exception：异常设定
// return type：返回类型
// function body：函数体
#include<iostream>
#include<functional>
using namespace std;

auto f = [](int a) -> int {return a;};
auto f1 = [](int a){return a;}; // 返回值类型比较明显，这个时候编译器就会进行自动推到返回值，那么C++11允许省略lambda表达式的返回值定义
// auto x2 = [](){return {1,2};}; // initializer list 不能进行自动推导
auto f2 = []{return 1;}; // lambda表达式 没有参数列表时，可以省略参数列表
int main()
{
    int a = 0;
    int b = 1;
    // auto f4 = [=]{ return a++;}; //error:increment of read-only variable 'a'
    auto f8 = [=]() mutable {return a++;}; // 使用mutable来修改按值获取的外部变量，同时我们使用了mutable，那么即使参数列表为空，也是需要写明参数列表
    cout<< f8() << " " << f8() <<endl; // 输出：0 1

    std::function<int(int)> f9 = [](int a){return a;};
    std::function<int(int)> f10 = std::bind([](int a, int b){cout << __FUNCTION__ << ":" << a << " " << b <<endl; return b;}, 12, 123);
    cout<< f10(1) << endl; // 输出：operator():12 123 -- 因为lambda表达式可以认为是一个带有operator()的类，同时function(可调用对象包装器)中是：int(int)，所有需要一个int参数。 输出12 123是，调用lambda表达式有默认参数12 123。

    using func_t = int(*)(int);
    func_t f11 = [](int a){return a;};     //ok:不存在捕获类型的表达式可以转换为函数指针
    // func_t f12 = [=](int a){return a;}; //error:存在捕获类型的表达式不能转换为函数指针
    return 0;
}
