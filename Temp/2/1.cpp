#include <iostream>
#include <math.h>
using namespace std;

void mySwap1(int *a,int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
int main()
{
	int a, b, c;
	int *pa, *pb, *pc;
	pa = &a, pb = &b, pc = &c;
	cout << "�������������ͱ���ֵ:"<<endl;
	cin >> a >> b >> c;

	mySwap1(pa, pb);
	mySwap1(pb, pc);
	cout << "����������:" << endl;
	cout << a <<" "<< b <<" "<< c << endl;
	return 0;
}
