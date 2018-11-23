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
        Node<int> *temp = head; //带头节点的单链表
        int nextCnt = 1;
        if (temp->next == nullptr)
        {
            //啥也没有当然就清空购物车啦~~~~~~~~~~
            return true;
        }
        while (temp->next->next != nullptr)
        {
            //cout << nextCnt << " " << flag << endl;
            //先交换再判断，第一次先交换至第一个节点 若下一个节点不为空
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
        if (temp->next == nullptr && temp != head) //如果当前节点不是头节点并且下一个域为空
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
    cout << "长度0-5的正确案例测试..." << endl;
    for (int testNum = 0; testNum < 6; testNum++) //测试的链表长度
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
        cout << (a.judgeRule() ? "我的购物车被清空了，哈哈哈" : "双11，不存在") << endl;
        cout << endl;
    }

    int testNum2 = 5;

    cout << "错误案例测试..." << endl;
    F b;
    //a.insertNode(1, 0);
    for (int i = 0; i < testNum2 - 1; i++)
    {
        b.insertNode(1, (testNum2 - i) * 3);
    }
    b.display();
    cout << (b.judgeRule() ? "我的购物车被清空了，哈哈哈" : "双11，不存在") << endl;
    cout << endl;

    F c;
    c.insertNode(1, 0);
    for (int i = 0; i < testNum2 - 1; i++)
    {
        c.insertNode(1, (testNum2 - i) * 3);
    }
    c.delNode(3);
    c.display();
    cout << (c.judgeRule() ? "我的购物车被清空了，哈哈哈" : "双11，不存在") << endl;
    cout << endl;

    cout << "输入案例测试..." << endl;
    int L;
    cout << "请输入测试案例数量：";
    int times;
    cin >> times;

    cout << endl;
    while (times--)
    {
        cout << "请输入插入数量：";
        cin >> L;
        F d;
        for (int i = 0; i < L; i++)
        {
            int t;
            cout << "请输入第" << i + 1 << "个元素值:";
            cin >> t;
            d.insertNode(i + 1, t);
        }
        d.display();
        cout << (d.judgeRule() ? "我的购物车被清空了，哈哈哈" : "双11，不存在") << endl;
        cout << endl;
    }
    return 0;
}