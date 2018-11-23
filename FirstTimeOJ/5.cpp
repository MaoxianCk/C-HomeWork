

#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d, x, y;
    int ansA, ansB, sum;
    int lastAnsA;
    cin >> a >> b >> c >> d >> x >> y;

    sum = 0;
    //暴力列举第一种怪物的数量
    for (ansA = 1; ansA < x; ansA++)
    {
        //如果当前的合法解已经有2个，就表示多解，可以直接结束判断
        if (sum == 2)
        {
            break;
        }
        //计算第一种怪物的头的总数量
        int sumAhead = ansA * a;
        //计算第二种怪物的数量
        ansB = (x - sumAhead) / c;
        //合法解条件
        if (ansA >= 1 && ansB >= 1)
        {
            //反证，验证当前计算的解是否满足条件
            if (sumAhead + ansB * c == x && ansA * b + ansB * d == y)
            {
                lastAnsA = ansA;
                sum++;
            }
        }
    }

    if (sum == 0)
    {
        cout << -1;
    }
    else if (sum == 1)
    {
        cout << lastAnsA << " " << (x - lastAnsA * a) / c;
    }
    else
    {
        cout << 0;
    }
    return 0;
}
