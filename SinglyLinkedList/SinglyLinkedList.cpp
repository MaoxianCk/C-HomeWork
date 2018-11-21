#include<iostream>
#include<windows.h>
#include<string>
using namespace std;

int inputNumber(string info);
enum Gender { male, female };
struct Date
{
	string num, name;
	Gender gender;
	int score;
	void printDate()
	{
		cout << "ѧ��:" << num << "\t����:" << name << "\t�Ա�:" << (gender == male ? "��" : "Ů") << "\t�ɼ�:" << score << endl;
	}
};

template <class T>
struct Node
{
	T date;
	Node *next;
};

template <class T>
class SinglyLinkedList
{
protected:
	unsigned int length;
	Node<T> *head=new Node<T>;

  public:
	SinglyLinkedList();
	~SinglyLinkedList();
	void printList();
	void printNodeInfo(unsigned int num);
	void setEmpty();
	bool modifyNodeByNum(unsigned int num, T d);
	void invert();
	bool insertByNum(unsigned int num, T d);
	unsigned int findListByDateNum(Date d);
	bool delNode(unsigned int num);

	unsigned int getLength();
};
template <class T> SinglyLinkedList<T>::SinglyLinkedList()
{
	length = 0;
	head->next = nullptr;
}

template <class T> SinglyLinkedList<T>::~SinglyLinkedList()
{
	setEmpty();
}
template <class T>
void SinglyLinkedList<T>::printList()
{
	//cout <<"��ʾѧ�����Ա���Ϣ" << endl;
	Node<T> *temp = head->next;
	while(temp!=nullptr)
	{
		temp->date.printDate();
		temp = temp->next;
	}
	cout << endl;
}
template <class T>
void SinglyLinkedList<T>::printNodeInfo(unsigned int num)
{
	//num--;
	Node<T> *temp = head;
	while(num--)
	{
		temp = temp->next;
	}
	temp->date.printDate();
}
template <class T>
void SinglyLinkedList<T>::setEmpty()
{
	while (head->next != nullptr)
	{
		delNode(1);
	}
}
template <class T>
bool SinglyLinkedList<T>::modifyNodeByNum(unsigned int num, T d)
{
	//cout <<"�޸�ѧ�����Ա���Ϣ" << endl;
	if (num > length)
	{
		//cout <<"�޸�λ�ó�����Χ" << endl;
		return false;
	}
	Node<T> *temp = head;
	while(num--)
	{
		temp = temp->next;
	}
	temp->date = d;
	return true;
}
template <class T>
void SinglyLinkedList<T>::invert()
{
	//cout <<"�������Ա�" << endl;
	//�͵����÷�

	Node<T> *temp, *tempNext;
	temp = head->next;
	head->next=nullptr;
	while (temp != nullptr)
	{
			tempNext = temp->next;
			temp->next = head->next;
			head->next = temp;
			temp = tempNext;
	}
}
template <class T>
bool SinglyLinkedList<T>::insertByNum(unsigned int num, T d)
{
	num--;
	if (num >length || num < 0)
	{
		//cout <<"����λ�ó�����Χ" << endl;
		return false;
	}
	//cout <<"��������" << endl;
	Node<T> *insertedNode=new Node<T>;

	insertedNode->date = d;
	Node<T> *temp = head;
	while (num--)
	{
		temp = temp->next;
	}
	insertedNode->next = temp->next;
	temp->next = insertedNode;
	length++;
	return true;
}
template <class T>
unsigned int SinglyLinkedList<T>::findListByDateNum(Date d)
{
	int cnt = 1;
	Node<Date> *temp = head->next;
	while(temp!=nullptr)
	{
		if(temp->date.num==d.num)
		{
			return cnt;
		}
		temp = temp->next;
		cnt++;
	}
	return -1;
}
template <class T>
bool SinglyLinkedList<T>::delNode(unsigned int num)
{
	num--;
	if (num<0 || num >= length)
	{
		//cout <<"ɾ��λ�ó�����Χ" << endl;
		return false;
	}
	//cout <<"ɾ���ڵ�" << endl;
	Node<T> *temp = head;
	Node<T> *deletedNode;
	while (num--&&temp!=nullptr)
	{
		temp = temp->next;
	}
	deletedNode = temp->next;

	temp->next = temp->next->next;
	delete deletedNode;
	length--;
	return true;
}
template <class T>
unsigned int SinglyLinkedList<T>::getLength()
{
	return length;
}




class StudentList : public SinglyLinkedList<Date>
{
private:

	Date inputStudentInfo();
public:
	StudentList();
	void creatStudentList();
	void printStudentList();
	void prinStudentListTitle();
	void modifyStudnetNode();
	void invertStudentList();
	void insertStudentList();
	unsigned int findStudentList();
	void delStudentList();
};
StudentList::StudentList() :SinglyLinkedList() {}

