// Ԫ��֮ս.cpp : �������̨Ӧ�ó������ڵ㡣
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
#include <io.h>
#include <vector>
using namespace std;

const int X = 80, Y = 25, TEST = 0;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
int SUM = 0, station, MAX, Final;

enum Direction
{
	RIGHT,
	DOWN,
	LEFT,
	UP,
	ENTER,
	ESC,
	SPACE
};

void location(HANDLE hOut, int x, int y)        //��λ
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}

void prints(string s, int t)            //�������ӡ�ַ���
{
	int n = s.length();
	for (int i = 0; i < n; i++)
	{
		Sleep(t);
		cout << s[i];
	}
}

void printWINDOW()             //���ô��ڴ�С
{
	string temp = "mode con cols=" + to_string(X) + " lines=" + to_string(Y);
	char const *size = temp.c_str();
	system(size);
}

void Presskey(int m)
{
	char ch = _getch();
	if (ch == 27) exit(0);
	while (ch != m)
	{
		ch = _getch();
		if (ch == 27) exit(0);
	}
}
int GETMID(string s)              //�����ַ������Ȼ�ȡ����λ��
{
	int n = s.length() + 1;
	return (X - n) / 2;
}
void hideCursor(bool b)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;   //�����
	info.bVisible = b; //�Ƿ���ʾ

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
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

