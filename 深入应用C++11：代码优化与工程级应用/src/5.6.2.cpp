// 异步操作(future/promise/package_task)
// 5.6.2 协助线程赋值的类:std::promise
#include<iostream>
#include<functional>
#include<thread>
#include<future>
using namespace std;

void print_int(std::future<int>& fut){
    printf("enter:%s\n", __FUNCTION__);
    int x = fut.get();
    printf("value x:%d\n", x);

    //int y = fut.get();
    //printf("value y:%d\n", y);

    printf("leave:%s\n", __FUNCTION__);
}

int main(){
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::thread th1(print_int, std::ref(fut)); // // send future to new thread - <<C++11 的 std::ref 用法>>:https://murphypei.github.io/blog/2019/04/cpp-std-ref
    std::this_thread::sleep_for(std::chrono::seconds(2));
    prom.set_value(10); // // fulfill promise(synchronizes with getting the future)
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // prom.set_value(11);  // promise::set_value()只能用于设置一次值.如果多次调用,std::future_error则抛出a.
    th1.join();
    return 0;
}

