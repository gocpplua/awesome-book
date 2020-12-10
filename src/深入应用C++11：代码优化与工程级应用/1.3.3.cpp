// 1.3.3 初始化列表
#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;

class FooInt
{
    public:
        FooInt(std::initializer_list<int>){}
};

class FooVector
{
    std::vector<int> content_;
public:
    FooVector(std::initializer_list<int> list)
    {
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            content_.push_back(*it);
        }
    }
};

class FooMap
{
    std::map<int, int> content_;
    using pair_t = std::map<int, int>::value_type; // typedef pair<const Key, T> value_type;
public:
    FooMap(std::initializer_list<pair_t> list)
    {
        for(auto it = list.begin(); it != list.end(); ++it)
        {
            content_.insert(*it);
        }
        
    }
};

std::initializer_list<int> funcList()
{
    int a = 1, b = 2;
    return {a , b};
}

std::vector<int> funcVec()
{
    int a = 1, b = 2;
    return {a , b};
}

int main()
{
    // 1.任意长度的初始化列表(initializer_list)
    FooInt foo{1,2,3,4,5}; // 使用 initializer_list 来接受任意长度的初始化列表
    FooVector fooVector{1,2,3,4,5};
    FooMap fooMap{{1,2}, {2,3}};
    
    // 2.initializer_list的一些细节
    // A、它是一个轻量级的容器类型，内部定义了iterator等容器必须的概念 B、接受的元素类型必须是相同的 C、有三个接口：size(),begin(),end() D、只能被整体初始化或赋值
    std::initializer_list<int> list;
    size_t n = list.size(); // n = 0
    list = {1, 2, 3, 4, 5};
    n = list.size();// n = 5 整体进行初始化或赋值
    list = {3, 1, 2, 4};
    n = list.size();// n = 4 整体进行初始化或赋值

    // initializer_list的内部并不负责保存初始化列表元素的拷贝，仅仅是存储了列表中元素的引用而已
    // 我们应该使用真正的容器或者具有转移/拷贝语义的物件来替代initializer_list返回需要的结果
    std::initializer_list<int> list1 = funcList();
    std::vector<int> list2 = funcVec();
    for (auto &&i : list1)
    {
        cout << "list1:" << i << endl; // 输出的值不一定
    }
    for (auto &&i : list2)
    {
        cout << "list2:" << i << endl; // 输出1，2
    }
}