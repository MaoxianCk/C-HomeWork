#include <iostream>
#include <math.h>
using namespace std;

void priceByReference(double &a, double &b, double &sub, double &sum)
{
	cout << "ʹ�ô����ô�������..." << endl;
	a *= 0.75;
	b *= 0.8;
	sub = abs(a - b);
	sum = a + b;
}
int main()
{
	double aPrice = 600, bPrice = 350;
	double a, b, sub, sum;

	a = aPrice,
	b = bPrice, sub = 0, sum = 0;
	priceByReference(a, b, sub, sum);
	cout << "A��Ʒԭ��:" << aPrice
		 << "\tB��Ʒԭ��:" << bPrice
		 << "\tA�ۺ�۸�:" << a
		 << "\tB�ۺ�۸�:" << b
		 << "\tAB�ۺ���" << sub
		 << "\tAB�ۺ󵥼��ܺ�" << sum << endl;
	return 0;
}
