#include <iostream>
#include <math.h>
using namespace std;

void priceByPointer(double *a, double *b, double *sub, double *sum)
{
    cout << "ʹ��ָ�봦������..." << endl;
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
    cout << "A��Ʒԭ��:" << aPrice
         << "\tB��Ʒԭ��:" << bPrice
         << "\tA�ۺ�۸�:" << a
         << "\tB�ۺ�۸�:" << b
         << "\tAB�ۺ���" << sub
         << "\tAB�ۺ󵥼��ܺ�" << sum << endl;
    return 0;
}