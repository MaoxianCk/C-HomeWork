// 抽.cpp : 定义控制台应用程序的入口点。
//

#include <algorithm>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <random>
#include <string>
#include <windows.h>
using namespace std;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
random_device rd;

int selectRandNumber = 5; /*！！！！！   a,b为范围，最大值建议不要超过99否则会影响效果。c为抽取学生数量，建议为3-5人    ！！！！！*/
const int classesNumber = 6;
int classNum = 1; //当前的班级编号
int classesStudentsNumber = 55;
bool TEST = true;
string classesName[classesNumber] = {"1班理论", "1班实验", "2班理论", "2班实验", "15软工1班", "15软工2班"};
int classesStudentsNumberArrary[classesNumber] = {61, 58, 64, 59, 60, 54};

enum Direction
{
	RIGHT,
	DOWN,
	LEFT,
	UP,
	ENTER,
	ESC,
	SPACE
}; //方向 0 1 2 3 4 5对应右下左上回车ESC 顺时针

void hideCursor(bool b)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;   //光标厚度
	info.bVisible = b; //是否显示

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void location(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}
int getKeyboard()
{
	unsigned char ch;
	ch = _getch();

	switch (ch)
	{
		//→
	case 'D':
	case 'd':
	case 77:
		return RIGHT;
		//↓
	case 'S':
	case 's':
	case 80:
		return DOWN;
		//←
	case 'A':
	case 'a':
	case 75:
		return LEFT;
		//↑
	case 'W':
	case 'w':
	case 72:
		return UP;

	case 13:
		return ENTER;

	case 27:
		return ESC;
	case 32:
		return SPACE;
	default:
		return -1;
	}
}
void prints(string s, int t)
{
	int n = s.length();
	for (int i = 0; i < n; i++)
	{
		Sleep(t);
		cout << s[i];
	}
}

//从文件读取名单
void GetList(int cla_number, int stu_number, string &id, string &name)
{
	int number;
	string Sid, Sname;
	string str;
	switch (cla_number)
	{
	case 1:
		str = "1班理论.txt";
		break;
	case 2:
		str = "1班实验.txt";
		break;
	case 3:
		str = "2班理论.txt";
		break;
	case 4:
		str = "2班实验.txt";
		break;
	case 5:
		str = "15软工1班.txt";
		break;
	case 6:
		str = "15软工2班.txt";
		break;
	default:
		break;
	}
	ifstream fin(str);
	while (fin >> number >> Sid >> Sname)
	{
		if (number == stu_number)
		{
			id = Sid;
			name = Sname;
			break;
		}
	}
}

void LuckyDraw(int i)
{
	string temp = "mode con cols=" + to_string(80) + " lines=" + to_string(selectRandNumber*2+15);
	char const *size = temp.c_str();
	system(size);

	system("cls");
	int *R = new int[i];
	location(hOut, 25, 3);

	string Rule = "数字滚动中，请按任意键选取";
	prints(Rule, 0);

	for (int k = 0; k < i; k++)
	{
		location(hOut, 17, 6 + k * 2);
		cout << "第" << k + 1 << "位幸运儿是    号！";
	}

	while (1)
	{
		for (int k = 0; k < i; k++)
		{
			Sleep(3); //随机间隔，减少短时间内随机相似性
			//R[k] = rand() % classesStudentsNumber+ 1;
			R[k] = rd() % classesStudentsNumber + 1;

			for (int p = 0; p < k; p++)
			{
				while (R[k] == R[p])
				{
					Sleep(3);
					R[k] = rd() % classesStudentsNumber + 1;
				}
			}
		}

		if (!_kbhit())
		{
			for (int k = 0; k < i; k++)
			{
				location(hOut, 31, 6 + k * 2);
				if (R[k] < 10)
				{
					cout << "0";
				}
				cout << R[k];
			}
		}
		else
		{
			for (int k = 0; k < i; k++)
			{
				location(hOut, 31, 6 + k * 2);
				if (R[k] < 10)
				{
					cout << "0";
				}
				cout << R[k];
			}
			break;
		}
	}

	for (int k = 0; k < i; k++)
	{
		string id, name;
		GetList(classNum, R[k], id, name);
		location(hOut, 41, 6 + k * 2);
		cout << "  " << id << "  " << name;
	}
}

//选择班级 根据班级数量选择班级，6个班级编号1-6,全局变量classNum为当前选择班级
void selectClass()
{
	const int posX = 35, posY = 5;
	int sel = 1;

	system("cls");
	location(hOut, posX - 3, 3);
	//cout << "请选择班级";

	for (int i = 0; i < classesNumber; i++)
	{
		location(hOut, posX, posY + (i + 1) * 2 - 1);
		cout << classesName[i];
	}

	location(hOut, posX - 3, posY + (sel + 1) * 2 - 1);
	cout << "  ";
	location(hOut, posX - 3, posY + sel * 2 - 1);
	cout << ">>";

	while (true)
	{
		int dir = getKeyboard();
		if (dir == UP)
		{
			sel = (sel <= 1 ? 1 : sel - 1);
			location(hOut, posX - 3, posY + (sel + 1) * 2 - 1);
			cout << "  ";
			location(hOut, posX - 3, posY + sel * 2 - 1);
			cout << ">>";
		}
		else if (dir == DOWN)
		{
			sel = (sel >= classesNumber ? classesNumber : sel + 1);
			location(hOut, posX - 3, posY + (sel - 1) * 2 - 1);
			cout << "  ";
			location(hOut, posX - 3, posY + sel * 2 - 1);
			cout << ">>";
		}
		else if (dir == ENTER)
		{
			break;
		}
		else if (dir == ESC)
		{
			exit(0);
		}
	}
	classNum = sel;
	classesStudentsNumber = classesStudentsNumberArrary[classNum - 1];
}
void selectRandNum()
{
	system("cls");

	location(hOut, 27, 4);
	cout << "您选择的班级是" << classesName[classNum - 1];

	location(hOut, 27, 6);
	hideCursor(true);
	cout << "请输入要抽取的人数: ";
	cin >> selectRandNumber;
	hideCursor(false);
}

void START()
{
	for (int i = 3; i >= 1; i--)
	{
		location(hOut, 27, 10);
		cout << "程序启动中，请稍候..." << i;
		Sleep(1001);
		system("cls");
	}
}
void Begin()
{
	if (!TEST)
	{
		START();
		location(hOut, 19, 8);
		string hello1 = "又到了一节课紧张而又刺激的“抽奖”环节！！";
		prints(hello1, 25);

		string hello2 = "今天会抽中哪几位幸运儿呢？？";
		location(hOut, 25, 10);
		prints(hello2, 25);
		Sleep(500);

		string hello3 = "按任意键进入“抽奖”界面....";
		location(hOut, 25, 12);
		prints(hello3, 27);

		int flag = _getch();
		if (flag >= 0 && flag <= 127)
			system("cls");
	}

	selectClass();

	selectRandNum();

	LuckyDraw(selectRandNumber);

	location(hOut, 11, 7 + selectRandNumber * 2);
	string end = "恭喜以上中奖同学，如有疑问欢迎发送邮件到664224027@qq.com！";
	prints(end, 27);
	location(hOut, 22, 9 + selectRandNumber * 2);
	string brand = "Power By CST17017 涂学彬, Maoxian";
	prints(brand, 27);
	location(hOut, 30, 11 + selectRandNumber * 2);
}

int main()
{
	system("mode con cols=80 lines=25");
	srand((int)time(0));
	hideCursor(false);
	Begin();
	
	return 0;
}