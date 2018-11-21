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
		cout << "学号:" << num << "\t姓名:" << name << "\t性别:" << (gender == male ? "男" : "女") << "\t成绩:" << score << endl;
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
	//cout <<"显示学生线性表信息" << endl;
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
	//cout <<"修改学生线性表信息" << endl;
	if (num > length)
	{
		//cout <<"修改位置超出范围" << endl;
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
	//cout <<"逆置线性表" << endl;
	//就地逆置法

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
		//cout <<"插入位置超出范围" << endl;
		return false;
	}
	//cout <<"插入数据" << endl;
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
		//cout <<"删除位置超出范围" << endl;
		return false;
	}
	//cout <<"删除节点" << endl;
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
	cout << "学号: ";
	cin >> d.num;
	cout << "姓名: ";
	cin >> d.name;
	while (true)
	{
		cout << "性别(男,女): ";
		cin >> str;
		if (str == "男")
		{
			d.gender = male;
			break;
		}
		else if (str == "女")
		{
			d.gender = female;
			break;
		}
		else
		{
			cout << "输入性别错误,请输入\"男\"或\"女\"" << endl;
			continue;
		}
	}

	while (true)
	{
		score = inputNumber("成绩: ");

		if (score < 0 || score>100)
		{
			cout << "成绩超出范围 [ 0 , 100 ],请重新输入" << endl;
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
	cout << "创建学生信息表" << endl;

	sum = inputNumber("请输入学生数量: ");
	while (sum--)
	{
		cout << "请输入第 " << cnt << " 名学生信息" << endl;
		d = inputStudentInfo();
		insertByNum(cnt++, d);
	}
}
void StudentList::printStudentList()
{
	cout << "*****学生信息表*****" << endl;
	printList();
}
void StudentList::prinStudentListTitle()
{
	cout << "-*-*-*-*-*-*-**-*-*-*-*-*-*-" << endl;
	cout << "   ****学生信息管理****" << endl;
	cout << "-*-*-*-*-*-*-**-*-*-*-*-*-*-" << endl;
}
void StudentList::modifyStudnetNode()
{
	unsigned int num;
	Date d;
	printStudentList();
	while (true)
	{
		num = inputNumber("请输入你要修改的编号:");
		if (num<1 || num>length)
		{
			cout << "编号超出范围!" << endl;
		}
		else
		{
			break;
		}
	}
	cout << "请输入新的学生信息" << endl;
	d = inputStudentInfo();
	modifyNodeByNum(num, d);
}
void StudentList::invertStudentList()
{
	cout << "逆置顺序表" << endl;
	invert();
}
void StudentList::insertStudentList()
{
	unsigned int num;
	Date d;
	printStudentList();
	while (true)
	{
		num = inputNumber("请输入你要插入的编号:");
		if (num<1 || num>length + 1)
		{
			cout << "编号超出范围!" << endl;
		}
		else
		{
			break;
		}
	}
	cout << "请输入新的学生信息" << endl;
	d = inputStudentInfo();
	insertByNum(num, d);
}
unsigned int StudentList::findStudentList()
{
	Date d;
	unsigned int num;
	cout << "请输入要查找的学号:";
	cin >> d.num;
	num = findListByDateNum(d);
	if (num == -1)
	{
		cout << "没有找到对应学生!" << endl;
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

	num = inputNumber("请输入要删除的编号:");
	if (delNode(num))
	{
		cout << "删除成功!" << endl;
	}
	else
	{
		cout << "删除失败!" << endl;
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
		bool flag = true;//标记是否纯数字
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
			cout << "请输入数字!" << endl;
			continue;
		}
	}
}
int main()
{
	//system("color 03");
	//设置颜色
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
		cout << "   1.插入一个学生信息" << endl;
		cout << "   2.查询一个学生信息" << endl;
		cout << "   3.删除一个学生信息" << endl;
		cout << "   4.更改一个学生信息" << endl;
		cout << "   5.逆置所有学生信息" << endl;
		cout << "   6.删除所有学生信息" << endl;
		cout << "   7.显示所有学生信息" << endl;
		cout << "   0.退出学生信息管理" << endl;
		cout << endl;

		select = inputNumber("请输入编号:");
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
			cout << "输入错误!" << endl;
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