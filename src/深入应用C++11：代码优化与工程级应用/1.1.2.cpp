#include<iostream>
#include<vector>
using namespace std;
// Q:auto 和 decltype区别
// Q:Where is the definition of `top-level cv-qualifiers` in the C++11 Standard?
// A:链接609的答案:http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4458.html#609
//   In this International Standard, the notation cv (or cv1, cv2, etc.), 
//   used in the description of types, represents an arbitrary set of cv-qualifiers, i.e., 
//   one of {const}, {volatile}, {const, volatile}, or the empty set. 
//   For a type cv T, the top-level cv-qualifiers of that type are those denoted by cv. 
//   [Example: The type corresponding to the type-id “const int&” has no top-level cv-qualifiers. 
//   The type corresponding to the type-id “volatile int * const” has the top-level cv-qualifier const. 
//   For a class type C, the type corresponding to the type-id “void (C::* volatile)(int) const” has the top-level cv-qualifier volatile. —end example]

class Foo
{
public:
    static const int Number = 0;
    int x;
};
const int func_cint(){
    return 0;
}

const Foo func_cfoo(){
    return Foo();
}

int main()
{
    // 1、获知表达式类型
    int x = 0;
    decltype(x) y = 1;
    decltype(x + y) z = 0;

    const int& i = x; // typeid输出:i,而不是ki，因为typeid忽略顶级const限定符
    decltype(i) j = y;
    // j = 1; // error:const int &j表达式必须是可修改的左值, 保留了表达式的引用和const限定符
    const decltype(z) *p = &z; // typeid输出：PKi,在指针情况下，所指的const资格不是顶级资格。它不会在typeid下丢失
    decltype(z) *pi = &z;
    decltype(pi) *pp = &pi;

    // FPK1AidPKiRKdE  F表示参数为函数,P为指针,R为引用,K为const,那么PK1A表示返回值为const A*,
    // id表示函数参数为int,double,PKi表示参数为const int*,RKd表示参数为const double& E表示结束
     cout << typeid(x).name() << " " << typeid(y).name() << " " << typeid(z).name() << " " << typeid(i).name() 
    << " " << typeid(j).name() << " " << typeid(p).name() << " " << typeid(pi).name() << " " << typeid(pp).name() << endl; // 输出: i i i i i PKi Pi PPi

    // 2、decltype的推导规则
    // A、推导规则1：exp是标识符、类访问表达式，decltype(exp)和exp的类型一致
    // B、推导规则2: exp是函数调用，decltype(exp)和返回值的类型一致
    // C、推导规则3：其他情况，若exp是一个左值，则decltype(exp)是exp类型的左值引用，否则和exp类型一致
    // -------------- 推导规则1 -------------------------------
    int n = 0;
    volatile const int &xx = n;

    decltype(n) a = n;
    decltype(xx) b = n; // onst volatile int &b
    decltype(Foo::Number) c = 0; // const int c = 0

    Foo foo;
    decltype(foo.x) d = 0;

    // -------------- 推导规则2 -------------------------------
    decltype(func_cint()) c2 = 0; // //int c2 : 函数返回int是纯右值，对于纯右值而言，只有类类型可以携带cv限定符，此外一般忽略cv限定。
    decltype(func_cfoo()) c3 = Foo(); // const Foo c3

    // -------------- 推导规则3 -------------------------------
    const Foo fooo = Foo();
    decltype(foo.x) aa = 0; // aa -> int
    decltype((foo.x)) bb = a; // bb -> const int&

    int n = 0, m = 0;
    decltype(n + m) cc = 0; // cc -> int  n+m返回是右值
    decltype((n+=m)) dd = cc; // dd -> int& n+=m返回是左值

    // 3、decltype的实际应用
    // A、模板编程 B、通过变量表达式抽取变量类型
    vector<int> v;
    decltype(v)::value_type i = 0;
    return 0;
}