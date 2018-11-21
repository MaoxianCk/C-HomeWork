#include<iostream>
#include<cmath>
using namespace std;
int main()
{
    int n, num, sum;
    cin >> n;
    while(n--)
    {
        cin >> num;
        while(log10(num)+1>=2)
        {
            sum = 0;
            while(num>0)
            {
                sum += num % 10;
                num /= 10;
            }
            num = sum;
        }
        cout << num << endl;
    }
    return 0;
}