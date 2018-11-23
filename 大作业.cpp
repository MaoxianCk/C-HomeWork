// ����ҵ.cpp: �������̨Ӧ�ó������ڵ㡣
//


#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<windows.h>
#include<dos.h>
#include<ctype.h>
#include<conio.h>
#include<thread>
#include<ctime>
#include<iomanip>
#include<random>
#include<memory.h>
#include<string>
#include<queue>
using namespace std;

struct Point
{
public:
	int x, y;
	Point();
	Point(int x, int y);
	bool operator==(const Point point);
};

Point::Point()
{
	x = 0;
	y = 0;
}
Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}
bool Point::operator==(const Point point)
{
	if (this->x == point.x && this->y == point.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}


class Algorithm
{
public:
	//pΪ��� val��������ֵ board����ָ��ָ���� wid lenΪ�����С cntΪ�������ֵ ��ʼΪ1
	void bfs(Point p, int val, int **board, int width, int height, int &cnt);
};
void Algorithm:: bfs(Point p, int val,int **board,int width,int height,int &cnt)
{
	int key = board[p.y][p.x];
	queue<Point>q;
	cnt = 1;
	q.push(p);
	Point now, next;
	int dir[4][2] = { { 1, 0 },{ -1, 0 },{ 0, 1 },{ 0, -1 } };
	board[p.y][p.x] = -1;//�����-1 �����߹����0
	while (!q.empty())
	{
		now = q.front();
		for (int i = 0; i < 4; i++)
		{
			next.x = now.x + dir[i][0];
			next.y = now.y + dir[i][1];
			if (next.x < width && next.y < height && next.x >= 0 && next.y >= 0)
			{
				if (key == board[next.y][next.x])
				{
					cnt++;//�ҵ��˾ͼ�һ
					board[next.y][next.x] = 0;
					q.push(next);
				}
			}
		}
		q.pop();
	}
}

class Board
{
private:
	int **pboard;
protected:
	int width, height;
public:
	Board();//ʲô������ ���ش�����Ϣ��û�г��ȿ��
	Board(int height, int width);//���ݳ�������ͼ������
	~Board();
	int getWidth();
	int getHeight();
	void display();
	void initialize();//��ʼ������
	void initialize(int info);
	void initializeByRand(int max);
	int** get();
};
Board::Board()
{
	pboard = nullptr;
	cout << "Boardû�д�С��Ϣ" << endl;
}
Board::Board(int height, int width)
{
	this->width = width;
	this->height = height;
	int **board = new int*[height];
	for (int i = 0; i < height; i++)
		board[i] = new int[width];
	pboard = board;
	initialize();
}
Board::~Board()
{
	if (pboard)
	{
		delete[] pboard;
	}
}
int Board::getWidth()
{
	return width;
}
int Board::getHeight()
{
	return height;
}
void Board::display()
{
	if (pboard != nullptr)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				cout << pboard[i][j];
			}
		}
	}
	else
	{
		cout << "������,δָ����С Error form Board::display" << endl;
	}
}
void Board::initialize()
{
	if (pboard != nullptr)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				pboard[i][j] = 0;
			}
		}
	}
	else
	{
		cout << "������ Error form Board::initialize()" << endl;
	}
}
void Board::initialize(int info)
{
	if (pboard != nullptr)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				pboard[i][j]=info;
			}
		}
	}
	else
	{
		cout << "������ Error form Board::initialize(int)" << endl;
	}
}
void Board::initializeByRand(int max)
{
	if (pboard != nullptr)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				Sleep(1);
				pboard[i][j] = rand()%max+1;
			}
		}
	}
	else
	{
		cout << "������ Error form Board::initialize(int)" << endl;
	}
}
int** Board::get()
{
	return pboard;
}

class GameController
{
private:
	Point point;//point.x,point.y  x,y����
	int direct;
	Point inputXY();
	int inputDir();
	virtual void inputClick() {}//������¼�
protected:
	enum Direction { RIGHT, DOWN, LEFT, UP, ENTER,ESC };//���� 0 1 2 3 4 5��Ӧ�������ϻس�ESC ˳ʱ��
public:
	Point getPoint();//��������� x y����Point��ʽ����
	int getDirection();//���뷽��wasd WASD�������� ����������0 1 2 3 4 ��Ӧ�������ϻس�(ö��)  ����Ч��������-1
};
Point GameController::inputXY()
{
	Point point;
	cin >> point.x >> point.y;
	return point;
}
int GameController::inputDir()
{
	char ch;
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
	default:
		return -1;
	}
}
Point GameController::getPoint()
{
	point = inputXY();
	return point;
}
int GameController::getDirection()
{
	direct = inputDir();
	return direct;
}

