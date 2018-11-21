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
	BiTree();							  //���캯��
	~BiTree();							  //��������
	void PreOrder(BiNode<DataType> *bt);  //ǰ���������
	void InOrder(BiNode<DataType> *bt);   //�����������
	void PostOrder(BiNode<DataType> *bt); //�����������
	void LeverOrder();					  //�����������
  private:
	BiNode<DataType> *root; //ָ�������ͷָ��
};

template <class DataType>
BiTree<DataType>::BiTree()
{
	//�Լ�ʵ�ֶ������Ĺ���
	//...
	
}

template <class DataType>
BiTree<DataType>::~BiTree()
{
	//�Լ�ʵ�ֶ�����������
	//...
}

template <class DataType>
void BiTree<DataType>::PreOrder(BiNode<DataType> *bt)
{
	if (bt == NULL)
		return; //�ݹ���õĽ�������
	else
	{
		cout << bt->data << " "; //���ʸ����bt��������
		PreOrder(bt->lchild);	//ǰ��ݹ����bt��������
		PreOrder(bt->rchild);	//ǰ��ݹ����bt��������
	}
}

template <class DataType>
void BiTree<DataType>::InOrder(BiNode<DataType> *bt)
{
	if (bt == NULL)
		return; //�ݹ���õĽ�������
	else
	{
		InOrder(bt->lchild);	 //����ݹ����bt��������
		cout << bt->data << " "; //���ʸ����bt��������
		InOrder(bt->rchild);	 //����ݹ����bt��������
	}
}

template <class DataType>
void BiTree<DataType>::PostOrder(BiNode<DataType> *bt)
{
	if (bt == NULL)
		return; //�ݹ���õĽ�������
	else
	{
		PostOrder(bt->lchild);   //����ݹ����bt��������
		PostOrder(bt->rchild);   //����ݹ����bt��������
		cout << bt->data << " "; //���ʸ����bt��������
	}
}

template <class DataType>
void BiTree<DataType>::LeverOrder()
{
	int front = -1, rear = -1; //����˳����У����ٶ����ᷢ������
	BiNode<DataType> *Q[100];
	BiNode<DataType> *q;
	if (root == NULL)
		return;			  //������Ϊ�գ��㷨����
	Q[++rear] = root;	 //��ָ�����
	while (front != rear) //�����зǿ�ʱ
	{
		q = Q[++front]; //����
		cout << q->data << " ";
		if (q->lchild != NULL)
			Q[++rear] = q->lchild;
		if (q->rchild != NULL)
			Q[++rear] = q->rchild;
	}
}

int main()
{
	//�������Լ�д
	//Ҫ���ȹ��������,��ʵ�ֶ�������ǰ�����򡢺��򡢲������
	//...
	//������ʾ��
	//����ܻᷢ��,�������������ķ�ʽ����,������Ҫд�ܳ�
	//��Ϊ��Ҫ����������ʹ��ͷָ��root,�ͱ���Ҫ����˽�г�Աroot�ķ���Ȩ��,��Ҫ��public��getRoot����
	//...���и�����鷳�Ĵ���
	//...
	//...
	//������������һ��main������ʵ��˼·
	//...(��ʼ����üͷ��˼��...)
	//...(�����벻����..)
	//���ʵ���벻��������Ҳ���Է���
	//��Ϊ�˶δ�����Ҫ��Ϊ������Ƚ�tree.cpp��tree_1.cpp����ʵ�ַ�ʽ����࣬���������������ʵ����
	//...
	//...
	//�ٱ���һ���...
	//���ں����е�ͷ����...
	//...
	//XXXͬѧ����������" ��ʦ����֪��Ϊʲô�ˡ�"
	//��ʦ˵��"�ã��������������ʵ�ַ�ʽ�����,��������Ϊʲô��������, �һά������һ��QQ�ǵķ�����"
	//XXXͬѧ˵��"!@#$%^&*()"
	//...
	//"�ܺã�",��ʦ˵��
	//...
	//û���������λͬѧ���½ڿθ����Ұɣ�
	//...
	//...(δ�����)
}
