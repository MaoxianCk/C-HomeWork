// 元素之战.cpp : 定义控制台应用程序的入口点。
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

void location(HANDLE hOut, int x, int y)        //定位
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}

void prints(string s, int t)            //按毫秒打印字符串
{
	int n = s.length();
	for (int i = 0; i < n; i++)
	{
		Sleep(t);
		cout << s[i];
	}
}

void printWINDOW()             //设置窗口大小
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
int GETMID(string s)              //根据字符串长度获取居中位置
{
	int n = s.length() + 1;
	return (X - n) / 2;
}
void hideCursor(bool b)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;   //光标厚度
	info.bVisible = b; //是否显示

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
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

void sayhello()
{
	string hello1 = "欢迎来到BrainStorm-Bus！";
	location(hOut, GETMID(hello1), 3);
	prints(hello1, 25), Sleep(400);
	string hello2 = "这是一款独一无二的训练思维的文字游戏";
	location(hOut, GETMID(hello2), 5);
	prints(hello2, 25), Sleep(1100);
	string hello3 = "简单介绍一下游戏规则：";
	location(hOut, GETMID(hello3), 7);
	prints(hello3, 25), Sleep(900);
	string hello4 = "一辆公交车上刚开始有若干名乘客";
	location(hOut, GETMID(hello4), 9);
	prints(hello4, 25), Sleep(300);
	string hello5 = "每经过一站就会有乘客上下车";
	location(hOut, GETMID(hello5), 11);
	prints(hello5, 25), Sleep(1100);
	string hello6 = "我会以文字的形式告诉你这些数值是多少";
	location(hOut, GETMID(hello6), 13);
	prints(hello6, 25), Sleep(600);
	string hello7 = "在公交车到达终点站的时候我会问你几个问题";
	location(hOut, GETMID(hello7), 15);
	prints(hello7, 25), Sleep(600);
	string hello8 = "如果你回答对了全部的问题你将得到由我亲自送出的神秘奖励！";
	location(hOut, GETMID(hello8), 17);
	prints(hello8, 25), Sleep(1100);
	string hello9 = "你准备好了的话 那我们就按1开始吧. . .";
	location(hOut, GETMID(hello9), 19);
	prints(hello9, 25), Sleep(600);
}
void loading()
{
	system("cls");
	string Loading0 = "游戏加载中，请稍候     ";
	string Loading1 = "游戏加载中，请稍候.    ";
	string Loading2 = "游戏加载中，请稍候. .  ";
	string Loading3 = "游戏加载中，请稍候. . .";
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
	string Begin = "公交车上刚开始有 " + begin + " 人，按1就发车啦，大家坐稳！！";
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
	string bus = "公交车运行中，请注意乘客上下车的信息...";
	location(hOut, GETMID(bus), Y / 2 - 3);
	cout << bus;
	for (int i = 1; i <= station; i++)
	{
		Sleep(1234);
		string add = to_string(Add[i]), red = to_string(Red[i]);
		string Inf = "到站啦！！本站有 " + add + " 人上车，" + red + " 人下车。";
		location(hOut, GETMID(Inf), Y / 2);
		prints(Inf, 22);
		Sleep(3456);
		location(hOut, GETMID(Inf), Y / 2);
		cout << "                                                                                 ";
		Sleep(765);
	}
	system("cls");
	string end = "终点站到了！！准备好回答问题了吗！！准备好了就按1哈哈哈哈. . .";
	location(hOut, GETMID(end), Y / 2 - 1);
	prints(end, 22);
	Presskey(49);
}
void question4()
{
	system("cls");
	string num1 = "最后一个问题，请问总共有多少站上车人数大于下车人数：";
	location(hOut, GETMID(num1), Y / 2 - 3);
	prints(num1, 30);
	int ans1;
	cin >> ans1;
	if (ans1 == Final)
	{
		string yes = "恭喜你挑战成功，凭此截图可向CST17017索取神秘礼物一份！";
		location(hOut, GETMID(yes), Y / 2 - 1);
		prints(yes, 30);
		location(hOut, GETMID("请按任意键继续. . ."), Y / 2 + 1);
		system("pause");
		exit(0);
	}
	else//19 25 5 24 2 16 8 17 8
	{
		string no3 = "对不起，挑战失败！您即将退出游戏. . .3";
		string no2 = "对不起，挑战失败！您即将退出游戏. . .2";
		string no1 = "对不起，挑战失败！您即将退出游戏. . .1";
		location(hOut, GETMID(no3), Y / 2 - 1);
		prints(no3, 30);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 - 1);
		prints(no2, 0);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 - 1);
		prints(no1, 0);
		Sleep(1001);
		location(hOut, GETMID("请按任意键继续. . ."), Y / 2 + 1);
		exit(0);
	}
}
void question3()
{
	system("cls");
	string num1 = "这个问题可能有点难，请问上车人数最多的时候是多少人：";
	location(hOut, GETMID(num1), Y / 2 - 1);
	prints(num1, 30);
	int ans1;
	cin >> ans1;
	if (ans1 == MAX)
	{
		string yes = "恭喜你回答正确！按1进入下一个问题. . .";
		location(hOut, GETMID(yes), Y / 2 + 1);
		prints(yes, 30);
		Presskey(49);
		question4();
	}
	else//28 14 16 20 21 29 12 18 17 19 16 16 22 
	{
		string no3 = "对不起，挑战失败！您即将退出游戏. . .3";
		string no2 = "对不起，挑战失败！您即将退出游戏. . .2";
		string no1 = "对不起，挑战失败！您即将退出游戏. . .1";
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no3, 30);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no2, 0);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no1, 0);
		Sleep(1001);
		location(hOut, GETMID("请按任意键继续. . ."), Y / 2 + 3);
		exit(0);
	}
}
void question2()
{
	system("cls");
	string num1 = "下面请看第二个问题，公交车总共经过了多少站：";
	location(hOut, GETMID(num1), Y / 2 - 1);
	prints(num1, 30);
	int ans2;
	cin >> ans2;
	if (ans2 == station)
	{
		string yes = "恭喜你回答正确！按1进入下一个问题. . .";
		location(hOut, GETMID(yes), Y / 2 + 1);
		prints(yes, 30);
		Presskey(49);
		question3();
	}
	else//28 14 16 20 21 29 12 18 17 19 16 16 22 
	{
		string no3 = "对不起，挑战失败！您即将退出游戏. . .3";
		string no2 = "对不起，挑战失败！您即将退出游戏. . .2";
		string no1 = "对不起，挑战失败！您即将退出游戏. . .1";
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no3, 30);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no2, 0);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no1, 0);
		Sleep(1001);
		location(hOut, GETMID("请按任意键继续. . ."), Y / 2 + 3);
		exit(0);
	}
}
void question1()
{
	system("cls");
	string num1 = "第一个问题你应该猜到了吧，请问现在车上还有多少人：";
	location(hOut, GETMID(num1), Y / 2 - 1);
	prints(num1, 30);
	int ans1;
	cin >> ans1;
	if (ans1 == SUM)
	{
		string yes = "恭喜你回答正确！按1进入下一个问题. . .";
		location(hOut, GETMID(yes), Y / 2 + 1);
		prints(yes, 30);
		Presskey(49);
		question2();
	}
	else//28 14 16 20 21 29 12 18 17 19 16 16 22 
	{
		string no3 = "对不起，挑战失败！您即将退出游戏. . .3";
		string no2 = "对不起，挑战失败！您即将退出游戏. . .2";
		string no1 = "对不起，挑战失败！您即将退出游戏. . .1";
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no3, 30);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no2, 0);
		Sleep(1001);
		location(hOut, GETMID(no3), Y / 2 + 1);
		prints(no1, 0);
		Sleep(1001);
		location(hOut, GETMID("请按任意键继续. . ."), Y / 2 + 3);
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
	cout << "总耗时：" << durationTime << endl << endl;
}
int main()
{
	srand((int)time(0));
	printWINDOW();            

	hideCursor(false);
	process();
	return 0;
}

