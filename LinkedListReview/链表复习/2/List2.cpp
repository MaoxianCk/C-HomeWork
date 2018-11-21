#include <algorithm>
#include <iostream>
#include <time.h>
using namespace std;

template <class Type>
struct Node
{
    Type data;
    Node *next;
};
template <class Type>
class SinglyList
{
  protected:
    Node<Type> *head;
    int length;

  public:
    SinglyList();
    ~SinglyList();
    void insertNode(int num, Type d);
    void delNode(int num);
    bool empty();
    void setEmpty();
};
template <class Type>
SinglyList<Type>::SinglyList()
{
    head = new Node<Type>;
    head->next = nullptr;
    length = 0;
}
template <class Type>
SinglyList<Type>::~SinglyList()
{
    while (!empty())
    {
        delNode(1);
    }
    delete head;
}
template <class Type>
void SinglyList<Type>::insertNode(int num, Type d)
{
    Node<Type> *newNode = new Node<Type>;
    Node<Type> *temp = head;
    newNode->data = d;

    while (--num)
    {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    length++;
}
template <class Type>
void SinglyList<Type>::delNode(int num)
{
    Node<Type> *delNode;
    Node<Type> *temp = head;
    while (--num)
    {
        temp = temp->next;
    }
    delNode = temp->next;
    temp->next = delNode->next;
    delete delNode;
    length--;
}
template <class Type>
bool SinglyList<Type>::empty()
{
    return (head->next == nullptr ? true : false);
}
template <class Type>
void SinglyList<Type>::setEmpty()
{
    while (!empty())
    {
        delNode(1);
    }
}

class F : public SinglyList<int>
{
  public:
    void display()
    {
        Node<int> *temp = head->next;
        cout << "First -> ";
        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }
    void bubbleSort()
    {
        Node<int> *cur, *tail;
        cur = head->next;
        tail = nullptr;
        while (cur != tail)
        {
            while (cur->next != tail)
            {
                if (cur->data > cur->next->data)
                {
                    int temp = cur->data;
                    cur->data = cur->next->data;
                    cur->next->data = temp;
                }
                cur = cur->next;
            }
            tail = cur;
            cur = head->next;
        }
    }
};

int main()
{
    srand((int)time(0));
    while (true)
    {
        cout << "请输入测试数值个数(输入0结束)：";
        int n;
        cin >> n;
        if(n==0)
        {
            break;
        }
        int *a = new int[n];
        cout << "随机产生" << n << "个[0,100]数字：";
        for (int i = 0; i < n; i++)
        {
            a[i] = rand() % 101;
            cout << a[i] << " ";
        }
        cout << endl;

        //链表冒泡排序法
        F list;
        for (int i = 0; i < n; i++)
        {
            list.insertNode(i + 1, a[i]);
        }
        cout << "原链表：" << endl;
        list.display();

        list.bubbleSort();
        cout << "冒泡排序后：" << endl;
        list.display();

        list.setEmpty();
        cout << "排序数组后插入:" << endl;
        sort(a, a + n);
        for (int i = 0; i < n; i++)
        {
            list.insertNode(i + 1, a[i]);
        }
        list.display();
    }
    cout << "程序结束..." << endl;
    return 0;
}
