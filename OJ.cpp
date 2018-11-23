#include <cmath>
#include <iostream>
using namespace std;

int Scan()
{
	//  ÊäÈëÍâ¹Ò
	int res = 0, flag = 0;
	char ch;
	if ((ch = getchar()) == '-')
	{
		flag = 1;
	}
	else if (ch >= '0' && ch <= '9')
	{
		res = ch - '0';
	}
	while ((ch = getchar()) >= '0' && ch <= '9')
	{
		res = res * 10 + (ch - '0');
	}
	return flag ? -res : res;
}

int main()
{
	int a,cnt=0;
	cin >> a;
	int b = 0;
	while (a--)
	{
		if(Scan()==1)
		{
			b++;
		}
		
		else
		{
			cnt++;
		}
		
	}
	cout << abs(cnt - b);
	return 0;
}