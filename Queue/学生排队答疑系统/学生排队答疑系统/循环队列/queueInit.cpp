#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

int inputNumber(int a, int b) //��Χa b ��������
{
    string str;
    while (true)
    {
        bool flag = true; //����Ƿ�����
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
                cout << "���������������������!" << endl;
                continue;
            }
            return num;
        }
        else
        {
            cout << "���������������������!" << endl;
            continue;
        }
    }
}
int inputNumber()
{
    string str;
    while (true)
    {
        bool flag = true; //����Ƿ�����
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
            cout << "����������!" << endl;
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
        cout << "ѧ�ţ�" << id << "\t������" << name << endl;
    }
};
template <class Type>
class Queue
{
  private:
    int queueSize;
    int front, rear;
    Type *data;

  public:
    Queue();
    //Queue(int size);
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
    queueSize = 200;
    front = rear = queueSize - 1;
    data = new Type[queueSize];
}
template <class Type>
Queue<Type>::~Queue()
{
    delete[] data;
}
template <class Type>
bool Queue<Type>::push(Type d)
{
    if ((rear + 1) % queueSize == front)
    {
        cout << "����" << endl;
        return false;
    }
    rear = (rear + 1) % queueSize;
    data[rear] = d;
    return true;
}
template <class Type>
Type Queue<Type>::pop()
{
    if (rear == front)
    {
        cout << "����" << endl;
        system("pause");
        exit(1);
    }
    front = (front + 1) % queueSize;
    Type temp = data[front];
    return temp;
}
template <class Type>
Type Queue<Type>::getByNum(int num)
{
    int length = (rear - front + queueSize) % queueSize;
    if (num > length || num < 1)
    {
        cout << "���Ҵ���û��numλ�ڵ�" << endl;
        num = 1;
    }
    int i = front;
    int cnt = 1;
    while (cnt <= num)
    {
        i = (i + 1) % queueSize;
        cnt++;
    }
    return data[i];
}
template <class Type>
int Queue<Type>::getLength()
{
    return (rear - front + queueSize) % queueSize;
}
template <class Type>
bool Queue<Type>::isEmpty()
{
    return (front == rear ? true : false);
}
template <class Type>
Type Queue<Type>::getFront()
{
    return data[(front + 1) % queueSize];
}

class QueueSystem
{
  private:
    Queue<Student> queue;

  public:
    void printWelcome();
    void selectMenu();
    void lineUp();  //�Ŷ�
    void lineOut(); //����
    void display(); //����
    void endExit();
    bool isEmpty();
};
void QueueSystem::printWelcome()
{
    cout << "   %---��ӭ�������ϵͳ---%" << endl;
}
void QueueSystem::lineUp()
{
    Student temp;
    cout << "������ѧ�ţ�";
    cin >> temp.id;
    cout << "������������";
    cin >> temp.name;

    if (queue.push(temp))
    {
        cout << "��ӳɹ���";
    }
    else
    {
        cout << "���ʧ�ܣ�����������";
    }
}
void QueueSystem::lineOut()
{
    if (queue.isEmpty())
    {
        cout << "Ŀǰû�����ڴ��ɣ�";
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
    cout << "���ڴ��ɵ�ͯЬ" << endl;
    while (i <= queue.getLength())
    {
        temp = queue.getByNum(i++);
        temp.display();
    }
}
void QueueSystem::endExit()
{
    cout << "�ѵ��°�ʱ�䣬�뻹���Ŷӵ�ͯЬ�´�����~" << endl;
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

    cout << "1.�Ŷ�\t2.����\t3.�鿴�Ŷ���Ϣ\t4.�˳�" << endl;

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
    //������ɫ
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