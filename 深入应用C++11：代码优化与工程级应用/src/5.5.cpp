#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
using namespace std;

std::once_flag flag;

void work(){
    std::call_once(flag, []{ cout << "work" << endl; });
}

int main(){
    std::vector<std::thread> v;
    for(int i = 0; i < 10; i++){
        std::thread t(work);
        v.emplace_back(std::move(t)); // template <class... Args>  void emplace_back (Args&&... args);
    }

    for(auto& val : v){
        val.join();
    }

    return 0;
}