class WindowsSet
{
private:
protected:
	void updateInfo();
	int X, Y;
	int winWidth, winHeight;
	int scrWidth, scrHeight;
	COORD winSizeCh;
	HWND hwnd;//handle ���
	RECT rect;
	void gameSelect();
public:
	WindowsSet();
	void moveToCenter();
	void setWindowsSize(int, int);
	void setWindowsName(string);
	void setWindowsColor(string);
	void shake();//������
};
WindowsSet::WindowsSet()
{
	hwnd = GetForegroundWindow();//��ȡ��ǰ���
	updateInfo();
//	moveToCenter();
}
void WindowsSet::updateInfo()
{
	GetWindowRect(hwnd, &rect);//��ȡλ��

	this->scrWidth = GetSystemMetrics(SM_CXSCREEN);//��ȡ��Ļ��С
	this->scrHeight = GetSystemMetrics(SM_CYSCREEN);
	this->X = rect.left;//����ԭ����λ��
	this->Y = rect.top;
	winWidth = rect.right - rect.left;
	winHeight = rect.bottom - rect.top;
}
void WindowsSet::moveToCenter()
{
	SetWindowPos(hwnd, HWND_TOP, (scrWidth - winWidth) / 2, (scrHeight - winHeight) / 2, 100, 100, SWP_NOSIZE);
	//cout << X << ' ' << Y << ' ' << winWidth << ' ' << winHeight << ' ' << scrWidth << ' ' << scrHeight << endl;
	updateInfo();
}
void WindowsSet::setWindowsSize(int height, int width)
{
	if (height < 15)
	{
		height = 15;
	}
	if (width < 15)
	{
		width = 15;
	}
	this->winSizeCh.Y = height;
	this->winSizeCh.X = width;

	string temp = "mode con cols=" + to_string(width) + " lines=" + to_string(height);
	char const *size = temp.c_str();
	system(size);

	updateInfo();
	moveToCenter(); 

}
void WindowsSet::setWindowsColor(string info)
{
	if (info.length() == 2)
	{
		if (!((info[0] >= '0'&&info[0] <= '9') || (info[0] >= 'A'&&info[0] <= 'F') || (info[0] >= 'a'&&info[0] <= 'f')) && !((info[1] >= '0'&&info[1] <= '9') || (info[1] >= 'A'&&info[1] <= 'F') || (info[1] >= 'a'&&info[1] <= 'f')))
		{
			cout << "��ɫ��������" << endl;
			return;
		}
	}
	else
	{
		cout << "��ɫ��������" << endl;
		return;
	}
	string temp = "color " + info;
	char const *color = temp.c_str();
	system(color);
}
void WindowsSet::setWindowsName(string name)
{
	char const *temp = name.c_str();
	SetConsoleTitle(temp);
}
void WindowsSet::shake()
{
	int x, y, wait, k;
	GetWindowRect(hwnd, &rect);//��ȡλ��

	x = rect.left;		//ԭ����λ��
	y = rect.top;
	wait = 25;//�ӳ�_����
	k = 5;//�𶯷���

	for (int i = 0; i < 3; i++)
	{
		SetWindowPos(hwnd, HWND_TOPMOST, x + k, y - k, 100, 100, SWP_NOSIZE);
		Sleep(wait);
		SetWindowPos(hwnd, HWND_TOPMOST, x - k, y - k, 100, 100, SWP_NOSIZE);
		Sleep(wait);
		SetWindowPos(hwnd, HWND_TOPMOST, x - k, y + k, 100, 100, SWP_NOSIZE);
		Sleep(wait);
		SetWindowPos(hwnd, HWND_TOPMOST, x + k, y + k, 100, 100, SWP_NOSIZE);
		Sleep(wait);
		SetWindowPos(hwnd, HWND_TOPMOST, x, y, 100, 100, SWP_NOSIZE);
		Sleep(wait);
	}
}
void WindowsSet::gameSelect()
{
	int num;
	cin >> num;
}
class GameView: public WindowsSet//������ʾ������������ع��//����QT
{
private:
	int boardWidth, boardHeight;
	const int gameNum = 3;


	void printStrByCh(string str,int wait);
public:
	GameView();
	GameView(int width, int height);
	void setPos(COORD pos);
	void setPos(int x, int y);
	void HideCursor();
	void HideCursor(bool);
	void HideCursor(bool, int);
	void setTextColor(string temp);
	int getGameNum();
	void displayWinBegin();		 //����ʼ����
	int displayWinSelect();		//����ѡ�����
	void displayFrame();		 //��Ϸ�߿�
};

