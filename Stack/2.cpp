#include <iostream>
using namespace std;

//共享栈
template <class Type>
class ArrayBothStack
{
  private:
    int maxSize;
    int topL;
    int topR;
    Type *date;

  public:
    ArrayBothStack();
    ArrayBothStack(int max);
    bool pushL(Type d);
    bool pushR(Type d);
    Type popL();
    Type popR();
    Type getTopL();
    Type getTopR();
    bool isEmptyL();
    bool isEmptyR();
};
template <class Type>
ArrayBothStack<Type>::ArrayBothStack()
{
    maxSize = 100;
    date = new Type[maxSize];
    topL = -1;
    topR = maxSize;
}
template <class Type>
ArrayBothStack<Type>::ArrayBothStack(int max)
{
    maxSize = max;
    date = new Type[maxSize];
    topL = -1;
    topR = maxSize;
}
template <class Type>
bool ArrayBothStack<Type>::pushL(Type d)
{
    topL++;
    if (topL == topR)
    {
        return false;
    }

    date[topL] = d;
    return true;
}
template <class Type>
bool ArrayBothStack<Type>::pushR(Type d)
{
    topR--;
    if (topL == topR)
    {
        return false;
    }

    date[topR] = d;
    return true;
}
template <class Type>
Type ArrayBothStack<Type>::popL()
{
    if (topL == -1)
    {
        return false;
    }

    Type temp;
    temp = date[topL];
    topL--;
    return temp;
}
template <class Type>
Type ArrayBothStack<Type>::popR()
{
    if (topR == maxSize)
    {
        return false;
    }

    Type temp;
    temp = date[topR];
    topR++;
    return temp;
}
template <class Type>
Type ArrayBothStack<Type>::getTopL()
{
    Type temp = date[topL];
    return temp;
}
template <class Type>
Type ArrayBothStack<Type>::getTopR()
{
    Type temp = date[topR];
    return temp;
}
template <class Type>
bool ArrayBothStack<Type>::isEmptyL()
{
    return (topL == -1 ? true : false);
}
template <class Type>
bool ArrayBothStack<Type>::isEmptyR()
{
    return (topR == maxSize ? true : false);
}

void divideNumberAndPrint(int *a, int n)
{
    ArrayBothStack<int> stack(n);
    for (int i = 0; i < n; i++)
    {
        if (a[i] % 2 == 1)
        {
            stack.pushL(a[i]);
        }
        else
        {
            stack.pushR(a[i]);
        }
    }
    cout << "奇数 : ";
    while (!stack.isEmptyL())
    {
        cout << stack.popL() << " ";
    }
    cout << endl;
    cout << "偶数 : ";
    while (!stack.isEmptyR())
    {
        cout << stack.popR() << " ";
    }
}

int main()
{
    int n;
    cout << "有几个数字：";
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n;i++)
    {
        cout << "请输入第" << i + 1 << "个数字：";
        cin >> a[i];
    }
        divideNumberAndPrint(a, n);
    return 0;
}