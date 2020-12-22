#include<iostream>
#include<thread>
#include<atomic>
using namespace std;

struct Counter{
public:
    void increment(){
        ++val;
    }

    void decrement(){
        --val;
    }

    int get(){
        return val.load(); // load: Read contained value  store:Modify contained value
    }
private:
    std::atomic<int> val;
};

Counter g_counter;

void Increments()
{
	for (int i = 0; i < 10; ++i)
	{
		g_counter.increment();
	}
}

void Decrements()
{
	for (int i = 0; i < 5; ++i)
	{
		g_counter.decrement();
	}
}

int main()
{
    std::thread t1(Increments);
	std::thread t2(Decrements);

	t1.join();
	t2.join();
    cout << g_counter.get() << endl;
	return 0;   
}