// 草稿.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>
#include<cmath>
using namespace std;

void price(double *A, double *B, double *sub, double *sum)
{
	*A *= 0.75;
	*B *= 0.8;
	*sub = abs(*A - *B);
	*sum = *A + *B;
}
int main()
{
	double A = 600, B = 350, sub, sum;
	price(&A, &B, &sub, &sum);
	cout << "商品A的价格：" << A << "\t" << "商品B的价格：" << B << endl;
	cout << "商品A、B的差价：" << sub << "\t" << "商品A、B的单价总和：" << sum << endl;

	return 0;
}


