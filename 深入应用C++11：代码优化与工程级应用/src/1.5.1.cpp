// 1.5.1 可调用对象
#include<iostream>
using namespace std;

// 可调用对象的定义:
// A、是一个函数指针
// B、是一个具有operator()成员函数的类对象(仿函数)
// C、是一个可被转换为函数指针的类对象
// D、是一个类成员(函数)指针

// A、是一个函数指针
void func(){
    cout << "func()" << endl;
}

// B、是一个具有operator()成员函数的类对象(仿函数)
struct Foo{
    void operator()(void)    {
        cout << "Foo operator()" << endl;
    }
};

// C、是一个可被转换为函数指针的类对象
struct Bar{
    using fr_t = void(*)(int);
    static void func(int)    {
        cout << "Bar func" << endl;
    }

    operator fr_t() {
        cout << "Bar fr_t" << endl;
        return func;
    }
};

struct Bar2{
    static void func(int)    {
        cout << "Bar2 func" << endl;
    }

    void operator()(int a) {
        cout << "Bar2 fr_t" << endl;
        func(a);
    }
};

// D、是一个类成员(函数)指针
struct A{
    int a_;

    void mem_func(void)    {
        cout << "A mem_func" << endl;
    }
};

int main(){
    // A、是一个函数指针
    void(*func_ptr)(void) = &func;
    func_ptr();

    // B、是一个具有operator()成员函数的类对象(仿函数)
    Foo foo;
    foo();

    // C、是一个可被转换为函数指针的类对象
    Bar bar;
    bar; // 没有任何输出
    bar(1); // 这里用一个(),而不是两个，我的理解：bar这里看成一个函数指针bar.operator(),然后加上(int)，就是调用：bar.operator()(int)
    bar.operator Bar::fr_t()(1);

    Bar2 bar2;
    bar2(1);
    
    void (A::*mem_func_ptr)(void) = &A::mem_func; // D、是一个类成员(函数)指针
    int A::*mem_obj_ptr = &A::a_;                 // 或者是 类成员指针
    A aa;
    (aa.*mem_func_ptr)();
    aa.*mem_obj_ptr = 123;

    return 0;
}