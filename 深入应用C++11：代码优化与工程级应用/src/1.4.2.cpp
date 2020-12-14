// 1.4.2 基于范围的for循环使用细节
#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;

using mmType = std::map<std::string, int>;
std::vector<int> arr{1, 2, 3};
std::vector<int>& get_range(void)
{
    cout << "get_range ->:" << endl;
    return arr;
}

int main()
{
     mmType mm = {
        {"1", 1}, {"2", 2}, {"3", 3}
    };
    cout << typeid(mmType::value_type).name() << endl; // 每一个容器，我们在cplusplus中都是可以找到对一个的value_type的

    for(auto& val : mm) // 知识点1:auto 自动推导出来的类型是容器中的value_type
    {
        cout << val.first << " -> " << val.second << endl; 
    }


    // 使用基于范围的for循环时，还需要注意容器本身的一些约束
    std::set<int> ss = {1, 2, 3};
    for (auto& val : ss)
    {
        //cout << val++ << endl; // error:std::set内部元素是readonly的
    }
    
    // 输出 1 2 3:get_range()只被调用一次。 对于基于范围的for循环， 冒号后面的表达式只会执行一次
    for (auto val : get_range())
    {
        cout << val << endl;
    }
    
    // 输出的值乱七八糟的，这是因为基于for循环其实是for循环的语法糖，同普通for循环一样，在迭代器修改的时候，会引起迭代器失效
    cout << "modify1:" << endl;
    std::vector<int> arrVec{1, 2, 3, 4};
    for (auto val : arrVec)
    {
        cout << val << endl;
        arrVec.push_back(0);
    }
     // 上述代码等价于下述代码
     cout << "modify2:" << endl;
     std::vector<int> _range{1, 2, 3, 4};
     for(auto __begin = _range.begin(), __end = _range.end(); __begin !=__end; ++__begin)
     {
         cout << *__begin << endl;
        _range.push_back(0);
     }

    return 0;
}