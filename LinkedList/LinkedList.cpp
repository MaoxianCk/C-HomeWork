#include <iostream>
using namespace std;

struct Date
{
    int number;
    Date()
    {
        number = 0;
    }
    Date(int n)
    {
        number = n;
    }
    bool operator==(Date d)
    {
        if (number == d.number)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Node
{
  public:
    Node();
    Node(int number);
    Node(Node *node);
    Date date;
    Node *prevNode = nullptr; // previous Nodeָ����һ���ڵ�
    Node *nextNode = nullptr; // next Nodeָ����һ���ڵ�
};
Node::Node()
{
    date.number = 0;
}
Node::Node(int number)
{
    date.number = number;
}
Node::Node(Node *node)
{
    date = node->date;
}

//˫����
class LinkedList
{
  private:
    Node *head = new Node();
    Node *tail = new Node();
    int length;

  public:
    LinkedList();
    ~LinkedList();

    void insertNodeToHead(Node *node);               //����ڵ㵽ͷ��
    void insertNodeToTail(Node *node);               //����ڵ㵽ĩβ
    bool insertNodeByNumber(Node *node, int number); //���뵽��numberλ,�ӵ�0λ��ʼ

    bool deleteNodeFromHead();           //��ͷ��ɾ��һ���ڵ�
    bool deleteNodeFromTail();           //��β��ɾ��һ���ڵ�
    bool deleteNodeByNumber(int number); //ɾ����numberλ�ڵ㣬�ӵ�0λ��ʼ
    void deleteList();                   //ɾ�����нڵ�

    int findNodeByDate(Date d);        //����Date��Ϣ��ǰ������ҵ�һ��ƥ��ڵ�λ��
    Date findNodeByNumber(int number); //���ص�numberλ��date��Ϣ

    bool modifyDateByNumber(Date d, int number); //���ݰ�numberλ�ڵ�date�޸�Ϊd

    void displayList(); //��ӡ������Ϣ

    bool isEmpty();
    int getLength();
};
LinkedList::LinkedList()
{
    //��ʼ��ͷ�ڵ�
    head->prevNode = nullptr;
    head->nextNode = tail;
    //��ʼ��β�ڵ�
    tail->prevNode = head;
    tail->nextNode = nullptr;

    length = 0;
}
LinkedList::~LinkedList()
{
    deleteList();
}
void LinkedList::insertNodeToHead(Node *n)
{
    Node *node = new Node(n);
    //�޸�node��ǰ��ڵ�
    node->prevNode = head;
    node->nextNode = head->nextNode;
    //�޸Ĳ���ǰͷ�ڵ�ĺ����ڵ�Ϊnode��ԭ��һ���ڵ㣨head��һ���ڵ㣩��ǰ���ڵ�Ϊnode
    head->nextNode->prevNode = node;
    head->nextNode = node;

    length++;
}
void LinkedList::insertNodeToTail(Node *n)
{
    Node *node = new Node(n);
    //�޸�node��ǰ��ڵ�
    node->prevNode = tail->prevNode;
    node->nextNode = tail;
    //�޸Ĳ���ǰ���һ���ڵ㣨tailǰһ���ڵ㣩�ĺ����ڵ�Ϊnode��β�ڵ��ǰ���ڵ�Ϊnode
    tail->prevNode->nextNode = node;
    tail->prevNode = node;

    length++;
}
bool LinkedList::insertNodeByNumber(Node *n, int number)
{
    if (number < 0 || number > length)
    {
        cout << "����ʧ�ܣ�����ڵ�λ�ò��������ȷ�Χ" << endl;
        return false;
    }

    Node *node = new Node(n);
    Node *tempNode = nullptr; //���ڲ����������ʱָ��
    //�������λ����ǰ�벿�֣���ͷ�ڵ������չ
    if (number <= length / 2)
    {
        tempNode = head;
        //��ͷ�ڵ������չ��Ҫ����λ��ǰһ��λ��
        for (int i = 0; i < number; i++)
        {
            tempNode = tempNode->nextNode;
        }
    }
    else
    {
        tempNode = tail;
        //��β�ڵ���ǰ��չ������λ��ǰһ��λ��
        for (int i = 0; i <= length - number; i++)
        {
            tempNode = tempNode->prevNode;
        }
    }
    //�޸�node��ǰ��ڵ�
    node->prevNode = tempNode;
    node->nextNode = tempNode->nextNode;
    //�޸Ĳ����ǰ�ڵ㣨tempNode���ĺ����ڵ�Ϊnode��ԭ��number�ڵ㣨tempNode��һ���ڵ㣩��ǰ���ڵ�Ϊnode
    tempNode->nextNode->prevNode = node;
    tempNode->nextNode = node;

    length++;
    return true;
}

bool LinkedList::deleteNodeFromHead()
{
    if (length <= 0)
    {
        cout << "ɾ��ʧ�ܣ�����Ϊ��" << endl;
        return false;
    }

    Node *tempNode = head->nextNode;
    head->nextNode = tempNode->nextNode;
    head->nextNode->prevNode = head;

    tempNode->prevNode = nullptr;
    tempNode->nextNode = nullptr;
    delete tempNode;
    tempNode = nullptr;

    length--;
    return true;
}
bool LinkedList::deleteNodeFromTail()
{
    if (length <= 0)
    {
        cout << "ɾ��ʧ�ܣ�����Ϊ��" << endl;
        return false;
    }

    Node *tempNode = tail->prevNode;
    tail->prevNode = tempNode->prevNode;
    tail->prevNode->nextNode = tail;

    tempNode->prevNode = nullptr;
    tempNode->nextNode = nullptr;
    delete tempNode;
    tempNode = nullptr;

    length--;
    return true;
}
bool LinkedList::deleteNodeByNumber(int number)
{
    if (length <= 0)
    {
        cout << "ɾ��ʧ�ܣ�����Ϊ��" << endl;
        return false;
    }
    if (number < 0 || number >= length)
    {
        cout << "ɾ��ʧ�ܣ�ɾ���ڵ�λ�ò��������ȷ�Χ" << endl;
        return false;
    }

    Node *tempNode = nullptr; //����ɾ����������ʱָ��
    //���ɾ��λ����ǰ�벿�֣���ͷ�ڵ������չ
    if (number <= length / 2)
    {
        tempNode = head;
        //��ͷ�ڵ������չ��numberλ
        for (int i = 0; i <= number; i++)
        {
            tempNode = tempNode->nextNode;
        }
    }
    else
    {
        tempNode = tail;
        //��β�ڵ���ǰ��չ��numberλ
        for (int i = 0; i < length - number; i++)
        {
            tempNode = tempNode->prevNode;
        }
    }
    tempNode->prevNode->nextNode = tempNode->nextNode;
    tempNode->nextNode->prevNode = tempNode->prevNode;

    tempNode->prevNode = nullptr;
    tempNode->nextNode = nullptr;
    delete tempNode;
    tempNode = nullptr;

    length--;
    return true;
}
void LinkedList::deleteList()
{
    while (!isEmpty())
    {
        deleteNodeFromHead();
    }
}

int LinkedList::findNodeByDate(Date d)
{
    int number = 0;
    Node *tempNode = head->nextNode;
    while (tempNode != tail)
    {
        if (tempNode->date == d)
        {
            return number;
        }
        tempNode = tempNode->nextNode;
        number++;
    }
    cout << "û���ҵ�ƥ��Date�ڵ�" << endl;
    return -1;
}
Date LinkedList::findNodeByNumber(int number)
{
    if (number < 0 || number >= length)
    {
        cout << "�޸�ʧ�ܣ��޸Ľڵ�λ�ò��������ȷ�Χ" << endl;
        return false;
    }
    Node *tempNode = head->nextNode;
    for (int i = 0; i < number; i++)
    {
        tempNode = tempNode->nextNode;
    }
    Date tempDate = tempNode->date;
    return tempDate;
}

bool LinkedList::modifyDateByNumber(Date d, int number)
{
    if (length <= 0)
    {
        cout << "�޸�ʧ�ܣ�����Ϊ��" << endl;
        return false;
    }
    if (number < 0 || number >= length)
    {
        cout << "�޸�ʧ�ܣ��޸Ľڵ�λ�ò��������ȷ�Χ" << endl;
        return false;
    }

    Node *tempNode = head->nextNode;
    for (int i = 0; i < number; i++)
    {
        tempNode = tempNode->nextNode;
    }
    tempNode->date = d;
    return true;
}

void LinkedList::displayList()
{
    Node *tempNode = head->nextNode;

    cout << "*********************" << endl;
    cout << "   head" << endl;
    int cnt = 0;
    while (tempNode != tail)
    {
        cout << "ID:" << cnt << "\tDate:" << tempNode->date.number << endl;
        tempNode = tempNode->nextNode;
        cnt++;
    }
    cout << "   tail" << endl;
}
bool LinkedList::isEmpty()
{
    if (length <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int LinkedList::getLength()
{
    return length;
}

int main()
{
    int a[5];
    int *p, *p1;
    p = a;
    p1 = (a + 1);
    cout << p << ' ' << p1;
    system("pause");
    return 0;
}
