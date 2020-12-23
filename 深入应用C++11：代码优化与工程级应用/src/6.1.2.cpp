#include<iostream>
#include<chrono>
#include <iomanip>      // std::put_time
#include <ctime>
using namespace std;

int main()
{
    using days_type = std::chrono::duration<int, std::ratio<24*60*60>>;
    std::chrono::time_point<std::chrono::system_clock, days_type> today = std::chrono::time_point_cast<days_type>(std::chrono::system_clock::now());
    cout << today.time_since_epoch().count() << " days since epoch" << endl;

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t last = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    std::time_t next = std::chrono::system_clock::to_time_t(now + std::chrono::hours(24));
    cout << "one day ago, the time was " << std::put_time(std::localtime(&last), "%F %T") << endl; // std::put_time
    cout << "next day, the time was " << std::put_time(std::localtime(&next), "%F %T") << endl;
    return 0;
}