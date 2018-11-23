#include <iostream>
#include <string>
using namespace std;

template <class DataType>
struct BiNode
{
	DataType data;
	BiNode<DataType> *lchild, *rchild;
};


template<class DataType>
class BiTree
{
	public:
		BiTree()
		{
			root = Creat(root);   //构造函数，建立一棵二叉树
		}
		~BiTree()
		{
			Release(root);   //析构函数
		}
		void PreOrder()
		{
			PreOrder(root);   //前序遍历二叉树
		}
		void InOrder()
		{
			InOrder(root);   //中序遍历二叉树
		}
		void PostOrder()
		{
			PostOrder(root);   //后序遍历二叉树
		}
		int getDepth()
		{
			return getDepth(root);
		}
		int getNodeNum()
		{
			return getNodeNum(root);
		}
		void PreOrderLeaf()
		{
			PreOrderLeaf(root);
		}
		void LeverOrder();                              //层序遍历二叉树
	private:
		BiNode<DataType> *root;                    //指向根结点的头指针
		BiNode<DataType> *Creat(BiNode<DataType> *bt);    //构造函数调用
		void Release(BiNode<DataType> *bt);               //析构函数调用
		void PreOrder(BiNode<DataType> *bt);          //前序遍历函数调用
		void InOrder(BiNode<DataType> *bt);             //中序遍历函数调用
		void PostOrder(BiNode<DataType> *bt);         //后序遍历函数调用

		//********//
		int getDepth(BiNode<DataType> *bt);
		int getNodeNum(BiNode<DataType> *bt);
		void PreOrderLeaf(BiNode<DataType> *bt);
};

template <class DataType>
BiNode<DataType> *BiTree<DataType>::Creat(BiNode<DataType> *bt)
{
	char ch;
	cin >> ch;                      //输入结点的数据信息，假设为字符
	if (ch == '#')
		{
			bt = NULL;                //建立一棵空树
		}
	else
		{
			bt = new BiNode<DataType>;
			bt->data = ch;  //生成一个结点，数据域为ch
			bt->lchild = Creat(bt->lchild);//递归建立左子树
			bt->rchild = Creat(bt->rchild);//递归建立右子树
		}
	return bt;
}

template <class DataType>
void BiTree<DataType>::Release(BiNode<DataType> *bt)
{
	if(bt != NULL)
		{
			Release(bt->lchild);
			Release(bt->rchild);
			delete bt;
		}
}

template <class DataType>
void BiTree<DataType>::PreOrder(BiNode<DataType> *bt)
{
	if (bt == NULL)  return;              //递归调用的结束条件
	else
		{
			cout << bt->data << " ";          //访问根结点bt的数据域
			PreOrder(bt->lchild);             //前序递归遍历bt的左子树
			PreOrder(bt->rchild);             //前序递归遍历bt的右子树
		}
}

template<class DataType>
void BiTree<DataType>::InOrder(BiNode<DataType> *bt)
{
	if (bt == NULL) return;                 //递归调用的结束条件
	else
		{
			InOrder(bt->lchild);                 //中序递归遍历bt的左子树
			cout << bt->data << " ";            //访问根结点bt的数据域
			InOrder(bt->rchild);                //中序递归遍历bt的右子树
		}
}

template <class DataType>
void BiTree<DataType>::PostOrder(BiNode<DataType> *bt)
{
	if (bt == NULL) return;                //递归调用的结束条件
	else
		{
			PostOrder(bt->lchild);              //后序递归遍历bt的左子树
			PostOrder(bt->rchild);             //后序递归遍历bt的右子树
			cout << bt->data << " ";                      //访问根结点bt的数据域
		}
}


template<class DataType>
void BiTree<DataType>::LeverOrder()
{
	int front = -1,rear = -1;         //采用顺序队列，并假定不会发生上溢
	BiNode<DataType> *Q[100];
	BiNode<DataType> *q;
	if (root == NULL) return;        //二叉树为空，算法结束
	Q[++rear] = root;                      //根指针入队
	while (front != rear)                  //当队列非空时
		{
			q = Q[++front];                    //出队
			cout << q->data << " ";
			if (q->lchild != NULL)  Q[++rear] = q->lchild;
			if (q->rchild != NULL)  Q[++rear] = q->rchild;
		}
}

template<class DataType>
int BiTree<DataType>::getDepth(BiNode<DataType> *bt)
{
	if(bt==NULL)
		{
			return 0;
		}
	int ldepth=getDepth(bt->lchild);
	int rdepth=getDepth(bt->rchild);
	return ((ldepth>rdepth?ldepth:rdepth)+1);
}

template<class DataType>
int BiTree<DataType>::getNodeNum(BiNode<DataType> *bt)
{
	if(bt==NULL)
		{
			return 0;
		}
	int lnodeNum=getNodeNum(bt->lchild);
	int rnodeNum=getNodeNum(bt->rchild);

	return lnodeNum+rnodeNum+1;//左子树结点数 加上 右子树结点数 加 根结点
}

template<class DataType>
void BiTree<DataType>::PreOrderLeaf(BiNode<DataType> *bt)
{
	if (bt == NULL)  return;              //递归调用的结束条件
	else
		{
			if(bt->lchild==NULL && bt->rchild==NULL)
				{
					cout << bt->data << " ";          //访问根结点bt的数据域
					return ;
				}
			PreOrderLeaf(bt->lchild);             //前序递归遍历bt的左子树
			PreOrderLeaf(bt->rchild);             //前序递归遍历bt的右子树
		}

}

int main()
{
	BiTree<char> *tree = new BiTree<char>();
	cout << "前序遍历：";
	tree->PreOrder();
	cout << endl;

	cout << "中序遍历：";
	tree->InOrder();
	cout << endl;

	cout << "后序遍历：";
	tree->PostOrder();
	cout << endl;

	cout << "层序遍历：";
	tree->LeverOrder();
	cout << endl;

	cout<<"深度：";
	cout<<tree->getDepth();
	cout<<endl;

	cout<<"结点个数：";
	cout<<tree->getNodeNum();
	cout<<endl;

	cout<<"前序遍历叶子结点：";
	tree->PreOrderLeaf();
	cout<<endl;

	delete tree;


	return 0;
}
