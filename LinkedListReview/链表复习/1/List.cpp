#include <iostream>
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
    Type getNode(int num);
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
    while (head->next != nullptr)
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
}
template <class Type>
Type SinglyList<Type>::getNode(int num)
{
    Type data;
    Node<Type> *temp = head->next;
    while (--num)
    {
        temp = temp->next;
    }
    data = temp->data;
    return data;
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
    bool judgeRule()
    {
        bool flag = true;
        Node<int> *temp = head; //��ͷ�ڵ�ĵ�����
        int nextCnt = 1;
        if (temp->next == nullptr)
        {
            //ɶҲû�е�Ȼ����չ��ﳵ��~~~~~~~~~~
            return true;
        }
        while (temp->next->next != nullptr)
        {
            //cout << nextCnt << " " << flag << endl;
            //�Ƚ������жϣ���һ���Ƚ�������һ���ڵ� ����һ���ڵ㲻Ϊ��
            temp = temp->next;
            nextCnt++;
            if ((temp->data) != (nextCnt * 3))
            {
                //cout << nextCnt << " " << flag << endl;
                flag = false;
                break;
            }
        }
        temp = temp->next;
        if (temp->next == nullptr && temp != head) //�����ǰ�ڵ㲻��ͷ�ڵ㲢����һ����Ϊ��
        {
            if ((temp->data) != 0)
            {
                flag = false;
            }
        }
        return flag;
    }
};

int main()
{
    cout << "����0-5����ȷ��������..." << endl;
    for (int testNum = 0; testNum < 6; testNum++) //���Ե�������
    {
        F a;
        for (int i = 0; i < testNum; i++)
        {
            if (i == 0)
            {
                a.insertNode(1, 0);
            }
            else if (i >= 1 && i < testNum)
            {
                a.insertNode(1, (testNum - i + 1) * 3);
            }
        }
        a.display();
        cout << (a.judgeRule() ? "�ҵĹ��ﳵ������ˣ�������" : "˫11��������") << endl;
        cout << endl;
    }

    int testNum2 = 5;

    cout << "����������..." << endl;
    F b;
    //a.insertNode(1, 0);
    for (int i = 0; i < testNum2 - 1; i++)
    {
        b.insertNode(1, (testNum2 - i) * 3);
    }
    b.display();
    cout << (b.judgeRule() ? "�ҵĹ��ﳵ������ˣ�������" : "˫11��������") << endl;
    cout << endl;

    F c;
    c.insertNode(1, 0);
    for (int i = 0; i < testNum2 - 1; i++)
    {
        c.insertNode(1, (testNum2 - i) * 3);
    }
    c.delNode(3);
    c.display();
    cout << (c.judgeRule() ? "�ҵĹ��ﳵ������ˣ�������" : "˫11��������") << endl;
    cout << endl;

    cout << "���밸������..." << endl;
    int L;
    cout << "��������԰���������";
    int times;
    cin >> times;

    cout << endl;
    while (times--)
    {
        cout << "���������������";
        cin >> L;
        F d;
        for (int i = 0; i < L; i++)
        {
            int t;
            cout << "�������" << i + 1 << "��Ԫ��ֵ:";
            cin >> t;
            d.insertNode(i + 1, t);
        }
        d.display();
        cout << (d.judgeRule() ? "�ҵĹ��ﳵ������ˣ�������" : "˫11��������") << endl;
        cout << endl;
    }
    return 0;
}