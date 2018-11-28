#include <iomanip>
#include <iostream>
#include <math.h>
#include <memory.h>
#include <string>

using namespace std;

double cal(double x, double y, int com)
{
	switch (com)
	{
	case 0:
		return x + y;
	case 1:
		return x - y;
	case 2:
		return x * y;
	case 3:
		return x / y;
	}
}
bool f(double a, double b, double c)
{
	bool t = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int p = 0;
			if (fabs(cal(cal(a, b, i), c, j) - 18) < 0.0001)
			{
				t=1; p++;
				//cout << i << " " << j <<" "<<p<< endl;
				break;
			}
			if (fabs(cal(cal(a, c, i), b, j) - 18) < 0.0001)
			{
				t = 1;
				p++;
				//cout << i << " " << j <<" "<<p<< endl;
				break;
			}
			if (fabs(cal(cal(b, a, i), c, j) - 18) < 0.0001)
			{
				t=1; p++;
				//cout << i << " " << j <<" "<<p<< endl;
				break;
			}
			if (fabs(cal(cal(b, c, i), a, j) - 18) < 0.0001)
			{
				t=1; p++;
				//cout << i << " " << j <<" "<<p<< endl;
				break;
			}
			if (fabs(cal(cal(c, b, i), a, j) - 18) < 0.0001)
			{
				t=1; p++;
				//cout << i << " " << j <<" "<<p<< endl;
				break;
			}
			if (fabs(cal(cal(c, a, i), b, j) - 18) < 0.0001)
			{
				t=1; p++;
				//cout << i << " " << j <<" "<<p<< endl;
				break;
			}
		}
	}
	return t;
}
int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		double a, b, c;
		cin >> a >> b >> c;
		cout << (f(a, b, c) ? "Yes" : "No") << endl;
	}
	return 0;
}
