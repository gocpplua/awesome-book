// 2.1.1 &&������
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
	{ // ����һ�Σ�����copy���죬��������
		cout << "a1" << endl;
		A a1 = getA();
	}

	{
		// ����һ�Σ�һ��copy���죬��������
		cout << "a2" << endl;
		A&& a2 = getA();	
	}

	{
		// ����һ�Σ�һ��copy���죬�������� -- ͬa2
		cout << "a3" << endl;
		const A& a3 = getA();	// ok:������ֵ�����������������ͣ����Խ�����ֵ����ֵ��������ֵ��������ֵ!!!!!
	}

	{
		//A &a4 = getA(); // error:�ǳ�����ֵ����ֻ�ܽ�����ֵ
	}
	return 0;
}