GameView::GameView()
{
	cout << "GameViewû�д�С��Ϣ" << endl;
	HideCursor();
};
GameView::GameView(int width, int height)
{
	this->boardWidth = width;
	this->boardHeight = height;
	HideCursor();
}
void GameView::setPos(COORD pos)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void GameView::setPos(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void GameView::HideCursor()
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;//�����
	info.bVisible = false;//�Ƿ���ʾ

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void GameView::HideCursor(bool temp)
{

	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;//�����
	info.bVisible = (temp ? false : true);//�Ƿ�����

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void GameView::HideCursor(bool temp,int dwSize)
{
	if (dwSize > 100)
	{
		dwSize = 100;
	}
	CONSOLE_CURSOR_INFO info;
	info.dwSize = dwSize;//�����
	info.bVisible = (temp ? false : true);//�Ƿ�����

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void GameView::setTextColor(string temp)
{

	if (temp == "WHITE")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else if (temp == "RED")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	}
	else if (temp == "GREEN")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	}
	else if (temp == "BLUE")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	}
	else if (temp == "CYAN")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else if (temp == "MAGENTA")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	}
	else if (temp == "YELLOW")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
}
void GameView::printStrByCh(string str, int wait)
{
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		cout << str[i];
		Sleep(wait);
	}
}
int GameView::getGameNum()
{
	return gameNum;
}
void GameView::displayWinBegin()
{	
	system("cls");
	string str = "�� ʼ �� ��";
	int len = str.length();
	setPos((int)(winSizeCh.X-len+0.5)/2,2);

	printStrByCh(str, 70);

	Sleep(1000);
	system("cls");
}
int GameView::displayWinSelect()
{
	const int posX=12, posY=6;//�˵�λ��(�����ϽǶ���)

	int i = 0;
	string menuName = "ѡ����Ϸ:";
	string gameName[] = { "������","2048","���ĵ��"};
	string info = "��ѡ����Ҫ�����Ϸ:";
	string remind = "WSѡ�� ENTERȷ��";
	setPos(posX, posY);

	printStrByCh(menuName, 30);
	for (i = 0; i < gameNum; i++)
	{
		setPos(posX+4, posY + i + 2);
		cout << i + 1 << ".";
		printStrByCh(gameName[i], 30);
	}
	cout << endl;
	setPos(posX * 4, posY + 3);
	printStrByCh(remind, 0);
	setPos(posX, posY + i + 3);
	printStrByCh(info, 30);

	//ѡ����Ϸ
	Sleep(20);
	setPos(posX, posY + 2);
	cout << ">>";
	GameController gameControl;
	int sel = 0;
	while (1)
	{
		setPos(posX + info.length(), posY + i + 3);
		cout << "                      ";
		setPos(posX + info.length(), posY + i + 3);
		printStrByCh(gameName[sel], 15);

		int temp = gameControl.getDirection();
		if (temp == 3)
		{
			sel = (sel <= 0 ? 0 : sel - 1);
			setPos(posX, posY + sel + 3);
			cout << "  ";
			setPos(posX, posY + sel + 2);
			cout << ">>";

		}
		else if (temp == 1)
		{
			sel = (sel >= gameNum - 1 ? gameNum - 1 : sel + 1);
			setPos(posX, posY + sel + 1);
			cout << "  ";
			setPos(posX, posY + sel + 2);
			cout << ">>";
		}
		else if (temp == 4)
		{
			break;
		}
	}
	system("cls");
	return sel;
}
void GameView::displayFrame()
{
	updateInfo();
	string ch[11] = { "��","��","��","��","��","��","��","��","��","��","��" };
					//  0    1   2    3    4    5    6     7    8    9    10
	int bx=2, by=1;
	setPos(bx, by);
	cout << ch[0];
	for (int i = 0; i < winSizeCh.X - 3-2*bx; i++)
	{
		cout << ch[4];
	}
	cout << ch[2];

	for (int i = 0; i < winSizeCh.Y - 1-2*by; i++)
	{
		setPos(bx, bx + i);
		cout << ch[5];
	}

	for (int i = 0; i < winSizeCh.Y - 1-2*by; i++)
	{
		setPos(winSizeCh.X-2*bx, 2*by + i);
		cout << ch[5];
	}

	setPos(bx, winSizeCh.Y - 2*by);
	cout << ch[1];
	for (int i = 0; i < winSizeCh.X - 3-2*bx; i++)
	{
		cout << ch[4];
	}
	cout << ch[3];
}


class Game :public GameController
{
protected:
	int score;
	int life;
	int step;
	Point overPoint = { -1,-1 };
	GameController gameController;
public:
	Game();
	Game(int score, int life, int step);
	virtual bool play() = 0;
	virtual bool replayOrBreak() = 0;
};
Game::Game() :score(0), life(0), step(0) {};
Game::Game(int score, int life, int step) : score(score), life(life), step(step) {};


//������ (�޽���)
class Gomoku :public Game
{
private:
	const int size = 15;
	Board *board=new Board(15, 15);
	GameView *gameView=new GameView(15,15);
	string cheeseman[2] = { "��","��" };
	string playerName[2] = { "���1","���2" };
	Point cursor = { (int)(size / 2),(int)(size / 2) };
	Point ex = cursor;
	enum cheese  { blank,player1,player2 };
	bool isWin(int X,int Y); //win->true   
	bool isEnd();
	int**pboard;
	bool isLegal(int X, int Y);
	Point moveCursor();
	bool replayOrBreak();
public:
	Gomoku();
	void display();
	bool play();
};
Gomoku::Gomoku()
{
	board->initialize(blank);
	pboard = board->get();
	gameView->HideCursor(false);
	gameView->setWindowsSize(42, 85);
	gameView->setWindowsName("������");
}

