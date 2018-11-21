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
    void insertNodeOrder(int d)
    {
        Node<int> *newNode = new Node<int>;
        newNode->data = d;

        Node<int> *temp = head;
        while (temp->next != nullptr)
        {
            if (temp->next->data > d)
            {
                break;
            }
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
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
    cout << (512 << 16);
    return 0;
}
