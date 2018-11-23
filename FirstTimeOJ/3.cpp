#include <iostream>
using namespace std;

int main()
{
    int a, b;
    int min, mid, max;
    int x, y, z;

    cin >> a >> b;

    x = a + b;
    y = a - b;
    z = a * b;

    max = x;
    if (y > max)
    {
        max = y;
    }
    if (z > max)
    {
        max = z;
    }

    min = x;
    if (y < min)
    {
        min = y;
    }
    if (z < min)
    {
        min = z;
    }

    mid = x + y + z - min - max;


    cout << min;
    if (mid != min)
    {
        cout << " " << mid;
    }
    if (max != mid)
    {
        cout << " " << max;
    }

    return 0;
}