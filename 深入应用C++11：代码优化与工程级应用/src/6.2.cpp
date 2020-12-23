#include<iostream>
#include<string>
using namespace std;

int main(){
    double f = 1.53;
    string f_str = std::to_string(f);
    cout << f_str << endl;

    double f1 = 4.123;
    wstring f_str1 = std::to_wstring(f1);
    wcout << f_str1 << endl;
}