bool Gomoku::isWin(int X,int Y)
{
	bool win = false;
	int cnt = 1;
	int tempX = X;
	int tempY = Y;
	const int winNum = 5;//ʤ������ ��������

	bool flag=false;



	// ��ά�����¼�ᣬ�ݣ���б����б
	int dir[4][2][2] = 
	{
		// ��
		{ { -1, 0 },{ 1, 0 } },
		// ��  
		{ { 0, -1 },{ 0, 1 } },
		// ��б  
		{ { -1, -1 },{ 1, 1 } },
		// ��б  
		{ { 1, -1 },{ -1, 1 } } 
	};
	for (int i = 0; i < 4; i++) 
	{
		cnt = 1;
		//����  
		for (int j = 0; j < 2; j++)
		{
			flag = true;//�Ƿ�ͬɫ
			while (flag) 
			{
				tempX = tempX + dir[i][j][0];
				tempY = tempY + dir[i][j][1];
				if (tempX >= 0 && tempX < size&&tempY >= 0 && tempY < size)
				{
					if ((pboard[tempY][tempX] == pboard[Y][X])) //����
					{
						cnt++;
					}
					else
					{
						flag = false;
					}
				}
				else
				{
					flag = false;
				}
			}
			tempX = X;
			tempY = Y;
		}

		if (cnt >= winNum) 
		{
			win = true;
			break;
		}
		else
			win = false;
	}
	if (win)
		return 1;
	else
		return 0;
}
bool Gomoku::isEnd()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pboard[i][j] == blank)
			{
				return false;
			}
		}
	}
	return true;
}
bool Gomoku::isLegal(int X, int Y)
{
	if (X >= 0 && X < size&&Y >= 0 && Y < size&&pboard[Y][X]==blank)
		return true;
	return false;
}
void Gomoku::display()
{
	system("cls");
	gameView->displayFrame();
	gameView->setPos(18, 3);
	cout << "WASD���������ƶ� ENTERȷ�� ESC�˳�";
	gameView->setPos(18, 5);
	cout << playerName[0] << "�������� " << cheeseman[0]<<'\t' << playerName[1] << "�������� " << cheeseman[1];

	//�������
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (j < size - 1)
			{
				gameView->setPos(17 + j * 4, 7 + i * 2);
				cout << "��";
			}
			if (i < size - 1)
			{
				gameView->setPos(15 + j * 4, 8 + i * 2);
				cout << "��";
			}
		}
	}
	//���̽��㣨���ӵ㣩
	for (int i = 0; i < size; i++)
	{
		int j;
		for (j = 0; j < size; j++)
		{
			gameView->setPos(15 + j * 4, 7 + i * 2);
			if (pboard[i][j]!=blank)
			{
				if (pboard[i][j] == player1)
				{
					cout << cheeseman[0];
				}
				else if (pboard[i][j] == player2)
				{
					cout << cheeseman[1];
				}
			}
			else if (i == 0 && j == 0)
			{
				cout << "��";
			}
			else if (i == 0 && j == size - 1)
			{
				cout << "��";
			}
			else if (i == size - 1 && j == 0)
			{
				cout << "��";
			}
			else if (i == size - 1 && j == size - 1)
			{
				cout << "��";
			}
			else if (i == 0)
			{
				cout << "��";
			}
			else if (j == size - 1)
			{
				cout << "��";
			}
			else if (j == 0)
			{
				cout << "��";
			}
			else if (i == size - 1)
			{
				cout << "��";
			}
			else 
			{
				cout << "��";
			}

		}
	}
}
Point Gomoku::moveCursor()
{
	gameView->HideCursor(false, 100);
	cursor = ex;
	gameView->setPos(15 + cursor.x * 4, 7 + cursor.y * 2);

	while (true)
	{
		switch (gameController.getDirection())
		{
		case UP:
		{
			cursor.y--;
			if (cursor.y < 0)
			{
				cursor.y = 0;
			}

			break;
		}
		case DOWN:
		{
			cursor.y++;
			if (cursor.y >= size)
			{
				cursor.y = size - 1;
			}
			break;
		}
		case RIGHT:
		{
			cursor.x++;
			if (cursor.x >= size)
			{
				cursor.x = size - 1;
			}
			break;
		}
		case LEFT:
		{
			cursor.x--;
			if (cursor.x < 0)
			{
				cursor.x = 0;
			}
			break;
		}
		case ENTER:
		{
			gameView->HideCursor(true, 100);
			ex = cursor;
			return cursor;
		}
		case ESC:
		{
			gameView->HideCursor(true, 100);
			return overPoint;
		}
		}
		gameView->setPos(15 + cursor.x * 4, 7 + cursor.y * 2);
	}
	return cursor;
}
bool Gomoku::replayOrBreak()
{
	gameView->setPos(25, 7 + size * 2);
	cout << "                                                  ";
	gameView->setPos(25, 7 + size * 2);
	cout << "��J�س� ���¿�ʼ" << endl;

	gameView->setPos(25, 8 + size * 2);
	cout << "                                                  ";
	gameView->setPos(25, 8 + size * 2);
	cout << "��K�س� �ص��˵�" << endl;


	char sel;
	while (1)
	{
		gameView->setPos(25, 9 + size * 2);
		cout << "                 ";
		gameView->setPos(25, 9 + size * 2);
		cin >> sel;
		if (sel == 'j' || sel == 'J' || sel == 'k' || sel == 'K')
		{
			break;
		}
	}
	if (sel == 'k' || sel == 'K')
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool Gomoku::play()
{
		/*gameView->setPos(4, 2);
		cout << "���������1����: ";
		cin >> playerName[0];
		gameView->setPos(4, 4);
		cout << "���������2����: ";
		cin >> playerName[1];*/
		int winner = 0;
		int player = 0;

		while (1)
		{
			display();
			gameView->setPos(13, 7 + size * 2);
			cout << "                                                  ";
			gameView->setPos(13, 7 + size * 2);
			cout << "��" << playerName[player] << " " << cheeseman[player] << " ����:";
			while (1)
			{
				cursor = moveCursor();
				if (cursor == overPoint)
				{
					if (replayOrBreak())
						return true;
					else
						return false;
				}
				if (isLegal(cursor.x, cursor.y))
				{
					if (player == 0)
					{
						pboard[cursor.y][cursor.x] = player1;
					}
					else if (player == 1)
					{
						pboard[cursor.y][cursor.x] = player2;
					}
					break;
				}
				else
				{
					gameView->setPos(13, 7 + size * 2);
					cout << "                                                  ";
					gameView->setPos(13, 7 + size * 2);
					cout << "Υ���߷�" << endl;
					gameView->setPos(13, 8 + size * 2);
					cout << "                                                  ";
					gameView->setPos(13, 8 + size * 2);
					cout << "��" << playerName[player] << "��������:";
				}
			}

			if (isWin(cursor.x, cursor.y))
			{
				display();
				gameView->setPos(13, 7 + size * 2);
				cout << "                                                  ";
				gameView->setPos(13, 7 + size * 2);
				cout << playerName[player] << "ʤ��" << endl;
				winner = 1;
				break;
			}
			if (isEnd())
			{
				display();
				gameView->setPos(13, 7 + size * 2);
				cout << "                                                  ";
				gameView->setPos(13, 7 + size * 2);
				cout << "����";
				break;
			}
			player ^= 1;
		}
		gameView->shake();

		gameView->setPos(13, 8 + size * 2);
		cout << "                                                  ";
		gameView->setPos(13, 8 + size * 2);
		cout << "Game Over" << endl;


		if (replayOrBreak())
			return true;
		else
			return false;
}

//2048
class G2048 :public Game
{
private:
	const int size = 4;
	int MaxNum = 0;
	Board *board = new Board(4, 4);//ԭ����Ϊ1234��ʾ2��n�η�   2^11=2048   ���������ԭ����+1
	GameView *gameView = new GameView(4, 4);
	int **pboard;
	int **pBfsBoard;
	void insertNum();
	int countBlank();
	bool move(int dir);
	bool isEnd();
	void CopyToBfsBoard(int **board);
	bool replayOrBreak();
public:
	G2048();
	void display();
	bool play();
};
G2048::G2048()
{
	board->initialize(0);
	pboard=board->get();

	int **BfsBoard = new int*[size];
	for (int i = 0; i < size; i++)
	{
		BfsBoard[i] = new int[size];
	}
	pBfsBoard = BfsBoard;

	gameView->HideCursor(true);
	gameView->setWindowsSize(25, 80);
	gameView->setWindowsName("2048");
}
void G2048::insertNum()
{
	int cntBlank = countBlank();
	int temp = rand() % cntBlank;//�ڵڼ����ո���� ��֤�����λ��ˢ�·���
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pboard[i][j] == 0)
			{
				if (temp == 0)
				{
					if (rand() % 10 == 0)//      10%����4  2^2;
					{
						pboard[i][j] = 2;
					}
					else
					{
						pboard[i][j] = 1;
					}
					return;
				}
				else
				{
					temp--;
				}
			}
		}
	}
}
int G2048::countBlank()
{
	int cnt = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pboard[i][j] == 0)
			{
				cnt++;
			}
			if (pboard[i][j] > MaxNum)
			{
				MaxNum = pboard[i][j];
			}
		}
	}
	return cnt;
}
void G2048::CopyToBfsBoard(int **board)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			pBfsBoard[i][j] = board[i][j];
		}
	}

}
bool G2048::move(int dir)
{
	bool flag = false;
	switch (dir)
	{
	case UP:
	{
		//ÿ��Ԫ�������� ��ͬ��������0 ����0
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				int temp = pboard[i][j];
				if (temp != 0)
				{
					for (int k = i + 1; k < size; k++)
					{
						//��ͬ��0 ԭλ+1
						if (pboard[k][j] == temp)
						{
							pboard[k][j] = 0;
							pboard[i][j]++;
							score += (int)pow(2, pboard[i][j]);
							flag = true;//��ʾ�з���������ֹû�б仯��ˢ������
							break;
						}
						else if (pboard[k][j] == 0)
						{
							continue;
						}
						else
						{
							break;
						}
					}
				}
			}
		}
		//����Ϸ���0
		for (int h = 0; h < size - 1; h++)//�ظ�size-1��
		{

			for (int j = 0; j < size; j++)
			{
				for (int i = 0; i < size; i++)
				{
					for (int k = i - 1; k >= 0; k--)
					{
						if (pboard[i][j] != 0 && pboard[k][j] == 0)
						{
							flag = true;
							pboard[k][j] = pboard[i][j];
							pboard[i][j] = 0;
						}
					}
				}
			}
		}
		return flag;
	}
	case DOWN:
	{
		flag = false;
		for (int i = size - 1; i >= 0; i--)
		{
			for (int j = 0; j < size; j++)
			{
				int temp = pboard[i][j];
				if (temp != 0)
				{
					for (int k = i - 1; k >= 0; k--)
					{
						//��ͬ��0 ԭλ+1
						if (pboard[k][j] == temp)
						{
							pboard[k][j] = 0;
							pboard[i][j]++;
							score += (int)pow(2, pboard[i][j]);
							flag = true;//��ʾ�з���������ֹû�б仯��ˢ������
							break;
						}
						else if (pboard[k][j] == 0)
						{
							continue;
						}
						else
						{
							break;
						}
					}
				}
			}
		}

		for (int h = 0; h < size - 1; h++)
		{
			for (int j = 0; j < size; j++)
			{
				for (int i = size - 1; i >= 0; i--)
				{
					for (int k = i + 1; k < size; k++)
					{
						if (pboard[i][j] != 0 && pboard[k][j] == 0)
						{
							flag = true;
							pboard[k][j] = pboard[i][j];
							pboard[i][j] = 0;
						}
					}
				}
			}
		}
		return flag;
	}
	case RIGHT:
	{
		flag = false;
		for (int i = 0; i < size; i++)
		{
			for (int j = size - 1; j >= 0; j--)
			{
				int temp = pboard[i][j];
				if (temp != 0)
				{
					for (int k = j - 1; k >= 0; k--)
					{
						//��ͬ��0 ԭλ+1
						if (pboard[i][k] == temp)
						{
							pboard[i][k] = 0;
							pboard[i][j]++;
							score += (int)pow(2, pboard[i][j]);
							flag = true;//��ʾ�з���������ֹû�б仯��ˢ������
							break;
						}
						else if (pboard[i][k] == 0)
						{
							continue;
						}
						else
						{
							break;
						}
					}
				}
			}
		}

		for (int h = 0; h < size - 1; h++)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = size - 1; j >= 0; j--)
				{
					for (int k = j + 1; k < size; k++)
					{
						if (pboard[i][j] != 0 && pboard[i][k] == 0)
						{
							flag = true;
							pboard[i][k] = pboard[i][j];
							pboard[i][j] = 0;
						}
					}
				}
			}
		}
		return flag;
	}

	case LEFT:
	{
		flag = false;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				int temp = pboard[i][j];
				if (temp != 0)
				{
					for (int k = j + 1; k < size; k++)
					{
						//��ͬ��0 ԭλ+1
						if (pboard[i][k] == temp)
						{
							pboard[i][k] = 0;
							pboard[i][j]++;
							score += (int)pow(2, pboard[i][j]);
							flag = true;//��ʾ�з���������ֹû�б仯��ˢ������
							break;
						}
						else if (pboard[i][k] == 0)
						{
							continue;
						}
						else
						{
							break;
						}
					}
				}
			}
		}

		for (int h = 0; h < size - 1; h++)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					for (int k = j - 1; k >= 0; k--)
					{
						if (pboard[i][j] != 0 && pboard[i][k] == 0)
						{
							flag = true;
							pboard[i][k] = pboard[i][j];
							pboard[i][j] = 0;
						}
					}
				}
			}
		}
		return flag;
	}
	}
	return false;
}
void G2048::display()
{

	gameView->displayFrame();
	int FrameSize = this->size + 1;

	//�߽�
	for (int i = 0; i < FrameSize; i++)
	{
		for (int j = 0; j < FrameSize; j++)
		{
			gameView->setPos(8 + j * 8, 4 + i * 4);

			if (i == 0 && j == 0)
			{
				cout << "��";
			}
			else if (i == 0 && j == FrameSize - 1)
			{
				cout << "��";
			}
			else if (i == FrameSize - 1 && j == 0)
			{
				cout << "��";
			}
			else if (i == FrameSize - 1 && j == FrameSize - 1)
			{
				cout << "��";
			}
			else if (i == 0)
			{
				cout << "��";
			}
			else if (j == FrameSize - 1)
			{
				cout << "��";
			}
			else if (j == 0)
			{
				cout << "��";
			}
			else if (i == FrameSize - 1)
			{
				cout << "��";
			}
			else
			{
				cout << "��";
			}
		}
	}
	//�������
	for (int i = 0; i < FrameSize; i++)
	{
		for (int j = 0; j < FrameSize; j++)
		{
			if (j < FrameSize - 1)
			{
				gameView->setPos(10 + j * 8, 4 + i * 4);
				cout << "����������";
			}
			if (i < FrameSize - 1)
			{
				for (int k = 0; k < 3; k++)
				{
					gameView->setPos(8 + j * 8, 5 + i * 4 + k);
					cout << "��";
				}
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pboard[i][j] != 0)
			{
				int k = 0;
				if (pboard[i][j] > 6 && pboard[i][j] < 10)
				{
					k = 1;
				}
				else if (pboard[i][j] >= 10)
				{
					k = 1;
				}
				else
				{
					k = 0;
				}
				gameView->setPos(11 - k + j * 8, 6 + i * 4);
				cout << "     ";
				gameView->setPos(12 - k + j * 8, 6 + i * 4);

				cout << pow(2, pboard[i][j]);
			}
			else if (pboard[i][j] == 0)
			{
				gameView->setPos(9 + j * 8, 6 + i * 4);
				cout << "      ";
			}
		}
	}
	gameView->setPos(size * 11 + 5, 5);
	cout << "                  ";
	gameView->setPos(size*11+5,5);
	cout << "Score: " << score;

	gameView->setPos(size * 11 + 5, 7);
	cout << "                  ";
	gameView->setPos(size * 11 + 5, 7);
	cout << "Max Number: " << pow(2,MaxNum);

	gameView->setPos(size * 11 + 5, 11);
	cout << "WASD���������ƶ�";
	gameView->setPos(size * 11 + 5, 12);
	cout << "ENTERȷ�� ESC�˳�";
}
bool G2048::isEnd()
{
	Algorithm algorithm;
	int cnt = 0;
	Point cursor;
	//���û�п�λ ��һbfs
	if (countBlank() <= 0)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cursor.x = j;
				cursor.y = i;

				CopyToBfsBoard(pboard);
				algorithm.bfs(cursor, pboard[i][j], pBfsBoard, size, size, cnt);
				if (cnt > 1)
				{
					return false;
				}
			}
		}
		return true;
	}
	return false;
}
bool G2048::replayOrBreak()
{
	gameView->setPos(size * 11 + 5, 15);
	cout << "                  ";
	gameView->setPos(size * 11 + 5, 15);
	cout << "��J�س� ���¿�ʼ" << endl;

	gameView->setPos(size * 11 + 5, 16);
	cout << "                  ";
	gameView->setPos(size * 11 + 5, 16);
	cout << "��K�س� �ص��˵�" << endl;

	char sel;
	while (1)
	{
		gameView->setPos(size * 11 + 5, 17);
		cout << "                  ";
		gameView->setPos(size * 11 + 5, 17);
		cin >> sel;
		if (sel == 'j' || sel == 'J' || sel == 'k' || sel == 'K')
		{
			break;
		}
	}
	if (sel == 'k' || sel == 'K')
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool G2048::play()
{
	insertNum();
	display();
	int i = 0;
	bool win = false;
	while (!isEnd())		//û�п�λ ��Ϸ����
	{
		int dir = gameController.getDirection();
		if (dir == ESC)
		{
			if (replayOrBreak())
				return true;
			else
				return false;
		}
		if (move(dir))
		{
			display();
			//Sleep(50);
			insertNum();
		}
		display();
		if (MaxNum >= 2048)
		{
			win = true;
		}
	}
	gameView->setPos(size * 11 + 5, 9);
	cout << "                  ";
	gameView->setPos(size * 11 + 5, 9);

	if (win)
	{
		cout << "You are win!";
	}
	else
	{
		cout << "Game Over!";
	}

	gameView->shake();

	if (replayOrBreak())
		return true;
	else
		return false;
	
}

class HappyClick:public Game
{
private:
	const int size = 5;
	int max = 5;
	Board*board = new Board(5, 5);
	int BfsBoard[5][5];
	GameView *gameView = new GameView(5, 5);
	Algorithm algorithm;
	int **pboard;
	int **pBfsBoard;
	Point cursor = { (int)(size / 2),(int)(size / 2) };
	Point ex = cursor;
	bool isEnd();
	void ClickAdd(Point p);
	bool Click(Point cursor);
	void CopyToBfsBoard(int **board);
	void moveDown();
	void combing();//if(t)����ʱ++ ���򲻱����ڳ�ʼ��
	void clean();
	Point moveCursor();
	bool replayOrBreak();
public:
	HappyClick();
	void display();
	bool play();
};
HappyClick::HappyClick():Game(0,5,0)
{	
	board->initializeByRand(max);
	pboard = board->get();

	int **BfsBoard = new int*[size];
	for (int i = 0; i < size; i++)
		BfsBoard[i] = new int[size];
	pBfsBoard = BfsBoard;
	CopyToBfsBoard(pboard);

	gameView->HideCursor(true,100);
	gameView->setWindowsSize(30, 80);
	gameView->setWindowsName("���ĵ��");
}
bool HappyClick::isEnd()
{
	if (life > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void HappyClick::ClickAdd(Point p)
{	
	CopyToBfsBoard(pboard);
	display();
	Sleep(500);
	pboard[p.y][p.x]++;

	Sleep(500);
	display();

	int temp = pboard[p.y][p.x];
	CopyToBfsBoard(pboard);
	int cnt = 1;
	algorithm.bfs(p, temp, pBfsBoard, size, size, cnt);

	if (cnt >= 3)
	{
		display();
		Sleep(500);

		score += cnt*temp;
		pboard[p.y][p.x] = temp + 1;

		display();
		Sleep(500);

		moveDown();		
		
		display();
		Sleep(500);

		clean();
		
		display();
		Sleep(500);

		combing();
	}
	else
	{
		CopyToBfsBoard(pboard);
		life--;
	}
}
bool HappyClick::Click(Point p)
{
	int temp = pboard[p.y][p.x];
	CopyToBfsBoard(pboard);
	int cnt = 1;
	algorithm.bfs(p, temp, pBfsBoard, size, size, cnt);
	bool flag = false;

	if (cnt >= 3)
	{
		score += cnt*temp;
		if (step == 0)
		{
			pboard[p.y][p.x] = temp;
		}
		else
		{
			pboard[p.y][p.x] = temp + 1;
		}
		if (step != 0)
		{
			display();
			Sleep(500);
		}
		moveDown();
		if (step != 0)
		{
			display();
			Sleep(500);
		}
		clean();
		if (step != 0)
		{
			display();
			Sleep(500);
		}
		flag = true;
	}
	return flag;
}
void HappyClick::CopyToBfsBoard(int **board)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			pBfsBoard[i][j] = board[i][j];
		}
	}

}
void HappyClick::clean()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pBfsBoard[i][j] == 0)
			{
				pboard[i][j] = rand() % max+1;
			}
		}
	}
	CopyToBfsBoard(pboard);
}
Point HappyClick::moveCursor()
{
	gameView->HideCursor(false, 100);
	cursor = ex;
	gameView->setPos(12 + cursor.x * 8, 6 + cursor.y * 4);
	while (true)
	{
		switch (gameController.getDirection())
		{
			case UP:
			{
				cursor.y--;
				if (cursor.y < 0)
				{
					cursor.y = 0;
				}

				break;
			}
			case DOWN:
			{
				cursor.y++;
				if (cursor.y >= size)
				{
					cursor.y = size - 1;
				}
				break;
			}
			case RIGHT:
			{
				cursor.x++;
				if (cursor.x >= size)
				{
					cursor.x = size - 1;
				}
				break;
			}
			case LEFT:
			{
				cursor.x--;
				if (cursor.x < 0)
				{
					cursor.x = 0;
				}
				break;
			}
			case ENTER:
			{
				gameView->HideCursor(true, 100);
				ex = cursor;
				return cursor;
			}
			case ESC:
			{
				gameView->HideCursor(true, 100);
				return overPoint;
			}
		}
		gameView->setPos(12 + cursor.x * 8, 6 + cursor.y * 4);
	}
	return cursor;
}
void  HappyClick::moveDown()
{
	for (int h = 0; h < size - 1; h++)
	{
		for (int j = 0; j < size; j++)//�� |
		{
			for (int i = size - 1; i > 0; i--)//�� ��
			{
				if (pBfsBoard[i][j] == 0)
				{
					for (int k = i; k > 0; k--)
					{
						swap(pBfsBoard[k][j], pBfsBoard[k - 1][j]);
						swap(pboard[k][j], pboard[k - 1][j]);
					}
				}
			}
		}
	}
}
void  HappyClick::combing()
{
	bool flag = true;
	Point cursor;
	while (flag)
	{
		flag = false;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cursor.x = j;
				cursor.y = i;
				flag = Click(cursor);
				if (flag)
				{
					life++;
					if (life > 5)
					{
						life = 5;
					}
					break;
				}
			}
			if (flag)
			{
				break;
			}
		}

	}
}
void HappyClick::display()
{
	gameView->displayFrame();
	int FrameSize = this->size + 1;


	//�߽�
	for (int i = 0; i < FrameSize; i++)
	{
		for (int j = 0; j < FrameSize; j++)
		{
			gameView->setPos(8 + j * 8, 4 + i * 4);

			if (i == 0 && j == 0)
			{
				cout << "��";
			}
			else if (i == 0 && j == FrameSize - 1)
			{
				cout << "��";
			}
			else if (i == FrameSize - 1 && j == 0)
			{
				cout << "��";
			}
			else if (i == FrameSize - 1 && j == FrameSize - 1)
			{
				cout << "��";
			}
			else if (i == 0)
			{
				cout << "��";
			}
			else if (j == FrameSize - 1)
			{
				cout << "��";
			}
			else if (j == 0)
			{
				cout << "��";
			}
			else if (i == FrameSize - 1)
			{
				cout << "��";
			}
			else
			{
				cout << "��";
			}
		}
	}
	//�������
	for (int i = 0; i < FrameSize; i++)
	{
		for (int j = 0; j < FrameSize; j++)
		{
			if (j < FrameSize - 1)
			{
				gameView->setPos(10 + j * 8, 4 + i * 4);
				cout << "����������";
			}
			if (i < FrameSize - 1)
			{
				for (int k = 0; k < 3; k++)
				{
					gameView->setPos(8 + j * 8, 5 + i * 4 + k);
					cout << "��";
				}
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			
				int k = 0;
				if (pboard[i][j] >10)
				{
					k = 1;
				}
				else
				{
					k = 0;
				}
				gameView->setPos(12 - k + j * 8, 6 + i * 4);
				cout << "    ";
				gameView->setPos(12 - k + j * 8, 6 + i * 4);
				if (pBfsBoard[i][j] != 0)
				{
					cout << pboard[i][j];
				}
		}
	}
	gameView->setPos(size * 11 + 3, 5);
	cout << "              ";
	gameView->setPos(size * 11 + 3, 5);
	cout << "Score: " << score;

	gameView->setPos(size * 11 + 3, 7);
	cout << "               ";
	gameView->setPos(size * 11 + 3, 7);
	cout << "Life : " << life;

	gameView->setPos(size * 11 + 3, 9);
	cout << "WASD���������ƶ�";
	gameView->setPos(size * 11 + 3, 10);
	cout << "ENTERȷ�� ESC�˳�";
}
bool HappyClick::replayOrBreak()
{
	gameView->setPos(size * 11 + 3, 12);
	cout << "                  ";
	gameView->setPos(size * 11 + 3, 12);
	cout << "��J�س� ���¿�ʼ" << endl;

	gameView->setPos(size * 11 + 3, 13);
	cout << "                  ";
	gameView->setPos(size * 11 + 3, 13);
	cout << "��K�س� �ص��˵�" << endl;

	char sel;
	while (1)
	{
		gameView->setPos(size * 11 + 3, 14);
		cout << "                  ";
		gameView->setPos(size * 11 + 3, 14);
		cin >> sel;
		if (sel == 'j' || sel == 'J' || sel == 'k' || sel == 'K')
		{
			break;
		}
	}
	if (sel == 'k' || sel == 'K')
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool HappyClick::play()
{
	
	combing();
	score = 0;
	life = 5;
	cursor.x = (int)(size / 2);
	cursor.y = (int)(size / 2);
	display();
	while (!isEnd())
	{
		step++;//�غ���
		Point dir= moveCursor();
		if (dir == overPoint)
		{
			if (replayOrBreak())
				return true;
			else
				return false;
		}
		ClickAdd(dir);
	}
	gameView->shake();
	gameView->setPos(size * 11 + 3, 9);
	cout << "              ";
	gameView->setPos(size * 11 + 3, 9);
	cout << "Game Over" << score;

	if (replayOrBreak())
		return true;
	else
		return false;
}
class GameApp
{
public:
	GameApp();
};
GameApp::GameApp()
{

	GameView vi;
	bool over = false;

	//��ʼmenu
	vi.setWindowsSize(45, 150);
	vi.setWindowsName("maoxian");
	vi.displayWinBegin();
	while (1)
	{
		//��ʼmenu
		vi.setWindowsSize(45, 150);
		vi.setWindowsName("maoxian");

		//ѡ����Ϸ
		vi.displayFrame();
		int sel = 0;
		sel = vi.displayWinSelect();

		//������Ϸ
		int gameNum = vi.getGameNum();

		switch (sel)
		{
		case 0:
		{
			while (1)
			{
				Gomoku gomoku;
				over = gomoku.play();
				if (!over)
				{
					break;
				}
			}
			break;
		}
		case 1:
		{
			while (1)
			{
				G2048 g2048;
				over = g2048.play();
				if (!over)
				{
					break;
				}
			}
			break;
		}
		case 2:
		{
			while (1)
			{
				HappyClick happyClick;
				over = happyClick.play();
				if (!over)
				{
					break;
				}
			}
			break;
		}
		}
	}
}

int main()
{	
	srand((unsigned int)time(0));
	GameApp gameApp;
	return 0;
}