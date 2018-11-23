#include <iostream>
#include <string>
using namespace std;

struct BiNode
{
    char data;

    BiNode *lchild;
    BiNode *rchild;
};

BiNode *buildTreeByPreAndIn(string pre, string in, BiNode *bt)
{
    static int beg = 0;
    bt = NULL;
    if (pre != "" && in != "")
    {
        bt = new BiNode();
        bt->data = pre[beg];
        for (int i = 0; i < in.length(); i++)
        {
            if (in[i] == bt->data)
            {
                beg++;
                bt->lchild = buildTreeByPreAndIn(pre, in.substr(0, i), bt->lchild);
                bt->rchild = buildTreeByPreAndIn(pre, in.substr(i + 1, in.length() - i - 1), bt->rchild);
                break;
            }
        }
    }
    return bt;
}

void preOrder(BiNode *bt)
{
    if (bt == NULL)
        return; //�ݹ���õĽ�������
    else
    {
        cout << bt->data << " "; //���ʸ����bt��������
        preOrder(bt->lchild);    //ǰ��ݹ����bt��������
        preOrder(bt->rchild);    //ǰ��ݹ����bt��������
    }
}

void printByPair(BiNode *bt)
{
    if (bt == NULL)
    {
        cout << '#';
    }
    else
    {
        cout << bt->data;
        cout << "(";
        printByPair(bt->lchild);
        cout << ",";
        printByPair(bt->rchild);
        cout << ")";
    }
}

int main()
{
    BiNode *tree = NULL;
    string in = "DBJHLKMNEAFCGI";
    string p = "ABDEHJKLMNCFGI";

    tree = buildTreeByPreAndIn(p, in, tree);

    cout << "ǰ��������У�";
    cout << p << endl;

    cout << "����������У�";
    cout << in << endl;

    cout << endl;

    cout << "���ݸ������н���������..." << endl;
    cout << "ǰ����������ű�ʾ����ӡ��������" << endl;
    printByPair(tree);

    return 0;
}