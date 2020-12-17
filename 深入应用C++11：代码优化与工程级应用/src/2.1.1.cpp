// 2.1.1 &&的特性
#include<iostream>
using namespace std;

int construct = 0;
int copyconstruct = 0;
int destruct = 0;

class A
{
public:
	A() {
		cout << "construct:" << ++construct << endl;
	}
	A(const A& a) {
		cout << "copyconstruct:" << ++copyconstruct << endl;
	}
	~A() {
		cout << "destruct:" << ++destruct << endl;
	}

private:

};

A getA()
{
	return A();
}

int main()
{
	{ // 构造一次，两次copy构造，三次析构
		cout << "a1" << endl;
		A a1 = getA();
	}

	{
		// 构造一次，一次copy构造，两次析构
		cout << "a2" << endl;
		A&& a2 = getA();	
	}

	{
		// 构造一次，一次copy构造，两次析构 -- 同a2
		cout << "a3" << endl;
		const A& a3 = getA();	// ok:常量左值引用是万能引用类型，可以接受左值，右值，常量左值，常量右值!!!!!
	}

	{
		//A &a4 = getA(); // error:非常量左值引用只能接受左值
	}
	return 0;
}