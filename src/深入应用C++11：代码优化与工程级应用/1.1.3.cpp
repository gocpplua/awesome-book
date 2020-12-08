// 返回类型后置语法
#include<iostream>
using namespace std;

// C++11 引入了一个叫做尾返回类型（trailing return type），利用 auto 关键字将返回类型后置
template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u) // decltype推到表达式类型是在编译期完成的，所以这里虽然有两个t + u,实际上只会执行一次
{
    return t + u;
}

// C++14 开始是可以直接让普通函数具备返回值推导，因此下面的写法变得合法
template <typename T, typename U>
auto add2(T t, U u) // C++14 
{
    return t + u;
}

int main()
{
    return add(1, 2);
}
