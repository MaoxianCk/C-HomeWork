// 草稿.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>
using namespace std;

void swap1(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}
int main()
{
	int a, b, c;
	cin >> a >> b >> c;
	swap1(&a, &c);
	swap1(&a, &b);
	cout << a << " " << b << " " << c << endl;

	return 0;
}


