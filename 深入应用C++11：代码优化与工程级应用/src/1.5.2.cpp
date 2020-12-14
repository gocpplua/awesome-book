// 1.5.2 可调用对象包装器 std::function
#include<iostream>
#include<functional>
using namespace std;

void func(void)
{
    cout << __FUNCTION__ << endl;
    return;
}

class Foo
{
    public:
        static int foo_func(int a)
        {
            cout << __FUNCTION__ << endl;
            return a;
        }
};

class Bar
{
    public:
        int operator()(int a)
        {
            cout << __FUNCTION__ << "(" << a << ")" << endl;
            return a;
        }
};



class A
{
public:
    A(const std::function<void()>& f):_callback(f){}
    void notify(){
        _callback();
    }
private:
    std::function<void()> _callback;
};

class funcA{
public:
    void operator()()
    {
        cout << "funcA:" << __FUNCTION__ << endl;
    }
};

int main()
{
    function<void(void)> fr1 = func;
    fr1();

    function<int(int)> fr2 = Foo::foo_func;
    fr2(123);

    Bar bar;
    fr2 = bar;
    fr2(11);

// 委托机制
    funcA fa;
    A a(fa);
    a.notify();

    return 0;
}

