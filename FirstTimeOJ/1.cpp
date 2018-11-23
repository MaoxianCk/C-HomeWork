#include <iostream>
using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    if ((b % a) != 0)
    {
        cout << b % a - 1;
    }
    else
    {
        cout << a - 1;
    }

    return 0;
}
