#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    int max = a;
    if (b > max)
        max = b;
    if (c > max)
        max = c;
    int min = c;
    if (a < min)
        min = a;
    if (b < min)
        min = b;
    int n;
    if (min < a&&a < max)
        n = a;
    if (min < b&&b < max)
        n = b;
    else
        n = c;
    cout << min << " " << n << " " << max;

    return 0;
}