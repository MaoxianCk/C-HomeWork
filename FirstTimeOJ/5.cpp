

#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d, x, y;
    int ansA, ansB, sum;
    int lastAnsA;
    cin >> a >> b >> c >> d >> x >> y;

    sum = 0;
    //�����оٵ�һ�ֹ��������
    for (ansA = 1; ansA < x; ansA++)
    {
        //�����ǰ�ĺϷ����Ѿ���2�����ͱ�ʾ��⣬����ֱ�ӽ����ж�
        if (sum == 2)
        {
            break;
        }
        //�����һ�ֹ����ͷ��������
        int sumAhead = ansA * a;
        //����ڶ��ֹ��������
        ansB = (x - sumAhead) / c;
        //�Ϸ�������
        if (ansA >= 1 && ansB >= 1)
        {
            //��֤����֤��ǰ����Ľ��Ƿ���������
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
