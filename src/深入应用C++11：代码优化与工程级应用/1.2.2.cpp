// 模板别名
#include<iostream>
#include<map>
using namespace std;


/* 不能这么写
template <typename Val>
typedef std::map<std::string, Val> type;
*/

// C++11前需要使用繁琐的外敷模板
template <typename Val>
struct str_cmp
{
    typedef std::map<std::string, Val> type;
};

// C++11 以后写法：模板别名
template <typename Val>
using str_cmp_t = std::map<std::string, Val>;

int main()
{
    str_cmp<int>::type map1;
    str_cmp_t<int> map2;
    return 0;
}
