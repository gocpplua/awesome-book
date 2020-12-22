// 参考资料:https://www.cnblogs.com/haippy/p/3252041.html
#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<list>
#include<condition_variable>
using namespace std;

template<typename T>
class simpleSyncQueue{
public:
    simpleSyncQueue(int maxSize):m_maxSize(maxSize){}
    void put(const T& x){
        printf("put\n");
        for(int i = 0; i < 1000; i++);
        std::lock_guard<std::mutex> lock(m_mutex);
        while (IsFull())
        {
            cout << "is full" << endl;

            // 当前线程调用 wait() 后将被阻塞(此时当前线程应该获得了锁(m_mutex)),直到另外某个线程调用 notify_* 唤醒了当前线程。
            // 在线程被阻塞时，该函数会自动调用 m_mutex.unlock() 释放锁，使得其他被阻塞在锁竞争上的线程得以继续执行。另外，一旦当前线程获得通知(notified，
            // 通常是另外某个线程调用 notify_* 唤醒了当前线程)，wait() 函数也是自动调用 m_mutex.lock()，使得 m_mutex 的状态和 wait 函数被调用时相同。
            m_notFull.wait(m_mutex); 
        }

        // 下述代码，同while()
        // m_notFull.wait(m_mutex, [this]{ return !IsFull() }); // 条件判断为真，重新获取mutex，然后结束wait，继续执行。 不满足条件判断，就释放mutex，然后江线程置为waiting状态，继续等待

        m_queue.push_back(x);
        m_notEmpty.notify_one();
        printf("put ok\n");
    }

    void take(T& x){
        printf("take\n");
        std::lock_guard<std::mutex> lock(m_mutex);
        /*while (IsEmpty())
        {
            cout << "is empty" << endl;
            m_notEmpty.wait(m_mutex);
        }*/

        m_notEmpty.wait(m_mutex, [this]{ return !IsEmpty(); });
        x = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
        printf("take ok\n");
    }

private:
    bool IsEmpty(){
        return m_queue.empty();
    }

    bool IsFull(){
        return m_queue.size() == m_maxSize;
    }
private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable_any m_notEmpty;
    std::condition_variable_any m_notFull;
    int m_maxSize;
};

simpleSyncQueue<int> q(10);

void put(){
    for(int i = 0; i < 10; i++){
        q.put(1);
    }
}

void take(){
    int i = 0;
    for(int i = 0; i < 10; i++){
        q.take(i);
    }
}

int main(){
    
    std::thread t1(put);
    std::thread t2(take);
    t1.join();
    t2.join();
    return 0;
}