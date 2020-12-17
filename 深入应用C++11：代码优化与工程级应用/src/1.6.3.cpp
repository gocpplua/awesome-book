// 1.6.3 在需要的时间和地点实现闭包，使程序更加灵活
#include<iostream>
#include<functional>
#include<algorithm>
using namespace std;

int main()
{
    // 1.5.3 代码
    int numbers[] = {10,20,30,40,50,10};
    auto ff = std::bind(std::logical_and<bool>(), bind(greater<int>(), std::placeholders::_1, 5), bind(less_equal<int>(), std::placeholders::_1,10) );
    int cx = count_if ( numbers, numbers+6, ff);
    cout << "[logical_and]There are " << cx << " elements.\n";

    // 下述代码是对上述代码的简化：使用lambda表达式
    int cy = count_if(numbers, numbers + 6, [](int val){ return val > 5 && val <= 10; });
    cout << "[lambda]There are " << cy << " elements.\n";
}

