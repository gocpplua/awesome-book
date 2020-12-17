// 2.1.2 ��ֵ�����Ż����ܣ��������
// �ο���<<�㲻֪���Ŀ�������ֵ���ƶ����캯��>>:https://blog.csdn.net/wk_bjut_edu_cn/article/details/79148717
// ���⣺�ƶ�������Ӧ�׳��κ��쳣  
// �𰸣��ƶ�����ͨ���������ڴ棬��˲����׳��쳣������дһ�����׳��쳣���ƶ�����ʱ ��
//  ����Ӧ��������֪ͨ��׼�⣬������⹤��������ͨ��ָ����noexcept����������https://blog.csdn.net/rest_in_peace/article/details/81483224
#include<iostream>
#include<vector>
#include <string.h>

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



//start:�����嵥2-2 MyString ʵ��
class MyString{
private:
    char* m_data;
    size_t m_len;

    void copy_data(const char* s){
        m_data = new char[m_len + 1]; 
        memcpy(m_data, s, m_len);
        m_data[m_len] = '\0';
    }
public:
    MyString(){
        m_data = nullptr;
        m_len = 0;
        cout << "default construct" << endl;
    }
    MyString(const char* s){
        m_len = strlen(s);// #include <string.h>
        copy_data(s);
        cout << "my construct" << endl;
    }
    MyString(const MyString& str){
        m_len = str.m_len;
        copy_data(str.m_data);
        cout << "copy construct" << endl;
    }
    MyString& operator=(const MyString& str){
        if (this != &str)
        {
            m_len = str.m_len;
            copy_data(str.m_data);
        }
        cout << "copy assign" << endl;
        return *this;
    }
    ~MyString(){
        if (m_data)
        {
            delete []m_data;
        }
        m_data = 0;
    }
};

void testMyString()
{
    cout << "=========testMyString=========" << endl;
    MyString a;
    a = MyString("hello");
    std::vector<MyString> vec;
    vec.push_back(MyString("World"));
}
//end:�����嵥2-2 MyString ʵ��
int main()
{
    A a = getA(false);
    testMyString();
}