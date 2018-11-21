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
			root = Creat(root);   //���캯��������һ�ö�����
		}
		~BiTree()
		{
			Release(root);   //��������
		}
		void PreOrder()
		{
			PreOrder(root);   //ǰ�����������
		}
		void InOrder()
		{
			InOrder(root);   //�������������
		}
		void PostOrder()
		{
			PostOrder(root);   //�������������
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
		void LeverOrder();                              //�������������
	private:
		BiNode<DataType> *root;                    //ָ�������ͷָ��
		BiNode<DataType> *Creat(BiNode<DataType> *bt);    //���캯������
		void Release(BiNode<DataType> *bt);               //������������
		void PreOrder(BiNode<DataType> *bt);          //ǰ�������������
		void InOrder(BiNode<DataType> *bt);             //���������������
		void PostOrder(BiNode<DataType> *bt);         //���������������

		//********//
		int getDepth(BiNode<DataType> *bt);
		int getNodeNum(BiNode<DataType> *bt);
		void PreOrderLeaf(BiNode<DataType> *bt);
};

template <class DataType>
BiNode<DataType> *BiTree<DataType>::Creat(BiNode<DataType> *bt)
{
	char ch;
	cin >> ch;                      //�������������Ϣ������Ϊ�ַ�
	if (ch == '#')
		{
			bt = NULL;                //����һ�ÿ���
		}
	else
		{
			bt = new BiNode<DataType>;
			bt->data = ch;  //����һ����㣬������Ϊch
			bt->lchild = Creat(bt->lchild);//�ݹ齨��������
			bt->rchild = Creat(bt->rchild);//�ݹ齨��������
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
	if (bt == NULL)  return;              //�ݹ���õĽ�������
	else
		{
			cout << bt->data << " ";          //���ʸ����bt��������
			PreOrder(bt->lchild);             //ǰ��ݹ����bt��������
			PreOrder(bt->rchild);             //ǰ��ݹ����bt��������
		}
}

template<class DataType>
void BiTree<DataType>::InOrder(BiNode<DataType> *bt)
{
	if (bt == NULL) return;                 //�ݹ���õĽ�������
	else
		{
			InOrder(bt->lchild);                 //����ݹ����bt��������
			cout << bt->data << " ";            //���ʸ����bt��������
			InOrder(bt->rchild);                //����ݹ����bt��������
		}
}

template <class DataType>
void BiTree<DataType>::PostOrder(BiNode<DataType> *bt)
{
	if (bt == NULL) return;                //�ݹ���õĽ�������
	else
		{
			PostOrder(bt->lchild);              //����ݹ����bt��������
			PostOrder(bt->rchild);             //����ݹ����bt��������
			cout << bt->data << " ";                      //���ʸ����bt��������
		}
}


template<class DataType>
void BiTree<DataType>::LeverOrder()
{
	int front = -1,rear = -1;         //����˳����У����ٶ����ᷢ������
	BiNode<DataType> *Q[100];
	BiNode<DataType> *q;
	if (root == NULL) return;        //������Ϊ�գ��㷨����
	Q[++rear] = root;                      //��ָ�����
	while (front != rear)                  //�����зǿ�ʱ
		{
			q = Q[++front];                    //����
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

	return lnodeNum+rnodeNum+1;//����������� ���� ����������� �� �����
}

template<class DataType>
void BiTree<DataType>::PreOrderLeaf(BiNode<DataType> *bt)
{
	if (bt == NULL)  return;              //�ݹ���õĽ�������
	else
		{
			if(bt->lchild==NULL && bt->rchild==NULL)
				{
					cout << bt->data << " ";          //���ʸ����bt��������
					return ;
				}
			PreOrderLeaf(bt->lchild);             //ǰ��ݹ����bt��������
			PreOrderLeaf(bt->rchild);             //ǰ��ݹ����bt��������
		}

}

int main()
{
	BiTree<char> *tree = new BiTree<char>();
	cout << "ǰ�������";
	tree->PreOrder();
	cout << endl;

	cout << "���������";
	tree->InOrder();
	cout << endl;

	cout << "���������";
	tree->PostOrder();
	cout << endl;

	cout << "���������";
	tree->LeverOrder();
	cout << endl;

	cout<<"��ȣ�";
	cout<<tree->getDepth();
	cout<<endl;

	cout<<"��������";
	cout<<tree->getNodeNum();
	cout<<endl;

	cout<<"ǰ�����Ҷ�ӽ�㣺";
	tree->PreOrderLeaf();
	cout<<endl;

	delete tree;


	return 0;
}
