#include <iostream>
#include <math.h>
using namespace std;

void priceByPointer(double *a, double *b, double *sub, double *sum)
{
    cout << "使用指针处理数据..." << endl;
    *a *= 0.75;
    *b *= 0.8;
    *sub = abs(*a - *b);
    *sum = *a + *b;
}
int main()
{
    double aPrice = 600, bPrice = 350;
    double a, b, sub, sum;

    a = aPrice, b = bPrice;
    double *pa = &a, *pb = &b, *psub = &sub, *psum = &sum;
    priceByPointer(pa, pb, psub, psum);
    cout << "A商品原价:" << aPrice
         << "\tB商品原价:" << bPrice
         << "\tA折后价格:" << a
         << "\tB折后价格:" << b
         << "\tAB折后差价" << sub
         << "\tAB折后单价总和" << sum << endl;
    return 0;
}