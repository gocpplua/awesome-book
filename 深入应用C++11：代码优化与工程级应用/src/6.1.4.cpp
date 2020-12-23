#include<iostream>
#include<chrono>
using namespace std;
class Timer{
public:
    Timer():m_begin(std::chrono::high_resolution_clock::now()){}
    void reset(){
        m_begin = std::chrono::high_resolution_clock::now();
    }

    int64_t elapsed_nano() const{
        return elapsed<std::chrono::nanoseconds>();
    }

    int64_t elapsed_micro() const{
        return elapsed<std::chrono::microseconds>();
    }
private:
    template<typename Duration=std::chrono::milliseconds>
    int64_t elapsed() const{
        return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now() - m_begin).count();
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
};

int main()
{
    Timer t;
    cout << "Timer" << endl;
    cout << t.elapsed_micro() << " micro" << endl;
    cout << t.elapsed_nano() << " nano" << endl;
    return 0;
}