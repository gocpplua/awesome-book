// 2.1.2 ��ֵ�����Ż����ܣ��������
// �ο���<<�㲻֪���Ŀ�������ֵ���ƶ����캯��>>:https://blog.csdn.net/wk_bjut_edu_cn/article/details/79148717
// ���⣺�ƶ�������Ӧ�׳��κ��쳣  
// �𰸣��ƶ�����ͨ���������ڴ棬��˲����׳��쳣������дһ�����׳��쳣���ƶ�����ʱ ��
//  ����Ӧ��������֪ͨ��׼�⣬������⹤��������ͨ��ָ����noexcept����������https://blog.csdn.net/rest_in_peace/article/details/81483224
#include<iostream>
using namespace std;

class A{
public:
    A():m_ptr(new int(0)){
        cout << "construct" << endl;
    }
    ~A(){
        cout << "destruct" << endl;
        delete m_ptr;
    }
    A(const A& a)noexcept:m_ptr(new int(*a.m_ptr)){
        cout << "copy construct" << endl;
    }
    A(A&& a)noexcept:m_ptr(a.m_ptr){
        a.m_ptr = nullptr;
        cout << "move construct" << endl;
    }
private:
    int* m_ptr;
};

A getA(bool flag){
    A a;
    A b;
    if (flag)
    {
        return a;
    }
    return b; // ����ֵ��һ����ֵA&&����ô������ƶ����죬����������ƶ�����(ע�������������)����ô����ת��Ϊһ��const A&�����ԣ��ǵ���A�Ŀ������캯����
}

int main()
{
    A a = getA(false);
}