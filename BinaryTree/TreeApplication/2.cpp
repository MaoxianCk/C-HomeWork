#include <iostream>
#include <string>
using namespace std;

struct BiNode
{
    char data;

    BiNode *lchild;
    BiNode *rchild;
};

/*
BiNode *buildTreeByPostAndIn(string *post, string in, BiNode *bt)
{

    bt = NULL;
    if (*post != "" && in != "")
    {
        bt = new BiNode();
        bt->data = (*post)[(*post).length() - 1];

        for (int i = 0; i < in.length(); i++)
        {
            if (in[i] == bt->data)
            {
                *post = (*post).substr(0, (*post).length() - 1);
                bt->rchild = buildTreeByPostAndIn(post, in.substr(i + 1, in.length() - i - 1), bt->rchild);
                bt->lchild = buildTreeByPostAndIn(post, in.substr(0, i), bt->lchild);
                break;
            }
        }
    }
    return bt;
}
*/

BiNode *buildTreeByPostAndIn(string post, string in, BiNode *bt)
{
    static int end = post.length() - 1;//�Է���������̬����

    bt = NULL;
    if (end != -1 && in != "")
    {
        bt = new BiNode();
        bt->data = post[end];

        for (int i = 0; i < in.length(); i++)
        {
            if (in[i] == bt->data)
            {
                end--;
                bt->rchild = buildTreeByPostAndIn(post, in.substr(i + 1, in.length() - i - 1), bt->rchild);
                bt->lchild = buildTreeByPostAndIn(post, in.substr(0, i), bt->lchild);
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

void postOrder(BiNode *bt)
{
    if (bt == NULL)
        return; //�ݹ���õĽ�������
    else
    {
        postOrder(bt->lchild);   //ǰ��ݹ����bt��������
        postOrder(bt->rchild);   //ǰ��ݹ����bt��������
        cout << bt->data << " "; //���ʸ����bt��������
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
    string p = "DJLNMKHEBFIGCA";

    tree = buildTreeByPostAndIn(p, in, tree);

    cout << "����������У�";
    cout << in << endl;

    cout << "����������У�";
    cout << p << endl;

    cout << endl;

    cout << "���ݸ������н���������..." << endl;
    cout << "ǰ����������ű�ʾ����ӡ��������" << endl;
    printByPair(tree);

    return 0;
}