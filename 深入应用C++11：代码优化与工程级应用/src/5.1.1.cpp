// 5.1.1 线程创建
// !!! VSCODE 使用mingw64 g++编译失败（error: 'thread' is not a member of 'std'），使用cl.exe 编译成功！！
#include<iostream>
#include<thread>
#include<future>
using namespace std;

void func()
{
    printf("%s\n", __FUNCTION__);
}

void func1(int i)
{
    printf("%s:%d\n", __FUNCTION__, i);
}

void func2(int i)
{
    printf("%s:%d\n", __FUNCTION__, i);
}

std::vector<std::shared_ptr<std::thread>> g_list;
void funcg()
{
    printf("%s\n", __FUNCTION__);
}
void createthread(){
    g_list.push_back(std::make_shared<std::thread>(funcg));
}

int main()
{
    std::thread t(func);
    t.join(); // 等待运行于线程对象的func函数执行完成

    std::thread t1(func1, 1);
    t1.detach(); // 线程和线程对象/线程函数分离，可能main函数执行完了，但是线程函数还没有执行，所以有可能func1没有打印

    std::thread t2(func2, 2);
    printf("%s\n", "========craete t2========");
    std::thread t3(std::move(t2)); // t3 is now running func2(). t2 is no longer a thread

    // 此处发现t2 not joinable，当我们执行t2.join()，主线程直接卡住了！！！！！
    if (t2.joinable()){
        printf("t2 joinable\n");
    }
    else{
        printf("t2 not joinable\n"); 
    }
    

    printf("%s\n", "========create t3========"); // 这里使用cout可能导致打印错乱，因为printf是线程安全的，也就是自己做了线程同步的处理,但是cout不是线程安全的，要靠自己去线程同步，比较麻烦 。
    //t2.join(); // !!! 主线程卡住，下述打印不会执行
    printf("%s\n", "=========t2 join=========");
    t3.join();
    printf("%s\n", "=========t3 join=========");

    createthread();
    for(const auto& val : g_list){
        val->join();
    }

    return 0;
}