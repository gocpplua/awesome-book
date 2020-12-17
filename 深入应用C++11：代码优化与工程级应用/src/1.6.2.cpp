// 1.6.2 声明式的编程风格，简洁的代码
#include<iostream>
#include<functional>
#include<algorithm>
#include<vector>
using namespace std;

class CountEven
{
    int &count_;
public:
    CountEven(int& count):count_(count){
        cout << __FUNCTION__ << endl;
    }

    void operator()(int val)
    {
        if (!(val & 1))
        {
            cout << __FUNCTION__ << endl;
            ++count_;
        }
    }
};

int main()
{
    std::vector<int> v{1, 2, 3, 4};
    int even_count = 0;
    for_each(v.begin(), v.end(), CountEven(even_count));
    cout << "[1]the number of even is:" << even_count << endl;

    int even_count1 = 0;
    CountEven e(even_count1) ;
    for_each(v.begin(), v.end(), e);
    cout << "[1]the number of even is:" << even_count << endl;
}