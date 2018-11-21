#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int Y, M, D, y, m, d, min1, min2;

    //分解年月日
    Y = n / 10000;
    M = n / 100 % 100;
    D = n % 100;
    //逆置原日期并分解年月日
    y = n % 10 * 1000 + n / 10 % 10 * 100 + n / 100 % 10 * 10 + n / 1000 % 10;
    m = n / 10000 % 10 * 10 + n / 100000 % 10;
    d = n / 1000000 % 10 * 10 + n / 10000000;

    //得到对应月份的天数
    if (M == 1 || M == 3 || M == 5 || M == 7 || M == 8 || M == 10 || M == 12)
    {
        min1 = 31;
    }
    else if (M == 2)
    {
        if (Y % 3200 == 0 || (Y % 100 == 0 && Y % 400 != 0) || Y % 4 != 0)
        {
            min1 = 28;
        }
        else
        {
            min1 = 29;
        }
    }
    else
    {
        min1 = 30;
    }

    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
    {
        min2 = 31;
    }
    else if (m == 2)
    {
        if (y % 3200 == 0 || (y % 100 == 0 && y % 400 != 0) || y % 4 != 0)
        {
            min2 = 28;
        }
        else
        {
            min2 = 29;
        }
    }
    else
    {
        min2 = 30;
    }

    if (((Y >= 0) && (M >= 1 && M <= 12) && (D >= 1 && D <= min1))
     && ((y >= 0) && (m >= 1 && m <= 12) && (d >= 1 && d <= min2)))      
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
    return 0;
}