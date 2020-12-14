// 1.4.1 for循环的新用法
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void func1()
{
    std::vector<int> arr{1,2,3,4,5};
    for(auto it = arr.begin(); it != arr.end(); ++it)
    {
        cout << __FUNCTION__ << ":"<< *it << endl;
    }
}


void do_count(int n)
{
    cout << __FUNCTION__ << ":"<< n << endl;
}
void func2()
{
    std::vector<int> arr{1,2,3,4,5};
    for_each(arr.begin(), arr.end(), do_count); 
}


template<typename T>
void do_countT(T n)
{
    cout << __FUNCTION__ << ":"<< n << endl;
}

void func3()
{
    std::vector<int> arr{1,2,3,4,5};
    for_each(arr.begin(), arr.end(), do_countT<int>); 
}

void func4()
{
    std::vector<int> arr{1,2,3,4,5};
    for(auto n : arr) // 基于范围的for循环，n表示arr中的一个元素，auto让编译器自动推导出n类型
    {
        cout << __FUNCTION__ << ":"<< n << endl;
    }
}

int main()
{
    func1();
    func2();
    func3();
    func4();
    return 0;
}