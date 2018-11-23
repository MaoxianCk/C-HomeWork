#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    int year;
    cin >> year;

    if (year % 60 <= 3)
    {
        cout << year % 60 + 57;
    }
    else if (year % 60 == 3)
    {
        cout << 60;
    }
    else
    {
        cout << year % 60 - 3;
    }
    return 0;
}