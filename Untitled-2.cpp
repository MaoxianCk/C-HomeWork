// ��.cpp : �������̨Ӧ�ó������ڵ㡣
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

int selectRandNumber = 5; /*����������   a,bΪ��Χ�����ֵ���鲻Ҫ����99�����Ӱ��Ч����cΪ��ȡѧ������������Ϊ3-5��    ����������*/
const int classesNumber = 6;
int classNum = 1; //��ǰ�İ༶���
int classesStudentsNumber = 55;
bool TEST = true;
string classesName[classesNumber] = {"1������", "1��ʵ��", "2������", "2��ʵ��", "15��1��", "15��2��"};
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
}; //���� 0 1 2 3 4 5��Ӧ�������ϻس�ESC ˳ʱ��

void hideCursor(bool b)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;   //�����
	info.bVisible = b; //�Ƿ���ʾ

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
		//��
	case 'D':
	case 'd':
	case 77:
		return RIGHT;
		//��
	case 'S':
	case 's':
	case 80:
		return DOWN;
		//��
	case 'A':
	case 'a':
	case 75:
		return LEFT;
		//��
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

//���ļ���ȡ����
void GetList(int cla_number, int stu_number, string &id, string &name)
{
	int number;
	string Sid, Sname;
	string str;
	switch (cla_number)
	{
	case 1:
		str = "1������.txt";
		break;
	case 2:
		str = "1��ʵ��.txt";
		break;
	case 3:
		str = "2������.txt";
		break;
	case 4:
		str = "2��ʵ��.txt";
		break;
	case 5:
		str = "15��1��.txt";
		break;
	case 6:
		str = "15��2��.txt";
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

	string Rule = "���ֹ����У��밴�����ѡȡ";
	prints(Rule, 0);

	for (int k = 0; k < i; k++)
	{
		location(hOut, 17, 6 + k * 2);
		cout << "��" << k + 1 << "λ���˶���    �ţ�";
	}

	while (1)
	{
		for (int k = 0; k < i; k++)
		{
			Sleep(3); //�����������ٶ�ʱ�������������
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

//ѡ��༶ ���ݰ༶����ѡ��༶��6���༶���1-6,ȫ�ֱ���classNumΪ��ǰѡ��༶
void selectClass()
{
	const int posX = 35, posY = 5;
	int sel = 1;

	system("cls");
	location(hOut, posX - 3, 3);
	//cout << "��ѡ��༶";

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
	cout << "��ѡ��İ༶��" << classesName[classNum - 1];

	location(hOut, 27, 6);
	hideCursor(true);
	cout << "������Ҫ��ȡ������: ";
	cin >> selectRandNumber;
	hideCursor(false);
}

void START()
{
	for (int i = 3; i >= 1; i--)
	{
		location(hOut, 27, 10);
		cout << "���������У����Ժ�..." << i;
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
		string hello1 = "�ֵ���һ�ڿν��Ŷ��ִ̼��ġ��齱�����ڣ���";
		prints(hello1, 25);

		string hello2 = "���������ļ�λ���˶��أ���";
		location(hOut, 25, 10);
		prints(hello2, 25);
		Sleep(500);

		string hello3 = "����������롰�齱������....";
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
	string end = "��ϲ�����н�ͬѧ���������ʻ�ӭ�����ʼ���664224027@qq.com��";
	prints(end, 27);
	location(hOut, 22, 9 + selectRandNumber * 2);
	string brand = "Power By CST17017 Ϳѧ��, Maoxian";
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