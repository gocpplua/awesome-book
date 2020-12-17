// 2.1.2 右值引用优化性能，避免深拷贝
// 参考：<<你不知道的拷贝、赋值、移动构造函数>>:https://blog.csdn.net/wk_bjut_edu_cn/article/details/79148717
// 问题：移动操作不应抛出任何异常  
// 答案：移动操作通常不分配内存，因此不会抛出异常，当编写一个不抛出异常的移动操作时 ，
//  我们应当将此事通知标准库，避免额外工作，可以通过指定”noexcept“来做到。https://blog.csdn.net/rest_in_peace/article/details/81483224
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
    return b; // 返回值是一个右值A&&，那么会调用移动构造，如果不存在移动构造(注意是如果不存在)，那么将其转换为一个const A&，所以，是调用A的拷贝构造函数。
}



//start:代码清单2-2 MyString 实现
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
//end:代码清单2-2 MyString 实现
int main()
{
    A a = getA(false);
    testMyString();
}