Date StudentList::inputStudentInfo()
{
	Date d;
	string str;
	int score;
	cout << "ѧ��: ";
	cin >> d.num;
	cout << "����: ";
	cin >> d.name;
	while (true)
	{
		cout << "�Ա�(��,Ů): ";
		cin >> str;
		if (str == "��")
		{
			d.gender = male;
			break;
		}
		else if (str == "Ů")
		{
			d.gender = female;
			break;
		}
		else
		{
			cout << "�����Ա����,������\"��\"��\"Ů\"" << endl;
			continue;
		}
	}

	while (true)
	{
		score = inputNumber("�ɼ�: ");

		if (score < 0 || score>100)
		{
			cout << "�ɼ�������Χ [ 0 , 100 ],����������" << endl;
			continue;
		}
		else
		{
			d.score = score;
			break;
		}
	}
	return d;
}
void StudentList::creatStudentList()
{
	int sum;
	int cnt = 1;
	string str;
	Date d;
	cout << "����ѧ����Ϣ��" << endl;

	sum = inputNumber("������ѧ������: ");
	while (sum--)
	{
		cout << "������� " << cnt << " ��ѧ����Ϣ" << endl;
		d = inputStudentInfo();
		insertByNum(cnt++, d);
	}
}
void StudentList::printStudentList()
{
	cout << "*****ѧ����Ϣ��*****" << endl;
	printList();
}
void StudentList::prinStudentListTitle()
{
	cout << "-*-*-*-*-*-*-**-*-*-*-*-*-*-" << endl;
	cout << "   ****ѧ����Ϣ����****" << endl;
	cout << "-*-*-*-*-*-*-**-*-*-*-*-*-*-" << endl;
}
void StudentList::modifyStudnetNode()
{
	unsigned int num;
	Date d;
	printStudentList();
	while (true)
	{
		num = inputNumber("��������Ҫ�޸ĵı��:");
		if (num<1 || num>length)
		{
			cout << "��ų�����Χ!" << endl;
		}
		else
		{
			break;
		}
	}
	cout << "�������µ�ѧ����Ϣ" << endl;
	d = inputStudentInfo();
	modifyNodeByNum(num, d);
}
void StudentList::invertStudentList()
{
	cout << "����˳���" << endl;
	invert();
}
void StudentList::insertStudentList()
{
	unsigned int num;
	Date d;
	printStudentList();
	while (true)
	{
		num = inputNumber("��������Ҫ����ı��:");
		if (num<1 || num>length + 1)
		{
			cout << "��ų�����Χ!" << endl;
		}
		else
		{
			break;
		}
	}
	cout << "�������µ�ѧ����Ϣ" << endl;
	d = inputStudentInfo();
	insertByNum(num, d);
}
unsigned int StudentList::findStudentList()
{
	Date d;
	unsigned int num;
	cout << "������Ҫ���ҵ�ѧ��:";
	cin >> d.num;
	num = findListByDateNum(d);
	if (num == -1)
	{
		cout << "û���ҵ���Ӧѧ��!" << endl;
	}
	else
	{
		printNodeInfo(num);
	}
	return num;
}
void StudentList::delStudentList()
{
	unsigned int num;

	printStudentList();

	num = inputNumber("������Ҫɾ���ı��:");
	if (delNode(num))
	{
		cout << "ɾ���ɹ�!" << endl;
	}
	else
	{
		cout << "ɾ��ʧ��!" << endl;
	}
}


int inputNumber(string info)
{
	string str;
	while (true)
	{
		if (info != "")
		{
			cout << info;
		}
		bool flag = true;//����Ƿ�����
		cin >> str;
		for (unsigned int i = 0; i < str.length(); i++)
		{
			if (str[i]<'0' || str[i]>'9')
			{
				flag = false;
				break;
			}
		}
		if (flag == true)
		{
			return (atoi(str.c_str()));
		}
		else
		{
			cout << "����������!" << endl;
			continue;
		}
	}
}
int main()
{
	//system("color 03");
	//������ɫ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	StudentList list;
	int select;
	bool exit = false;

	list.prinStudentListTitle();
	list.creatStudentList();
	while (true)
	{
		system("cls");

		list.prinStudentListTitle();
		cout << "   1.����һ��ѧ����Ϣ" << endl;
		cout << "   2.��ѯһ��ѧ����Ϣ" << endl;
		cout << "   3.ɾ��һ��ѧ����Ϣ" << endl;
		cout << "   4.����һ��ѧ����Ϣ" << endl;
		cout << "   5.��������ѧ����Ϣ" << endl;
		cout << "   6.ɾ������ѧ����Ϣ" << endl;
		cout << "   7.��ʾ����ѧ����Ϣ" << endl;
		cout << "   0.�˳�ѧ����Ϣ����" << endl;
		cout << endl;

		select = inputNumber("��������:");
		switch (select)
		{
		case 1:
			list.insertStudentList();
			break;
		case 2:
			list.findStudentList();
			break;
		case 3:
			list.delStudentList();
			break;
		case 4:
			list.modifyStudnetNode();
			break;
		case 5:
			list.invert();
			break;
		case 6:
			list.setEmpty();
			break;
		case 7:
			list.printStudentList();
			break;
		case 0:
			exit = true;
			break;
		default:
			cout << "�������!" << endl;
			break;
		}
		if (exit == true)
		{
			break;
		}
		system("pause");
	}
	return 0;
}