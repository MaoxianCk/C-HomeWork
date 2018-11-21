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
class InitList
{
protected:
	unsigned int MAX_LENGTH;
	unsigned int length;
	T *date;
public:
	InitList();
	InitList(unsigned int maxLength);
	InitList(InitList &list);
	~InitList();
	void printList();
	void setEmpty();
	bool modifyNodeByNum(unsigned int num, T d);
	void invert();
	bool insertByNum(unsigned int num, T d);
	unsigned int findListByDateNum(Date d);
	bool delNode(unsigned int num);

	unsigned int getLength();
	unsigned int getMaxLength();
};
template <class T> InitList<T>::InitList()
{
	//cout << "建立学生线性表" << endl;

	length = 0;
	MAX_LENGTH = 100;
	T *temp = new T[MAX_LENGTH];
	date = temp;
}
template <class T> InitList<T>::InitList(unsigned int maxLength)
{
	//cout << "建立学生线性表" << endl;

	length = 0;
	MAX_LENGTH = maxLength;
	T *temp = new T[MAX_LENGTH];
	date = temp;
}
template <class T> InitList<T>::InitList(InitList &list)
{
	//cout << "建立学生线性表" << endl;

	length = list.getLength();
	MAX_LENGTH = list.getMaxLength();
	T *temp = new T[MAX_LENGTH];
	date = temp;
}
template <class T> InitList<T>::~InitList()
{
	delete[]date;
	date = nullptr;
}
template <class T>
void InitList<T>::printList()
{
	//cout << "显示学生线性表信息" << endl;

	for (unsigned int i = 0; i < length; i++)
	{
		cout << i + 1 << (i + 1 < 10 ? ". " : ".");
		date[i].printDate();
	}
	cout << endl;
}
template <class T>
void InitList<T>::setEmpty()
{
	length = 0;
}
template <class T>
bool InitList<T>::modifyNodeByNum(unsigned int num, T d)
{
	//cout << "修改学生线性表信息" << endl;
	if (num >= MAX_LENGTH)
	{
		//cout << "修改位置超出范围" << endl;
		return false;
	}

	date[num - 1] = d;
	return true;
}
template <class T>
void InitList<T>::invert()
{
	//cout << "逆置线性表" << endl;
	for (unsigned int i = 0; i <= length / 2; i++)
	{
		swap(date[i], date[length - i - 1]);
	}
}
template <class T>
bool InitList<T>::insertByNum(unsigned int num, T d)
{
	if (num >= MAX_LENGTH || num <= 0)
	{
		//cout << "插入位置超出范围" << endl;
		return false;
	}
	if (length + 1 > MAX_LENGTH)
	{
		//cout << "元素太多" << endl;
		return false;
	}
	//cout << "插入数据" << endl;
	for (unsigned int i = length; length > 0 && i > num - 1; i--)
	{
		date[i] = date[i - 1];
	}
	date[num - 1] = d;
	length++;
	return true;
}
template <class T>
unsigned int InitList<T>::findListByDateNum(Date d)
{
	for (unsigned int i = 0; i < length; i++)
	{
		if (date[i].num == d.num)
		{
			date[i].printDate();
			return i + 1;
		}
	}
	return -1;
}
template <class T>
bool InitList<T>::delNode(unsigned int num)
{
	if (num<1 || num > length)
	{
		//cout << "删除位置超出范围" << endl;
		return false;
	}
	//cout << "删除节点" << endl;
	for (unsigned int i = num - 1; i < length - 1; i++)
	{
		swap(date[i], date[i + 1]);
	}
	length--;
	return true;
}
template <class T>
unsigned int InitList<T>::getLength()
{
	return length;
}
template <class T>
unsigned int InitList<T>::getMaxLength()
{
	return MAX_LENGTH;
}

class StudentList : public InitList<Date>
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
StudentList::StudentList() :InitList(100) {}

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