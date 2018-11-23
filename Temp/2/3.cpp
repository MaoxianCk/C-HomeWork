#include <iostream>
using namespace std;

void initialize(int *p, int n)
{
    //从 1开始给 p到 p+n内元素依次赋值
    int now = 1;
    for (int *temp = p; temp < p + n; temp++)
    {
        *temp = now++;
    }
}
int getId(int *child, int n)
{
    int now = 1;//记录当前编号
    int out = 0;//已经退出的人数
    //指针循环
    for (int *pchild = child; pchild < child + n; pchild = (pchild == child + n - 1 ? child : pchild + 1))
    {
        if (*pchild != 0)
        {
            if (now == 5)//当n==5的时候，处理数据并显示当前剩余人数编号
            {
                now = 1;
                *pchild = 0;
                out++;
                cout << "第 " << out << " 轮的结果:";
                for (int *ptemp = child; ptemp < child + n; ptemp++)
                {
                    if (*ptemp != 0)
                    {
                        cout << *ptemp << " ";
                    }
                }
                cout << endl;
                if (out == n - 1)//游戏最后只留下一人，故只要踢出n-1个人就已经结束
                {
                    break;
                }
            }
            else
            {
                now++;
            }
        }
    }
    //返回仅有的最后一个人编号
    for (int *pchild = child; pchild < child + n; pchild++)
    {
        if (*pchild != 0)
        {
            return *pchild;
        }
    }
    return -1;
}

int main()
{
    int n;
    cout << "请输入小朋友的数量:";
    cin >> n;
    int *child = new int[n];

    initialize(child, n);

    int ans = getId(child, n);
    cout << "最后一个留下的人的编号是:" << ans << "!" << endl;

    return 0;
}