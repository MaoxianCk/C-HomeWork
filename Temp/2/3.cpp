#include <iostream>
using namespace std;

void initialize(int *p, int n)
{
    //�� 1��ʼ�� p�� p+n��Ԫ�����θ�ֵ
    int now = 1;
    for (int *temp = p; temp < p + n; temp++)
    {
        *temp = now++;
    }
}
int getId(int *child, int n)
{
    int now = 1;//��¼��ǰ���
    int out = 0;//�Ѿ��˳�������
    //ָ��ѭ��
    for (int *pchild = child; pchild < child + n; pchild = (pchild == child + n - 1 ? child : pchild + 1))
    {
        if (*pchild != 0)
        {
            if (now == 5)//��n==5��ʱ�򣬴������ݲ���ʾ��ǰʣ���������
            {
                now = 1;
                *pchild = 0;
                out++;
                cout << "�� " << out << " �ֵĽ��:";
                for (int *ptemp = child; ptemp < child + n; ptemp++)
                {
                    if (*ptemp != 0)
                    {
                        cout << *ptemp << " ";
                    }
                }
                cout << endl;
                if (out == n - 1)//��Ϸ���ֻ����һ�ˣ���ֻҪ�߳�n-1���˾��Ѿ�����
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
    //���ؽ��е����һ���˱��
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
    cout << "������С���ѵ�����:";
    cin >> n;
    int *child = new int[n];

    initialize(child, n);

    int ans = getId(child, n);
    cout << "���һ�����µ��˵ı����:" << ans << "!" << endl;

    return 0;
}