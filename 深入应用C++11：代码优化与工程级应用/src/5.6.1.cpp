// 异步操作(future/promise/package_task)
// 5.6.1 获取线程函数返回值的类:std::future
#include<iostream>
#include<future>
using namespace std;

bool is_prime(int x){
    for(int i = 2; i < x; i++){
        if (x % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    std::future<bool> fut = std::async(is_prime, INT_MAX);
    std::future_status status;
    do
    {
        status = fut.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::deferred) // 异步操作还没开始
        {
            cout << "deferred" << endl;
        }
        else if (status == std::future_status::timeout) // 异步操作超时，可以理解为开始了但是没有结束
        {
           cout << "timeout" << endl;
        }
        else if (status == std::future_status::ready)// 异步操作已经完成
        {
            cout << "ready" << endl;
        }
    } while (status != std::future_status::ready);
}