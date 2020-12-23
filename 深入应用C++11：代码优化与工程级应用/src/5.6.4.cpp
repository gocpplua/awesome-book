// 异步操作(future/promise/package_task)
// 5.6.4 future/promise/package_task三者之间关系
#include<iostream>
#include<future>
#include<thread>
#include<vector>
using namespace std;

int func(int x){
    cout << __FUNCTION__ << endl;
    return x + 2;
}

int main(){
    std::packaged_task<int(int)> task(func);
    std::future<int> fut = task.get_future();
    cout << "before create thread" << endl;
    std::thread t(std::move(task), 2); // 线程创建并运行函数func
    cout << "after create thread" << endl;
    t.detach();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    int val = fut.get();
    cout << val << endl;

    // std::future是不能复制的，不能放在容器中，需要使用shared_future
    vector<std::shared_future<int>> v;
    std::shared_future<int> f = std::async(std::launch::async, [](int a, int b)->int{ return a + b;}, 2, 3);
    auto f1 = std::async(std::launch::async, [](int a, int b)->int{return a + b; }, 2, 3); // std::async返回std::future<T>
    v.push_back(f);
    // v.push_back(f1); // error:std::async返回std::future<T>
    v.push_back(f1.share()); // ok:将share()函数std::future<int>转换为std::shared_future<int>

    for(const auto& valShare : v){
        cout << valShare.get() << endl;
    }
}