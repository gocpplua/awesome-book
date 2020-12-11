// 1.3.1 统一的初始化
#include<iostream>
using namespace std;

struct A
{
    int x;
    int y;
} a = {1, 2};

struct B
{
    int x;
    int y;
    B(){} // 手写了个构造函数，虽然什么都没填，但这构造函数已经不是编译器默认提供的了，所以不平凡，所以就不是 POD 类
};

class C
{
    int a;
};

class D
{
public:
    int a;
private:
    int b; // 所有的非静态成员需要同一个访问级别
};

class Foo
{
public:
    Foo(int){}
    Foo(int, int){}
    Foo func(void)
    {
        return {1,2}; // 这里如同返回一个Foo(int, int)
    }
private:
    Foo(const Foo&){}
};

int main()
{
    // POD 是 Plain Old Data 的缩写。Plain 代表它是一个普通类型，Old 代表它是旧的，与几十年前的 C 语言兼容
    // 需要两个特性：1、平凡 2、布局有序。 总结就是，能用 C 的 memcpy() 等函数进行操作的类、结构体就是 POD 类型的数据。
    cout << is_pod<A>::value << endl; //输出:1 关于POD可以参考文章<<C++11新特性之POD类型>>：https://blog.csdn.net/Jxianxu/article/details/80524526
    cout << is_pod<B>::value << endl; //输出:0 关于POD可以参考文章<<什么是 POD 数据类型？>>：https://zhuanlan.zhihu.com/p/45545035
    cout << is_pod<C>::value << endl; //输出:1 
    cout << is_pod<D>::value << endl; //输出:0

    // 统一的初始化:统一了各种对象的初始化方式，而且使得代码书写更加简单清晰
    Foo a1(123);
    // Foo a2 = 123; // error: 拷贝构造函数是私有的
    Foo a3 = {123}; // 同a1
    Foo a4{123};    // 同a1：{}的等号是否书写，对初始化没有影响
    int a5 = {123};
    int a6{123};
    int* arr = new int[3]{1,2,3}; //堆上动态分配的内存也可以初始化了
    return 0;
}