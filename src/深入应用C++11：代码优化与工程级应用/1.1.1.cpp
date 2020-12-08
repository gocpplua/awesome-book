#include<iostream>
#include <typeinfo>
using namespace std;

class Foo
{
private:
    /* data */
public:
    Foo(/* args */){}
    ~Foo(){}

public:
    // auto val1_ = 0; // error:non-static data member 不能用占位符 auto 进行 declared
    // static auto val2_ = 0; // error:无法推导“auto”类型(需要初始值设定项)
    static const auto var3_ = 0; // ok。 auto 仅能推导static const的整形或者枚举成员(因为其他静态类型在C++标准中无法进行就地初始化)
    static const auto var4_ = 'a';
    // static const auto var5_ = "a"; // error:"const char *const" 类型的成员不能包含类内初始值设定项
};

template<typename T>
struct Bar{};


int main()
{
    // 1.auto 关键字的新意义(C++98/03中，auto代表具有自动存储期的局部变量，C++11中用于类型推导)
    auto x = 5;
    const auto *v = &x, u = 6; // ok
    // const auto *v = &x, u = 6.0; // error:对于此实体“auto”类型是 "double"，但之前默示为 "int"
    //const auto u = 6, *v = &x; // ok 书中说会出错，实际测试没问题。 使用的编译器版本:g++.exe 8.1.0
    // auto i; // error:auto 不是一个实际类型声明，而是一个类型声明占位符，我们使用auto声明变量的时候必须马上初始化


    // 2.auto 的 推导规则：
    // A、当不声明为指针或者引用，auto推导结果和初始化表达式抛弃引用和cv限定符后类型一致(cv限定符就是const和volatile)
    // B、当声明为指针或者引用，auto推导结果将保留初始化表达式的cv属性(cv限定符就是const和volatile)
    auto* a = &x;
    auto b = &x;
    auto& c = x;
    auto d = c; // c 是一个int& 类型，此处auto会把引用类型抛弃，直接推导成原始类型int
    const auto e = x;
    auto f = e; // e 是一个 const int 类型，此处auto会把const属性抛弃，推导成non-const int
    const auto& g = x;
    auto& h = g;  // h 是 const int &类型，当auto 和 & 同时使用的时候，auto的推导会保留表达式的const属性
    // h = 1; // error:当auto 和 & 同时使用的时候，auto的推导会保留表达式的const属性
    f = 1; // ok:e 是一个 const int 类型，此处auto会把const属性抛弃，推导成non-const int
    cout << typeid(a).name() << " " << typeid(b).name() << " " << typeid(c).name() << " " << typeid(d).name() 
    << " " << typeid(e).name() << " " << typeid(f).name() << " " << typeid(g).name() << endl; // 输出: Pi Pi i i i i i

    // 3、auto限制
    // A、不能用于函数参数 B、auto不能用于非静态成员变量 C、不能定义数组 D、无法推导出模板参数
    // E、只能根据变量的初始化表达式推导出变量类型，如果想要根据某一个表达式得到类型，但不希望新变量和这个表达式具有相同的值，此时auto不适用，需要用decltype
    int arr[10] = {0};
    auto aa = arr; // ok: aa -> int*
    // auto rr[3] = {1,2,3}; // error:“auto”类型不能出现在顶级数组类型中 或者说是  aotp 不能定义数组
    // Bar<auto> bb; // error:无法推导出模板参数

    // 4.什么时候用auto
    // A、表达式类型太复杂的时候 B、类型无法人肉推导或者推导困难
    /*
    template<class T, class U>
    auto mul(T x, U y) // 我们并不知道x*y返回值，如果不用auto，旧需要多一个模板参数
    {
    
    return x*y;
    }
    */

    cout << " success" << endl;
    return 0;
}