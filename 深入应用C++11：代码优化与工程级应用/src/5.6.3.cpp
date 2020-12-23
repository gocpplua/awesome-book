// 异步操作(future/promise/package_task)
// 5.6.3 可调用对象的包装类:std::package_task
#include<iostream>
#include<functional>
#include<thread>
#include<future>
using namespace std;

int main(){
    std::packaged_task<int()> task([](){ return 7;});
    std::thread t(std::ref(task));
    std::future<int> f = task.get_future();
    auto r = f.get();
    cout << r << endl;
}