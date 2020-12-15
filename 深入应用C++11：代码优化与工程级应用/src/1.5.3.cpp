// 1.5.3 std::bind 绑定器
#include<iostream>
#include<functional>
#include<string>
#include <algorithm>
using namespace std;

void call_when_even(int x, const std::function<void(int)>& f)
{
    if (!(x & 1))
    {
        f(x);
    }
}

void output(int x)
{
    cout << __FUNCTION__ << ":" << x << endl;
}

void output2(int x, int y)
{
    cout << __FUNCTION__ << ":" << x << "," << y << endl;
}

void output_add_2(int x)
{
    cout << __FUNCTION__ << ":" << x + 2 << endl;
}

class A
{
public:
    A(string name):name_(name){
        cout << __FUNCTION__ << endl;
    }
    ~A(){
        cout << __FUNCTION__ << endl;
    }
    A(const A& a):name_(a.name_), i_(a.i_){
        cout << __FUNCTION__ << endl;
    }

    A& operator=(const A& a){
        name_ = a.name_;
        i_ = a.i_;
        cout << __FUNCTION__ << endl;
        return *this;
    }

    void output(int x, int y)
    {
        cout << name_ << ":" << x << " " << " " << y << endl;
    }


    string name_;
    int i_ = 0;
};

int main()
{
    for(int i = 0; i < 10; i++)
    {
        call_when_even(i, output);
    }


    // bind
    {
        auto fr = std::bind(output, std::placeholders::_1); // td::placeholders::_1 是一个占位符，表示这个位置将在函数调用时，被传入的第一个参数所替换
        for(int i = 0; i < 10; i++)
        {
            call_when_even(i, fr);
        }        
    }

    {
        auto fr = std::bind(output_add_2, std::placeholders::_1);
        for(int i = 0; i < 10; i++)
        {
            call_when_even(i, fr);
        }        
    }

    std::bind(output2, 1, 2)();
    std::bind(output2, std::placeholders::_1, 2)(1,2);
    std::bind(output2, 2, std::placeholders::_1)(1);
    //std::bind(output2, 2, std::placeholders::_2)(1); // error: 调用时没有第二个参数
    std::bind(output2, 2, std::placeholders::_2)(1,2); // ok:第一个参数没吞没
    std::bind(output2, std::placeholders::_1, std::placeholders::_2)(1, 2);
    std::bind(output2, std::placeholders::_2, std::placeholders::_1)(1, 2);


    A a("a"); // 当使用std::bind绑定成员函数时，第一个参数是对象this指针,可以传值和传入引用
    cout << "function fr" << endl;
    std::function<void(int, int)> fr = std::bind(&A::output, &a, std::placeholders::_1, std::placeholders::_2);
    cout << "function fr1" << endl;
    std::function<void(int, int)> fr1 = std::bind(&A::output, a, std::placeholders::_1, std::placeholders::_2); // ！！！传值会导致两次构造
    cout << "fr" << endl;
    fr(1, 2);
    cout << "fr1" << endl;
    fr1(11, 22);

    // bind原理图释:https://www.cnblogs.com/xusd-null/p/3698969.html
    std::function<int&(void)> fr_i = std::bind(&A::i_, &a);
    fr_i() = 123;
    cout << "fr_i:" << a.i_ << endl;


    // 使用bind简化和增强 bind1st 和 bind2st 
    // 参考<<c++ bind1st 和 bind2nd的用法>>:https://www.cnblogs.com/renyuan/p/6216375.html
    int numbers[] = {10,20,30,40,50,10};
    int cx;
    cx = count_if (numbers, numbers+6, bind1st(equal_to<int>(),10) ); //将10 绑定为第一个参数，即 10 < value
    cout << "There are " << cx << " elements that are equal to 10.\n";

    cx = count_if ( numbers, numbers+5, bind2nd(less<int>(),0) ); //将0 绑定为第二个参数，即 即 value < 0
    cout << "There are " << cx << " negative elements.\n";

    // 统一使用bind, 那么我们就不关心到底用 bind1st 还是 bind2st 
    cx = count_if (numbers, numbers+6, bind(equal_to<int>(),10, std::placeholders::_1) );
     cout << "[bind]There are " << cx << " elements that are equal to 10.\n";

    cx = count_if ( numbers, numbers+5, bind(less<int>(), std::placeholders::_1,0) ); //将0 绑定为第二个参数，即 即 value < 0
    cout << "[bind]There are " << cx << " negative elements.\n";

    // 使用std::logical_and组合两个条件
    auto ff = std::bind(std::logical_and<bool>(), bind(greater<int>(), std::placeholders::_1, 5), bind(less_equal<int>(), std::placeholders::_1,10) );
    cx = count_if ( numbers, numbers+6, ff);
    cout << "[logical_and]There are " << cx << " elements.\n";
    return 0;
}