// 草稿.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>
using namespace std;

int main()
{
	int n, cnt1 = 0, cnt2 = 0;
	cin >> n;
	bool *a = new bool[n] {0};
	for (int i = 0; i < n; i++)
	{
		if (a[i] == 0 && cnt2 == n - 1)
		{
			cout << "最后剩下的人是第" << i + 1 << "号" << endl;
			break;
		}
		if (a[i] == 0)
		{
			cnt1++;
		}
		if (cnt1 == 5)
		{
			a[i] = 1;
			cnt2++;
			cnt1 = 0;
		}
		if (i == n - 1)
		{
			i = -1;
		}
	}

	return 0;
}


