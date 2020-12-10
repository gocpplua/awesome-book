// 1.3.2 列表初始化的使用细节
#include<iostream>
#include<string>
using namespace std;

// 聚合类型定义
// (1) 类型是一个普通数组(如 int[10], char[],long[2][3])
// (2) 类型是一个类(class, struct, union),且
//     2.1 无用户自定义的构造函数 2.2 无private和protect的非静态数据成员 
//     2.3 无基类 2.4 无虚函数 2.5 不能有{}和=直接初始化的非静态数据成员

struct Foo
{
    int x;
    double y;
    int z;
    Foo(int, int){}
};

struct ST
{
    int x;
    double y;
private:
    int z;
};

struct STS
{
    int x;
    double y;
private:
    static int z;
};

struct Base{};
struct Dfoo : public Base
{
    int x;
    double y;
};

struct Vfoo
{
    int x;
    double y;
    virtual void vfoo(){}
};

struct CFoo
{
    int x;
    double y = 0.0;
};

struct SST
{
    int x;
    double y;
    virtual void f(){}
private:
    int z;

public:
    SST(int i, double j, int k):x(i), y(j), z(k){}
};

struct SSTS
{
    STS st;
    int x;
    int y;
};

int main()
{
    // 类型是一个普通数组
    int x[] = {1, 2, 3};
    float y[4][3] = {
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
        {1, 2, 3},
    };
    string sa[3] = {"123", "123", "123"};

    //类型是一个类(class, struct, union)
    //Foo foo{1, 2.5, 1}; //error:因为存在自定义的构造函数，所有不能使用初始化列表
    //ST s{1, 2.5, 1}; //error:存在非静态的private数据成员，所有不能使用初始化列表
    STS sts{1, 2.5}; //ok:因为private数据成员是static，所有不影响，只看x和y就行
    //Dfoo dfoo{1, 2.5}; //error:Dfoo有一个基类
    //Vfoo vfoo{1, 2.5};//error:Vfoo有一个虚函数
    CFoo cfoo{1, 2.5}; //error:CFoo存在直接使用=初始化的非静态数据成员y

    // 对于非聚合类型，想要使用初始化列表的方法就是自定义一个自定义构造函数
    SST sst(1, 2.5, 2);

    // 对于非聚合类型的定义并非递归的
    SSTS ssts{{}, 1, 2}; // ok:ssts初始化过程，对于非聚合类st做初始化时，直接用{}，相当于调用STS的无参构造函数



    return 0;
}