#include <iostream>
#include <math.h>
using namespace std;

void priceByReference(double &a, double &b, double &sub, double &sum)
{
	cout << "使用传引用处理数据..." << endl;
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
	cout << "A商品原价:" << aPrice
		 << "\tB商品原价:" << bPrice
		 << "\tA折后价格:" << a
		 << "\tB折后价格:" << b
		 << "\tAB折后差价" << sub
		 << "\tAB折后单价总和" << sum << endl;
	return 0;
}
