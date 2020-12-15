// 1.7 tuple 元组
#include<iostream>
#include <utility>
#include<tuple>
#include<map>
#include<string>
using namespace std;

void print_pack (std::tuple<std::string&&,int&&> pack) {
  std::cout << std::get<0>(pack) << ", " << std::get<1>(pack) << '\n';
}

int main()
{
    tuple<int, int> tp = make_tuple(1, 2);
    
    // auto tieTp = std::tie(11, 22); //error:std::tie(参数) 参数只能是左值
    int a = 11, b = 22;
    auto tieTp = std::tie(a, b); // 创建一个tuple的左值引用,实际类型是 std::tuple<int&, int&>
    cout << std::get<0>(tieTp) << endl; 
    // cout << tieTp.get<0>() << endl; // 书上这么写，但是tuple没有get成员

    std::tie(a, b) = tp;
    cout << a << " " << b << endl;

    std::tie(std::ignore, b) = tp; // 使用 std::ignore 占位符 不解某个位置的值
    cout << b << endl;

    // 创建右值引用的元组方法:forward_as_tuple
    std::string str ("John");
    print_pack (std::forward_as_tuple(str+" Smith",25));
    print_pack (std::forward_as_tuple(str+" Daniels",22));

    // 通过tuple_cat 连接多个tuple
    auto t2 = tuple_cat(tp, tieTp);
    cout << std::get<0>(t2) << " " << std::get<1>(t2) << std::get<2>(t2) << endl;
    return 0;
}