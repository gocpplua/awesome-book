// VSCode - 解决 vscode终端输出中文乱码的问题:https://blog.csdn.net/weixin_40040107/article/details/103721554
// 本来是通过转换以后才会输出正常的中文，现在是不用转换就可以输出正常字符，转换以后就不行。 因为我设置成了Unicode UTF-8
#include<iostream>
#include<codecvt>
#include<string>
using namespace std;

int main()
{
    std::wstring str = L"中国人";
    wcout << str << endl;
    std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> converter(new std::codecvt<wchar_t, char, std::mbstate_t>("CHS"));

    std::string narrowStr = converter.to_bytes(str);
    // string to wstring
    std::wstring wstr = converter.from_bytes(narrowStr);
    cout << narrowStr << endl;

    wcout.imbue(std::locale("CHS"));
    wcout << wstr << endl;

    cout << "发" << endl;
    return 0;
}