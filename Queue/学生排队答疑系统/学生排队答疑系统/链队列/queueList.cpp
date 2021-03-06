#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

int inputNumber(int a, int b) //范围a b 输入数字
{
    string str;
    while (true)
    {
        bool flag = true; //标记是否纯数字
        cin >> str;
        for (unsigned int i = 0; i < str.length(); i++)
        {
            if (str[i] < '0' || str[i] > '9')
            {
                flag = false;
                break;
            }
        }
        if (flag == true)
        {
            int num = atoi(str.c_str());
            if (num < a || num > b)
            {
                cout << "输入错误，请重新输入数字!" << endl;
                continue;
            }
            return num;
        }
        else
        {
            cout << "输入错误，请重新输入数字!" << endl;
            continue;
        }
    }
}
int inputNumber()
{
    string str;
    while (true)
    {
        bool flag = true; //标记是否纯数字
        cin >> str;
        for (unsigned int i = 0; i < str.length(); i++)
        {
            if (str[i] < '0' || str[i] > '9')
            {
                flag = false;
                break;
            }
        }
        if (flag == true)
        {
            return (atoi(str.c_str()));
        }
        else
        {
            cout << "请输入数字!" << endl;
            continue;
        }
    }
}

struct Student
{
    string id;
    string name;
    void display()
    {
        cout << "学号：" << id << "\t姓名：" << name << endl;
    }
};
template <class Type>
struct Node
{
    Type date;
    Node *next;
};

template <class Type>
class Queue
{
  private:
    Node<Type> *front, *rear;
    int length;

  public:
    Queue();
    Queue(int size);
    ~Queue();
    bool push(Type d);
    Type pop();
    bool isEmpty();
    int getLength();
    Type getFront();
    Type getByNum(int number);
};

template <class Type>
Queue<Type>::Queue()
{
    Node<Type> *temp = new Node<Type>;
    temp->next = nullptr;
    front = rear = temp;
    length = 0;
}
template <class Type>
Queue<Type>::~Queue()
{
    while (!isEmpty())
    {
        pop();
    }
    front = nullptr;
    rear = nullptr;
}
template <class Type>
bool Queue<Type>::push(Type d)
{
    Node<Type> *temp = new Node<Type>;
    temp->date = d;
    temp->next = nullptr;
    rear->next = temp;
    rear = temp;
    length++;
    return true;
}
template <class Type>
Type Queue<Type>::pop()
{
    if (rear == front)
    {
        cout << "下溢" << endl;
        system("pause");
        exit(1);
    }
    Node<Type> *temp = new Node<Type>;

    temp = front->next;
    Type tempDate = temp->date;
    front->next = temp->next;
    length--;
    if (temp->next == nullptr)
    {
        rear = front;
    }
    delete temp;

    return tempDate;
}
template <class Type>
Type Queue<Type>::getByNum(int num)
{
    if (num > length || num < 1)
    {
        cout << "查找错误，没有num位节点" << endl;
        num = 1;
    }
    int cnt = 0;
    Node<Type> *temp = new Node<Type>;
    temp = front;
    while (cnt < num)
    {
        temp = temp->next;
        cnt++;
    }
    Type tempDate = temp->date;
    return tempDate;
}
template <class Type>
int Queue<Type>::getLength()
{
    return length;
}
template <class Type>
bool Queue<Type>::isEmpty()
{
    return (front == rear ? true : false);
}
template <class Type>
Type Queue<Type>::getFront()
{
    Type tempDate = front->next->date;
    return tempDate;
}

class QueueSystem
{
  private:
    Queue<Student> queue;

  public:
    void printWelcome();
    void selectMenu();
    void lineUp();  //排队
    void lineOut(); //出队
    void display(); //遍历
    void endExit();
    bool isEmpty();
};
void QueueSystem::printWelcome()
{
    cout << "   %---欢迎进入答疑系统---%" << endl;
}
void QueueSystem::lineUp()
{
    Student temp;
    cout << "请输入学号：";
    cin >> temp.id;
    cout << "请输入姓名：";
    cin >> temp.name;

    if (queue.push(temp))
    {
        cout << "入队成功！";
    }
    else
    {
        cout << "入队失败，队伍已满，";
    }
}
void QueueSystem::lineOut()
{
    if (queue.isEmpty())
    {
        cout << "目前没有人在答疑，";
    }

    else
    {
        Student temp = queue.getFront();
        temp.display();
        queue.pop();
    }
}
void QueueSystem::display()
{
    Student temp;
    int i = 1;
    cout << "正在答疑的童鞋" << endl;
    while (i <= queue.getLength())
    {
        temp = queue.getByNum(i++);
        temp.display();
    }
}
void QueueSystem::endExit()
{
    cout << "已到下班时间，请还在排队的童鞋下次再来~" << endl;
    system("pause");
    exit(0);
}
bool QueueSystem::isEmpty()
{
    return queue.isEmpty();
}
void QueueSystem::selectMenu()
{
    system("cls");
    printWelcome();

    cout << "1.排队\t2.答疑\t3.查看排队信息\t4.退出" << endl;

    int sel;
    sel = inputNumber(1, 4);
    switch (sel)
    {
    case 1:
        lineUp();
        break;
    case 2:
        lineOut();
        break;
    case 3:
        display();
        break;
    case 4:
        endExit();
        break;
    }
    system("pause");
}

int main()
{
    //设置颜色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
    QueueSystem Sys;
    while (true)
    {
        Sys.selectMenu();
        if (Sys.isEmpty())
        {
            Sys.endExit();
        }
    }
    return 0;
}