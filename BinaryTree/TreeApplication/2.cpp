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
    static int end = post.length() - 1;//自符串迭代静态变量

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
        return; //递归调用的结束条件
    else
    {
        cout << bt->data << " "; //访问根结点bt的数据域
        preOrder(bt->lchild);    //前序递归遍历bt的左子树
        preOrder(bt->rchild);    //前序递归遍历bt的右子树
    }
}

void postOrder(BiNode *bt)
{
    if (bt == NULL)
        return; //递归调用的结束条件
    else
    {
        postOrder(bt->lchild);   //前序递归遍历bt的左子树
        postOrder(bt->rchild);   //前序递归遍历bt的右子树
        cout << bt->data << " "; //访问根结点bt的数据域
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

    cout << "中序遍历序列：";
    cout << in << endl;

    cout << "后序遍历序列：";
    cout << p << endl;

    cout << endl;

    cout << "根据给定序列建历二叉树..." << endl;
    cout << "前序遍历以括号表示法打印二叉树：" << endl;
    printByPair(tree);

    return 0;
}