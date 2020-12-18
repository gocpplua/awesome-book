#include<iostream>
#include<string>
using namespace std;

void printT(int& t){
    cout << "lvalue" << endl;
}

template<typename T>
void printT(T&& t){
    cout << "rvalue" << endl;
}

template<typename T>
void TestForward(T&& v){
    printT(v);
    printT(std::forward<T>(v));
    printT(std::move(v));
    cout << std::is_lvalue_reference<T>::value << endl;
}

void Test()
{
    TestForward(1); // 入参:右值   l - r - r
    int x = 1;
    TestForward(x); // 入参:左值   l - l - r
    TestForward(std::forward<int>(x)); //入参：右值 l - r - r
}


// 万能函数包裹器
template<class Function, class ...Args>
auto FuncWrapper(Function&& f, Args&& ...args){
    return f(std::forward<Args>(args)...);
}

void test0(){
    cout << "0" << endl;
}
int test1(){
    cout << "1" << endl;
    return 1;
}
int test2(int x){
    cout << x << endl;
    return x;
}
string test3(string s1, string s2){
    cout << s1 + s2 << endl;
    return s1 + s2;
}
void Test1(){
    FuncWrapper(test0);
    FuncWrapper(test1);
    FuncWrapper(test2, 1);
    FuncWrapper(test3, "aa", "bb");
}

int main(){
    Test(); // l - r - r   l - l - r  l - r - r  // 如果T& t，改为const T& t，输出都是r ????

    Test1();

    return 0;
}



