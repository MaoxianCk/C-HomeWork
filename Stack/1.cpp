#include <iostream>
#include <string>
using namespace std;

//˳��ջ
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
//���ص�ǰ���� top+1
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

//ʮ����ת������
string toBinary(int num)
{
    ArrayStack<int> stack;
    string str="";
    while (num > 0)
    {
        stack.push(num % 2);
        num /= 2;
    }
    while (!stack.isEmpty())
    {
        str += char(stack.pop() + '0');
    }
    return str;
}

int main()
{
    int n;
    cout << "������һ��ʮ����������";
    cin >> n;
    cout << "�����ƣ�" << toBinary(n) << endl;

    return 0;
}