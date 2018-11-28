#include <iostream>
#include <string>
using namespace std;

string substr(char *str, int beg, int num)
{
    if(beg<0)
    {
        beg = 0;
    }
    string temp = "";
    for (int i = 0; i < num; i++)
    {
        if (*(str + beg + i)== '\0')
        {
            break;
        }
        temp += *(str+beg+i);
    }
    return temp;
}
string substr(string str, int beg, int num)
{
    if(beg<0)
    {
        beg = 0;
    }
    string temp = "";
    for (int i = 0; i < num&&i<str.length();i++)
    {
        temp += str[i];
    }
    return temp;
}

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
    if (beg>=pre.length() && in != "")
    {
        bt = new BiNode();
        bt->data = pre[beg];
        for (int i = 0; i < in.length(); i++)
        {
            if (in[i] == bt->data)
            {
                beg++;
                bt->lchild = buildTreeByPreAndIn(pre, substr(in,0, i), bt->lchild);
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
        return; //递归调用的结束条件
    else
    {
        cout << bt->data << " "; //访问根结点bt的数据域
        preOrder(bt->lchild);    //前序递归遍历bt的左子树
        preOrder(bt->rchild);    //前序递归遍历bt的右子树
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

    cout << "前序遍历序列：";
    cout << p << endl;

    cout << "中序遍历序列：";
    cout << in << endl;

    cout << endl;

    cout << "根据给定序列建历二叉树..." << endl;
    cout << "前序遍历以括号表示法打印二叉树：" << endl;
    printByPair(tree);

    return 0;
}
