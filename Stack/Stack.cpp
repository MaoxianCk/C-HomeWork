#include <iostream>
using namespace std;

//顺序栈
template <class Type>
class ArrayStack
{
  private:
    int top;
    int maxSize;
    Type *date;

  public:
    ArrayStack();
    ArrayStack(int max);
    ~ArrayStack();
    bool push(Type d);
    Type pop();
    Type getTop();
    int getSize();
    bool isEmpty();
    void setEmpty();
};
template <class Type>
ArrayStack<Type>::ArrayStack()
{
    top = -1;
    maxSize = 100;
    date = new Type[maxSize];
}
template <class Type>
ArrayStack<Type>::ArrayStack(int max)
{
    top = -1;
    maxSize = max;
    date = new Type[maxSize];
}
template <class Type>
ArrayStack<Type>::~ArrayStack()
{
    top = -1;
    delete date;
    date = nullptr;
}
template <class Type>
bool ArrayStack<Type>::push(Type d)
{
    top++;
    if (top == maxSize)
    {
        return false;
    }

    date[top] = d;
    return true;
}
template <class Type>
Type ArrayStack<Type>::pop()
{
    if (top == -1)
    {
        return false;
    }

    Type temp = date[top];
    top--;
    return temp;
}
template <class Type>
Type ArrayStack<Type>::getTop()
{
    if (top == -1)
    {
        return false;
    }

    Type temp = date[top];
    return temp;
}
//返回当前长度 top+1
template <class Type>
int ArrayStack<Type>::getSize()
{
    return top + 1;
}
template <class Type>
bool ArrayStack<Type>::isEmpty()
{
    return (top == -1 ? true : false);
}
template <class Type>
void ArrayStack<Type>::setEmpty()
{
    top = -1;
}

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

void printBinary(int num)
{
    cout << "原数字 :" << num << endl;
    ArrayStack<int> stack;
    while (num > 0)
    {
        stack.push(num % 2);
        num /= 2;
    }
    cout << "二进制 :";
    while (!stack.isEmpty())
    {
        cout << stack.pop();
    }
    cout << endl;
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
    printBinary(3312);


    int a[11] = {1, 4, 6, 3, 5, 8, 9, 2, 3, 1, 5};
    divideNumberAndPrint(a, 11);
    return 0;
}