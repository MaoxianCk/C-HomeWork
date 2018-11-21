#include <iostream>
#include <string>
using namespace std;

template <class DataType>
struct BiNode
{
	DataType data;
	BiNode<DataType> *lchild, *rchild;
};

template <class DataType>
class BiTree
{
  public:
	BiTree();							  //构造函数
	~BiTree();							  //析构函数
	void PreOrder(BiNode<DataType> *bt);  //前序遍历函数
	void InOrder(BiNode<DataType> *bt);   //中序遍历函数
	void PostOrder(BiNode<DataType> *bt); //后序遍历函数
	void LeverOrder();					  //层序遍历函数
  private:
	BiNode<DataType> *root; //指向根结点的头指针
};

template <class DataType>
BiTree<DataType>::BiTree()
{
	//自己实现二叉树的构造
	//...
	
}

template <class DataType>
BiTree<DataType>::~BiTree()
{
	//自己实现二叉树的销毁
	//...
}

template <class DataType>
void BiTree<DataType>::PreOrder(BiNode<DataType> *bt)
{
	if (bt == NULL)
		return; //递归调用的结束条件
	else
	{
		cout << bt->data << " "; //访问根结点bt的数据域
		PreOrder(bt->lchild);	//前序递归遍历bt的左子树
		PreOrder(bt->rchild);	//前序递归遍历bt的右子树
	}
}

template <class DataType>
void BiTree<DataType>::InOrder(BiNode<DataType> *bt)
{
	if (bt == NULL)
		return; //递归调用的结束条件
	else
	{
		InOrder(bt->lchild);	 //中序递归遍历bt的左子树
		cout << bt->data << " "; //访问根结点bt的数据域
		InOrder(bt->rchild);	 //中序递归遍历bt的右子树
	}
}

template <class DataType>
void BiTree<DataType>::PostOrder(BiNode<DataType> *bt)
{
	if (bt == NULL)
		return; //递归调用的结束条件
	else
	{
		PostOrder(bt->lchild);   //后序递归遍历bt的左子树
		PostOrder(bt->rchild);   //后序递归遍历bt的右子树
		cout << bt->data << " "; //访问根结点bt的数据域
	}
}

template <class DataType>
void BiTree<DataType>::LeverOrder()
{
	int front = -1, rear = -1; //采用顺序队列，并假定不会发生上溢
	BiNode<DataType> *Q[100];
	BiNode<DataType> *q;
	if (root == NULL)
		return;			  //二叉树为空，算法结束
	Q[++rear] = root;	 //根指针入队
	while (front != rear) //当队列非空时
	{
		q = Q[++front]; //出队
		cout << q->data << " ";
		if (q->lchild != NULL)
			Q[++rear] = q->lchild;
		if (q->rchild != NULL)
			Q[++rear] = q->rchild;
	}
}

int main()
{
	//主函数自己写
	//要求：先构造二叉树,再实现二叉树的前序、中序、后序、层序遍历
	//...
	//友情提示：
	//你可能会发现,二叉树以这样的方式定义,主函数要写很长
	//因为你要在主函数中使用头指针root,就必须要开放私有成员root的访问权限,即要有public的getRoot方法
	//...还有更多更麻烦的处理
	//...
	//...
	//现在请你梳理一下main函数的实现思路
	//...(开始紧锁眉头地思考...)
	//...(好像想不出来..)
	//如果实在想不出来，你也可以放弃
	//因为此段代码主要是为了让你比较tree.cpp与tree_1.cpp哪种实现方式更简洁，而不是真的想让你实现它
	//...
	//...
	//再憋了一会儿...
	//终于好像有点头绪了...
	//...
	//XXX同学举起手来，" 老师，我知道为什么了。"
	//老师说："好！请你告诉我哪种实现方式更简洁,并告诉我为什么。如果答对, 我会奖励你买一颗QQ糖的分数。"
	//XXX同学说："!@#$%^&*()"
	//...
	//"很好！",老师说。
	//...
	//没错，你就是这位同学。下节课告诉我吧！
	//...
	//...(未完待续)
}
