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
    Node *prevNode = nullptr; // previous Node指向上一个节点
    Node *nextNode = nullptr; // next Node指向下一个节点
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

//双链表
class LinkedList
{
  private:
    Node *head = new Node();
    Node *tail = new Node();
    int length;

  public:
    LinkedList();
    ~LinkedList();

    void insertNodeToHead(Node *node);               //插入节点到头部
    void insertNodeToTail(Node *node);               //插入节点到末尾
    bool insertNodeByNumber(Node *node, int number); //插入到第number位,从第0位开始

    bool deleteNodeFromHead();           //从头部删除一个节点
    bool deleteNodeFromTail();           //从尾部删除一个节点
    bool deleteNodeByNumber(int number); //删除第number位节点，从第0位开始
    void deleteList();                   //删除所有节点

    int findNodeByDate(Date d);        //根据Date信息从前往后查找第一个匹配节点位置
    Date findNodeByNumber(int number); //返回第number位的date信息

    bool modifyDateByNumber(Date d, int number); //根据把number位节点date修改为d

    void displayList(); //打印链表信息

    bool isEmpty();
    int getLength();
};
LinkedList::LinkedList()
{
    //初始化头节点
    head->prevNode = nullptr;
    head->nextNode = tail;
    //初始化尾节点
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
    //修改node的前后节点
    node->prevNode = head;
    node->nextNode = head->nextNode;
    //修改插入前头节点的后驱节点为node与原第一个节点（head后一个节点）的前驱节点为node
    head->nextNode->prevNode = node;
    head->nextNode = node;

    length++;
}
void LinkedList::insertNodeToTail(Node *n)
{
    Node *node = new Node(n);
    //修改node的前后节点
    node->prevNode = tail->prevNode;
    node->nextNode = tail;
    //修改插入前最后一个节点（tail前一个节点）的后驱节点为node与尾节点的前驱节点为node
    tail->prevNode->nextNode = node;
    tail->prevNode = node;

    length++;
}
bool LinkedList::insertNodeByNumber(Node *n, int number)
{
    if (number < 0 || number > length)
    {
        cout << "插入失败，插入节点位置不在链表长度范围" << endl;
        return false;
    }

    Node *node = new Node(n);
    Node *tempNode = nullptr; //用于插入操作的临时指针
    //如果插入位置在前半部分，从头节点向后拓展
    if (number <= length / 2)
    {
        tempNode = head;
        //从头节点向后拓展到要插入位的前一个位置
        for (int i = 0; i < number; i++)
        {
            tempNode = tempNode->nextNode;
        }
    }
    else
    {
        tempNode = tail;
        //从尾节点向前拓展到插入位的前一个位置
        for (int i = 0; i <= length - number; i++)
        {
            tempNode = tempNode->prevNode;
        }
    }
    //修改node的前后节点
    node->prevNode = tempNode;
    node->nextNode = tempNode->nextNode;
    //修改插入点前节点（tempNode）的后驱节点为node与原第number节点（tempNode后一个节点）的前驱节点为node
    tempNode->nextNode->prevNode = node;
    tempNode->nextNode = node;

    length++;
    return true;
}

bool LinkedList::deleteNodeFromHead()
{
    if (length <= 0)
    {
        cout << "删除失败，链表为空" << endl;
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
        cout << "删除失败，链表为空" << endl;
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
        cout << "删除失败，链表为空" << endl;
        return false;
    }
    if (number < 0 || number >= length)
    {
        cout << "删除失败，删除节点位置不在链表长度范围" << endl;
        return false;
    }

    Node *tempNode = nullptr; //用于删除操作的临时指针
    //如果删除位置在前半部分，从头节点向后拓展
    if (number <= length / 2)
    {
        tempNode = head;
        //从头节点向后拓展到number位
        for (int i = 0; i <= number; i++)
        {
            tempNode = tempNode->nextNode;
        }
    }
    else
    {
        tempNode = tail;
        //从尾节点向前拓展到number位
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
    cout << "没有找到匹配Date节点" << endl;
    return -1;
}
Date LinkedList::findNodeByNumber(int number)
{
    if (number < 0 || number >= length)
    {
        cout << "修改失败，修改节点位置不在链表长度范围" << endl;
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
        cout << "修改失败，链表为空" << endl;
        return false;
    }
    if (number < 0 || number >= length)
    {
        cout << "修改失败，修改节点位置不在链表长度范围" << endl;
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
