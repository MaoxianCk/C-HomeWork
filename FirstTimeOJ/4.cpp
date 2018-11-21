#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d;
    bool ans = false;
    cin >> a >> b >> c >> d;

    if(a==b&&b==c&&c==d)
    {
        ans = false;
    }
    else if (a == b && c == d)
    {
        ans = true;
    }
    else if (a == c && b == d)
    {
        ans = true;
    }
    else if (a == d && b == c)
    {
        ans = true;
    }
    else
    {
        ans = false;
    }

    if (ans)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }

    return 0;
}