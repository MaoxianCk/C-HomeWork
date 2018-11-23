// 草稿.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>
using namespace std;

void inputMatrix(int a[3][4])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cin >> a[i][j];
		}
	}
}
void transpose(int a[3][4], int b[4][3])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			b[i][j] = a[j][i];
		}
	}
}
void printMatrix(int b[4][3])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << b[i][j] << " ";
		}
		cout << endl;
	}
}
int main()
{
	int a[3][4], b[4][3];
	inputMatrix(a);
	transpose(a, b);
	printMatrix(b);

	return 0;
}


