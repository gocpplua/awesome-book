// 1.2.3 函数模板的默认模板参数
#include<iostream>
using namespace std;

// C++98/03不支持默认模板参数
// 模板参数的填充顺序从右往左
template<typename R = int, typename U>
R func(U val)
{
    return val;
}

template<typename R, typename U = int, typename P = long>
R func1(U val)
{
    cout << "(func1)R:" << typeid(R).name() << " U:" << typeid(U).name() << " P:" << typeid(P).name() << endl;
    return (P)val;
}

template<typename T>
struct identity
{
    typedef T type;
};

template<typename T = int>
// void func2(T val, T = 0) // error：没懂？？？？
void func2(typename identity<T>::type val, T = 0)
{
    cout << "(func2)R:" << typeid(T).name() << endl;
    return;
}

int main()
{
    auto a = func(123); // a -> int
    auto b = func<long>(123);// 重点:b -> long(这里的理解方式:因为参数没有指定全，所以会进行从右到左进行参数类型推导。先是推导U，由于123是int，那么U就被推导成int，剩下一个R类型，刚刚可以用指定的long类型替换。
    auto c = func(123.1);// c -> int
    auto d = func<int, long>(123);// d -> int
    cout << typeid(a).name() << " "<< typeid(b).name() << " " << typeid(c).name()<< " " << typeid(d).name() << endl; // i l i

    auto aa = func1<int>(123);
    auto bb = func1<long>(123);
    auto cc = func1<int>(123.1);
    auto dd = func1<int, long>(123);
    cout << typeid(aa).name() << " "<< typeid(bb).name() << " " << typeid(cc).name()<< " " << typeid(dd).name() << endl; // i l i

    func2(1,2.0);
    return 0;
}