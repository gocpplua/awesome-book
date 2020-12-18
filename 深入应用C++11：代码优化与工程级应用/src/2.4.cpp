
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

struct Complicated{
    int year;
    double country;
    string name;

    Complicated(int a, double b, string c):year(a), country(b), name(c){
        cout << "contruct" << endl;
    }
    Complicated(const Complicated& other):year(other.year), country(other.country), name(other.name){
        cout << "copy contruct" << endl;
    }
};

int main()
{
    std::map<int, Complicated> m;
    
    int aInt = 4;
    double aDouble = 5.0;
    string aString = "C++";

    cout << "---insert---" << endl;
    m.insert(make_pair(4, Complicated(aInt, aDouble, aString)));// contruct copy copy ?? 为什么有两个copy

    cout << "---emplace---"<< endl;
    m.emplace(4, Complicated(aInt, aDouble, aString)); // construct copy ?? 为什么有一个copy

    std::vector<Complicated> v;
    cout << "---emplace_back---"<< endl;
    v.emplace_back(aInt, aDouble, aString); // construct

    cout << "---push_back---"<< endl;
    v.push_back(Complicated(aInt, aDouble, aString)); // construct copy copy ?? 为什么有两个copy
    return 0;
}