void sayhello()
{
	string hello1 = "��ӭ����BrainStorm-Bus��";
	location(hOut, GETMID(hello1), 3);
	prints(hello1, 25), Sleep(400);
	string hello2 = "����һ���һ�޶���ѵ��˼ά��������Ϸ";
	location(hOut, GETMID(hello2), 5);
	prints(hello2, 25), Sleep(1100);
	string hello3 = "�򵥽���һ����Ϸ����";
	location(hOut, GETMID(hello3), 7);
	prints(hello3, 25), Sleep(900);
	string hello4 = "һ���������ϸտ�ʼ���������˿�";
	location(hOut, GETMID(hello4), 9);
	prints(hello4, 25), Sleep(300);
	string hello5 = "ÿ����һվ�ͻ��г˿����³�";
	location(hOut, GETMID(hello5), 11);
	prints(hello5, 25), Sleep(1100);
	string hello6 = "�һ������ֵ���ʽ��������Щ��ֵ�Ƕ���";
	location(hOut, GETMID(hello6), 13);
	prints(hello6, 25), Sleep(600);
	string hello7 = "�ڹ����������յ�վ��ʱ���һ����㼸������";
	location(hOut, GETMID(hello7), 15);
	prints(hello7, 25), Sleep(600);
	string hello8 = "�����ش����ȫ���������㽫�õ����������ͳ������ؽ�����";
	location(hOut, GETMID(hello8), 17);
	prints(hello8, 25), Sleep(1100);
	string hello9 = "��׼�����˵Ļ� �����ǾͰ�1��ʼ��. . .";
	location(hOut, GETMID(hello9), 19);
	prints(hello9, 25), Sleep(600);
}
void loading()
{
	system("cls");
	string Loading0 = "��Ϸ�����У����Ժ�     ";
	string Loading1 = "��Ϸ�����У����Ժ�.    ";
	string Loading2 = "��Ϸ�����У����Ժ�. .  ";
	string Loading3 = "��Ϸ�����У����Ժ�. . .";
	location(hOut, GETMID(Loading1), Y / 2 - 1);
	cout << Loading0;
	Sleep(555);
	for (int i = 0; i < 6; i++)
	{
		location(hOut, GETMID(Loading1), Y / 2 - 1);
		if (i % 3 == 0)
			cout << Loading1;
		if (i % 3 == 1)
			cout << Loading2;
		if (i % 3 == 2)
			cout << Loading3;
		Sleep(555);
	}
}
void game()
{
	system("cls");
	station = rand() % 4 + 5;
	int Add[20] = { 0 }, Red[20] = { 0 };
	Add[0] = rand() % 7 + 17;
	while (Add[0] % 10 == 0)
	{
		Add[0] = rand() % 7 + 17;
	}
	SUM = Add[0];
	MAX = Add[1];
	Final = 0;
	string begin = to_string(SUM);
	string Begin = "�������ϸտ�ʼ�� " + begin + " �ˣ���1�ͷ�������������ȣ���";
	location(hOut, GETMID(Begin), Y / 2 - 3);
	prints(Begin, 30);
	Presskey(49);

	for (int i = 1; i <= station; i++)
	{
		Add[i] = rand() % 17 + rand() % 7 + 7;
		Red[i] = rand() % (SUM + Add[i] - 6);
		while (Red[i] % 10 == Add[i] % 10 || Red[i] / 10 == Add[i] / 10 || abs(Red[i] - Add[i]) <= 5 || Add[i] % 10 >= Red[i] || Red[i] % 10 == 0 || Add[i] % 10 == 0 || abs(Red[i] % 10 - Add[i] % 10) <= 2)
		{
			Add[i] = rand() % 17 + rand() % 7 + 7;
			Red[i] = rand() % (SUM + Add[i] - 6);
		}
		if (Add[i] > MAX) MAX = Add[i];
		SUM += Add[i];
		SUM -= Red[i];
		if (Add[i] > Red[i]) Final++;
	}

	system("cls");
	string bus = "�����������У���ע��˿����³�����Ϣ...";
	location(hOut, GETMID(bus), Y / 2 - 3);
	cout << bus;
	for (int i = 1; i <= station; i++)
	{
		Sleep(1234);
		string add = to_string(Add[i]), red = to_string(Red[i]);
		string Inf = "��վ��������վ�� " + add + " ���ϳ���" + red + " ���³���";
		location(hOut, GETMID(Inf), Y / 2);
		prints(Inf, 22);
		Sleep(3456);
		location(hOut, GETMID(Inf), Y / 2);
		cout << "                                                                                 ";
		Sleep(765);
	}
	system("cls");
	string end = "�յ�վ���ˣ���׼���ûش��������𣡣�׼�����˾Ͱ�1��������. . .";
	location(hOut, GETMID(end), Y / 2 - 1);
	prints(end, 22);
	Presskey(49);
}
void question4()
{
	system("cls");
	string num1 = "���һ�����⣬�����ܹ��ж���վ�ϳ����������³�������";
	location(hOut, GETMID(num1), Y / 2 - 3);
	prints(num1, 30);
	int ans1;
	cin >> ans1;
	if (ans1 == Final)
	{
		string yes = "��ϲ����ս�ɹ���ƾ�˽�ͼ����CST17017��ȡ��������һ�ݣ�";
		location(hOut, GETMID(yes), Y / 2 - 1);
		prints(yes, 30);
		location(hOut, GETMID("�밴���������. . ."), Y / 2 + 1);
		system("pause");
		exit(0);
	}
	else//19 25 5 24 2 16 8 17 8
	{
		string no3 = "�Բ�����սʧ�ܣ��������˳���Ϸ. . .3";
		string no2 = "�Բ�����սʧ�ܣ��������˳���Ϸ. . .2";
		string no1 = "�Բ�����սʧ�ܣ��������˳���Ϸ. . .1";
		location(hOut, GETMID(no3), Y / 2 - 1);
		prints(no3, 30);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 - 1);
		prints(no2, 0);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 - 1);
		prints(no1, 0);
		Sleep(1001);
		location(hOut, GETMID("�밴���������. . ."), Y / 2 + 1);
		exit(0);
	}
}
void question3()
{
	system("cls");
	string num1 = "�����������е��ѣ������ϳ���������ʱ���Ƕ����ˣ�";
	location(hOut, GETMID(num1), Y / 2 - 1);
	prints(num1, 30);
	int ans1;
	cin >> ans1;
	if (ans1 == MAX)
	{
		string yes = "��ϲ��ش���ȷ����1������һ������. . .";
		location(hOut, GETMID(yes), Y / 2 + 1);
		prints(yes, 30);
		Presskey(49);
		question4();
	}
	else//28 14 16 20 21 29 12 18 17 19 16 16 22 
	{
		string no3 = "�Բ�����սʧ�ܣ��������˳���Ϸ. . .3";
		string no2 = "�Բ�����սʧ�ܣ��������˳���Ϸ. . .2";
		string no1 = "�Բ�����սʧ�ܣ��������˳���Ϸ. . .1";
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no3, 30);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no2, 0);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no1, 0);
		Sleep(1001);
		location(hOut, GETMID("�밴���������. . ."), Y / 2 + 3);
		exit(0);
	}
}
void question2()
{
	system("cls");
	string num1 = "�����뿴�ڶ������⣬�������ܹ������˶���վ��";
	location(hOut, GETMID(num1), Y / 2 - 1);
	prints(num1, 30);
	int ans2;
	cin >> ans2;
	if (ans2 == station)
	{
		string yes = "��ϲ��ش���ȷ����1������һ������. . .";
		location(hOut, GETMID(yes), Y / 2 + 1);
		prints(yes, 30);
		Presskey(49);
		question3();
	}
	else//28 14 16 20 21 29 12 18 17 19 16 16 22 
	{
		string no3 = "�Բ�����սʧ�ܣ��������˳���Ϸ. . .3";
		string no2 = "�Բ�����սʧ�ܣ��������˳���Ϸ. . .2";
		string no1 = "�Բ�����սʧ�ܣ��������˳���Ϸ. . .1";
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no3, 30);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no2, 0);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no1, 0);
		Sleep(1001);
		location(hOut, GETMID("�밴���������. . ."), Y / 2 + 3);
		exit(0);
	}
}
void question1()
{
	system("cls");
	string num1 = "��һ��������Ӧ�òµ��˰ɣ��������ڳ��ϻ��ж����ˣ�";
	location(hOut, GETMID(num1), Y / 2 - 1);
	prints(num1, 30);
	int ans1;
	cin >> ans1;
	if (ans1 == SUM)
	{
		string yes = "��ϲ��ش���ȷ����1������һ������. . .";
		location(hOut, GETMID(yes), Y / 2 + 1);
		prints(yes, 30);
		Presskey(49);
		question2();
	}
	else//28 14 16 20 21 29 12 18 17 19 16 16 22 
	{
		string no3 = "�Բ�����սʧ�ܣ��������˳���Ϸ. . .3";
		string no2 = "�Բ�����սʧ�ܣ��������˳���Ϸ. . .2";
		string no1 = "�Բ�����սʧ�ܣ��������˳���Ϸ. . .1";
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no3, 30);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no2, 0);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no1, 0);
		Sleep(1001);
		location(hOut, GETMID("�밴���������. . ."), Y / 2 + 3);
		exit(0);
	}
}
void process()
{
	if (!TEST)
	sayhello();
	Presskey(49);
	loading();
	game();
	hideCursor(true);
	question1();
	double start, stop, durationTime;
	start = clock();

	stop = clock();
	durationTime = ((double)(stop - start)) / CLK_TCK;
	cout << "�ܺ�ʱ��" << durationTime << endl << endl;
}
int main()
{
	srand((int)time(0));
	printWINDOW();            

	hideCursor(false);
	process();
	return 0;
}

