#include <iostream>
#include <string>
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

enum OPERATORS
{
    ADD,
    SUB,
    MUL,
    DIV,
    PAR_L,
    PAR_R,
    END
};

char cmp[7][7] =
    {
        {'>', '>', '<', '<', '<', '>', '>'},
        {'>', '>', '<', '<', '<', '>', '>'},
        {'>', '>', '>', '>', '<', '>', '>'},
        {'>', '>', '>', '>', '<', '>', '>'},
        {'<', '<', '<', '<', '<', '=', '@'},
        {'>', '>', '>', '>', '@', '>', '>'},
        {'<', '<', '<', '<', '<', '@', '='}};

bool isNumber(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int isOperator(char ch)
{
    switch (ch)
    {
    case '+':
        return ADD;
    case '-':
        return SUB;
    case '*':
        return MUL;
    case '/':
        return DIV;
    case '(':
        return PAR_L;
    case ')':
        return PAR_R;
    case '#':
        return END;
    default:
        return -1;
    }
}
double caculater(int a, int b, char op)
{
    double ans = 0;
    if (op == '+')
    {
        ans = a + b;
    }
    else if (op == '-')
    {
        ans = a - b;
    }
    else if (op == '*')
    {
        ans = a * b;
    }
    else if (op == '/')
    {
        if (b == 0)
        {
            cout << "除数不能为零！" << endl;
            return 0;
        }
        ans = a / b;
    }
    return ans;
}

int slove(string str)
{
    ArrayStack<int> number(str.length());
    ArrayStack<char> operation(str.length());
    int cntEnd = 0;
    operation.push('#');
    char ch;
    for (int i = 0; i < str.length(); i++)
    {
        ch = str[i];

        if (isNumber(ch))
        {
            int temp = 0;
            bool flag = false; //是否是负数
            if (str[i - 2] == '(' && str[i - 1] == '-')
            {
                flag = true;
                operation.pop();
            }
            while (isNumber(str[i]))
            {
                temp = temp * 10 + str[i] - '0';
                i++;
            }
            number.push(flag ? -temp : temp);
            i--;
        }
        else if (isOperator(ch) != -1)
        {
            if (ch == '#')
            {
                cntEnd++;
                if (cntEnd == 1)
                {
                    continue;
                }
            }
            while (true)
            {
                char cmps = cmp[isOperator(operation.getTop())][isOperator(ch)];
                if (cmps == '<')
                {
                    operation.push(ch);
                    break;
                }
                else if (cmps == '>')
                {
                    int b = number.pop();
                    int a = number.pop();
                    char op = operation.pop();
                    number.push(caculater(a, b, op));
                    continue;
                }
                else if (cmps == '=')
                {
                    operation.pop();
                    break;
                }
                else
                {
                    cout << "表达式错误!" << endl;
                    return 0;
                }
            }
        }
        else if (ch == ' ')
        {
            continue;
        }
        else
        {
            cout << "表达式错误!" << endl;
            return 0;
        }
        if (cntEnd == 2)
        {
            return number.pop();
        }
    }

    cout << "表达式错误!" << endl;
    return 0;
}

int main()
{
    string str;
    cout << "请输入一个合法中缀表达式" << endl;
    cout << "例如 #((4 / 2) * (2 * 3 + 1)) - (-1) #" << endl;
    getline(cin,str);

    cout << str << " = " << slove(str) << endl;
    return 0;
}