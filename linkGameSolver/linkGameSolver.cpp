// 连连看.cpp: 定义控制台应用程序的入口点。
//
#include <cmath>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <memory.h>
#include <queue>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <time.h>
#include <windows.h>

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0) //必要的，我是背下来的

using namespace std;

/*
//原始标准数据
//窗口位置
static const int windowX = 50;
static const int windowY = 50;
//窗口内到地图的偏移量
static const int raceX = 17;
static const int raceY = 184;
//地图大小
static const int sizeX = 19;
static const int sizeY = 11;

//方块大小
static const int blockSizeX = 25;
static const int blockSizeY = 29;
//每个方块之间的间隔
static const int blank = 6;
*/

//精度值，影响速度
static const int radious = 11;
//窗口位置
static const int windowX = 50;
static const int windowY = 50;
//窗口内到地图的偏移量
static const int raceX = 17 + radious;
static const int raceY = 184 + radious;
//地图大小
static const int sizeX = 19;
static const int sizeY = 11;
//方块大小
static const int blockSizeX = 25 - radious * 2;
static const int blockSizeY = 29 - radious * 2;
//每个方块之间的间隔
static const int blank = 6 + radious * 2;

//剩余方块数量
int cnt = 0;

//点坐标带方向与当前步数
struct PointDir
{
	int x;
	int y;
	int step;//bfs中距离起点的距离
	int dir;//bfs中当前拓展的方向
};

//RGB颜色
class Color
{
  public:
	unsigned char R; //红色的亮度
	unsigned char G; //绿色的亮度
	unsigned char B; //蓝色的亮度
	Color(); //初始化参数为0
	Color(int r, int g, int b); //以rgb值初始化参数
	void operator=(COLORREF c); //以COLORREF对象赋值
	bool operator==(Color &c);
	bool operator!=(Color &c);
	void displayRGBInfo();
};

Color::Color()
{
	//默认构造函数初始化参数
	R = 0;
	G = 0;
	B = 0;
}
Color::Color(int r, int g, int b)
{
	//构造函数，根据传入rgb值初始化参数
	if (r > 255)
	{
		r = 255;
	}
	if (r < 0)
	{
		r = 0;
	}
	if (g > 255)
	{
		g = 255;
	}
	if (g < 0)
	{
		g = 0;
	}
	if (b > 255)
	{
		b = 255;
	}
	if (b < 0)
	{
		b = 0;
	}
	R = r;
	G = g;
	B = b;
}
void Color::operator=(COLORREF c)
{
	this->R = GetRValue(c);
	this->G = GetGValue(c);
	this->B = GetBValue(c);
}
bool Color::operator==(Color &c)
{
	if (this->R == c.R && this->G == c.G && this->B == c.B)
	{
		return true;
	}
	return false;
}
bool Color::operator!=(Color &c)
{
	if (this->R != c.R || this->G != c.G || this->B != c.B)
	{
		return true;
	}
	return false;
}
void Color::displayRGBInfo()
{
	std::cout << "R:" << (int)R << " G:" << (int)G << " B:" << (int)B << std::endl;
}

//一个方块
class Block
{
  public:
	Color rect[blockSizeY][blockSizeX];//一个方块内的所有像素点信息
	Block();// 初始化0
	bool operator==(Block &b);
};
Block::Block()
{
	memset(rect, 0, sizeof(rect));
}
bool Block::operator==(Block &b)
{
	for (int i = 0; i < blockSizeY; i++)
	{
		for (int j = 0; j < blockSizeX; j++)
		{
			if (b.rect[i][j].R != this->rect[i][j].R)
			{
				return false;
			}
			if (b.rect[i][j].G != this->rect[i][j].G)
			{
				return false;
			}
			if (b.rect[i][j].B != this->rect[i][j].B)
			{
				return false;
			}
		}
	}
	return true;
}

//设置控制台光标位置
void setPos(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//根据传入的image数组，创建截取的图片，仅调试时开启
void creatBmp(string str, Color image[blockSizeY][blockSizeX])
{

	ofstream fout;
	fout.open(str, ios::binary);

	unsigned short BmpFileType = 19778;							 //文件类型BM
	unsigned int BmpFileSize = blockSizeX * blockSizeY * 3 + 54; //指定文件大小
	unsigned short BmpFileReserved1 = 0;						 //保留 必须为0
	unsigned short BmpFileReserved2 = 0;						 //保留 必须为0
	unsigned int BmpFileOffbits = 54;							 //从文件头到位图的偏移量

	unsigned int InfoSize = 40;								 //本结构的大小 40B
	unsigned int BmpWidth = blockSizeX;						 //宽度
	unsigned int BmpHeight = blockSizeY;					 //高度
	unsigned short BmpPlanes = 1;							 //目标设备的级别 必须为1
	unsigned short BmpCount = 24;							 //位深度 每个像素点的位数 必须为 1 4 8 24 此处数值表示为2^n色
	unsigned int BmpCompression = 0;						 //压缩类型 必须是 0(不压缩), 1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型)
	unsigned int BmpSizeImage = blockSizeX * blockSizeY * 3; //实际位图数据占用量 B
	unsigned int BmpXPelsPerMeter = 0;						 //X 水平分辨率
	unsigned int BmpYPelsPerMeter = 0;						 //Y 垂直分辨率
	unsigned int BmpClrUsed = 0;							 //实际颜色数
	unsigned int BmpClrImportant = 0;						 //重要颜色数

	int zeroNum = (4 - ((BmpWidth * BmpCount / 8) % 4)) % 4;

	//根据 高度 宽度 位深度 更新数据
	BmpFileSize = 14 + 40 + BmpHeight * (BmpWidth + zeroNum) * (BmpCount / 8);
	BmpFileOffbits = (BmpCount <= 8 ? 14 + 40 + 4 * (int)pow(2, BmpCount) : 14 + 40);
	InfoSize = 40;
	BmpSizeImage = BmpHeight * (BmpWidth + zeroNum) * (BmpCount / 8);

	//写入信息

	//文件头
	cout << "写入文件头..." << endl;
	fout.write((char *)&BmpFileType, 2);
	fout.write((char *)&BmpFileSize, 4);
	fout.write((char *)&BmpFileReserved1, 2);
	fout.write((char *)&BmpFileReserved2, 2);
	fout.write((char *)&BmpFileOffbits, 4);
	//信息头
	cout << "写入信息头..." << endl;
	fout.write((char *)&InfoSize, 4);
	fout.write((char *)&BmpWidth, 4);
	fout.write((char *)&BmpHeight, 4);
	fout.write((char *)&BmpPlanes, 2);
	fout.write((char *)&BmpCount, 2);
	fout.write((char *)&BmpCompression, 4);
	fout.write((char *)&BmpSizeImage, 4);
	fout.write((char *)&BmpXPelsPerMeter, 4);
	fout.write((char *)&BmpYPelsPerMeter, 4);
	fout.write((char *)&BmpClrUsed, 4);
	fout.write((char *)&BmpClrImportant, 4);

	//图像
	cout << "写入图像信息..." << endl;

	for (int i = (int)BmpHeight - 1; i >= 0; i--)
	{
		for (int j = 0; j < (int)BmpWidth; j++)
		{
			fout.write((char *)&image[i][j].B, 1);
			fout.write((char *)&image[i][j].G, 1);
			fout.write((char *)&image[i][j].R, 1);
		}
		char *temp = 0x00;
		for (int j = 0; j < (int)zeroNum; j++)
		{
			fout.write((char *)&temp, 1);
		}
	}
	cout << "文件" << str << "保存成功" << endl;
	fout.close();
}

//*************************************************************************************

class linkGameSolver
{
  private:
	const char *titleName = "QQ游戏 - 连连看角色版";
	queue<PointDir> qClick;

	int map[11][19];
	HWND hwnd = NULL;
	const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  public:
	linkGameSolver()
	{
		memset(map, 0, sizeof(int) * sizeX * sizeY);

		findAndSetPos();
	}
	void showMap()
	{
		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				cout << map[i][j];
				if (map[i][j] < 10)
				{
					cout << "  ";
				}
				else
				{
					cout << " ";
				}
			}
			cout << endl;
		}
	}

	//HWND hwnd=NULL //初始化窗口句柄
	void findAndSetPos()
	{

		cout << "正在查找窗口 <<" << titleName << ">>..." << endl;
		while (hwnd == NULL)
		{
			hwnd = FindWindow(NULL, TEXT("QQ游戏 - 连连看角色版"));
			Sleep(500);
		}
		system("cls");

		cout << "窗口已找到" << endl;
		cout << "设置窗口位置" << endl;
		SetWindowPos(hwnd, HWND_TOP, windowX, windowY, 0, 0, SWP_NOSIZE);// 设置窗口位置但不改变大小
		SetForegroundWindow(hwnd);// 激活窗口
	}

	//截转换地图为二维数组 保存于map
	//窗口内部 据数据区17*184
	//数据区   方块29*59  距离6
	void getMap()
	{
		cout << "获取方块信息..." << endl;
		//保存每个方块的rgb值
		HDC hdc = GetDC(hwnd);
		Block block[sizeY][sizeX];

		for (int row = 0; row < sizeY; row++)
		{
			for (int col = 0; col < sizeX; col++)
			{
				setPos(0, 3);
				cout << "                                                           ";
				setPos(0, 3);
				cout << "正在获取block[" << row << "][" << col << "]块信息..." << endl;
				for (int i = 0; i < blockSizeY; i++)
				{
					for (int j = 0; j < blockSizeX; j++)
					{
						block[row][col].rect[i][j] = GetPixel(hdc, raceX + col * (blockSizeX + blank) + j, raceY + row * (blockSizeY + blank) + i);
					}
				}
			}
		}
		/*
		//保存图片bmp
		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				string str = "block[" + to_string(i) + "][" + to_string(j) + "].bmp";
				creatBmp(str, block[i][j].rect);
			}
		}
		*/

	    Block space;
		for (int i = 0; i < blockSizeY; i++)
		{
			for (int j = 0; j < blockSizeX; j++)
			{
				//设置空白方块的rgb值
				space.rect[i][j].R = 48;
				space.rect[i][j].G = 76;
				space.rect[i][j].B = 112;
			}
		}

		int cnt = 1;//起始编号为1,0表示为空地
		Block pblock[50];//临时变量，保存已经出现过的牌形种类
		pblock[0] = space;

		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				bool flag = false;
				for (int k = 0; k < cnt; k++)
				{
					//越界处理提示，一般不会出现
					if (k == 49)
					{
						cout << "牌面数量太多！" << endl;
						break;
					}
					if (block[i][j] == pblock[k])
					{
						map[i][j] = k;
						flag = true;
						break;
					}
				}
				if (!flag)
				{
					pblock[cnt] = block[i][j];
					map[i][j] = cnt;
					cnt++;
				}
			}
		}
	}

	bool checkOver()
	{
		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				if (map[i][j] != 0)
				{
					return false;
				}
			}
		}
		return true;
	}

    //该bfs仅判断单个方块是否有对应可达终点方块
    //inX,inY为起点方块,ansX,ansY为找到的可连接的终点方块
	bool bfs(int inX, int inY, int &ansX, int &ansY)
	{
		PointDir inp, curp, nextp;//起点，当前访问点，下一访问点
		//初始化起点
		inp.x = inX;
		inp.y = inY;
		inp.step = -1;// 由起点开始的点出发时step必定+1变为0
		inp.dir = -1;// 起点不设置有效方向，便于step计数

		//q保存bfs待访问队列
		queue<PointDir> q;
		curp = inp;
		q.push(curp);
		bool isFind = false;//是否找到可连接的对应方块
		//当队列不空并且没有找到对应终点方块时继续循环
		while (!q.empty() && isFind == false)
		{
			curp = q.front();
			q.pop();
			//上下左右四个方向，dirs[][]数组为四个方向的向量数组
			for (int k = 0; k < 4; k++)
			{
				nextp.x = curp.x + dirs[k][0];
				nextp.y = curp.y + dirs[k][1];
				nextp.dir = k;
				nextp.step = curp.step;
				//当当前访问点方向与上一点方向不相同，判定为拐点，step++
				if (curp.dir != k)
				{
					nextp.step++;
				}
				//当拐点大于2个(不符合连连看消除条件路径)跳过当前次循环
				if (nextp.step > 2)
				{
					continue;
				}
				//当当前点为起点时跳过当前次循环
				//因为连连看可消除路径数小于可到达路径数，故不判定当前点是否曾经被走过即用一个bool visited[][]保存访问状态，若有更好解决办法欢迎讨论。
				if (nextp.x == inp.x && nextp.y == inp.y)
				{
					continue;
				}
				//边界检查
				if ((nextp.x >= 0) && (nextp.x < sizeX) && (nextp.y >= 0) && (nextp.y < sizeY))
				{
					//若是空地加入待访问队列
					if (map[nextp.y][nextp.x] == 0)
					{
						q.push(nextp);
					}
					//若与起点方块相同，则判定找到对应终点方块，记录并退出循环
					if (map[nextp.y][nextp.x] == map[inp.y][inp.x])
					{
						map[inp.y][inp.x] = 0;
						map[nextp.y][nextp.x] = 0;
						ansX = nextp.x;
						ansY = nextp.y;
						isFind = true;
						break;
					}
				}
			}
		}
		return isFind;
	}

	//计算点击顺序并保存在待点击队列qClick里
	void caculate()
	{
		cnt = 0;
		for (int k = 0; k < 5; k++)
		{
			if (checkOver())
			{
				break;
			}
			for (int i = 0; i < sizeY; i++)
			{
				for (int j = 0; j < sizeX; j++)
				{
					//对每一个点bfs展开
					if (map[i][j] != 0) //0是空地
					{

						PointDir p1;
						p1.x = j;
						p1.y = i;
						PointDir p2;
						if (bfs(j, i, p2.x, p2.y))
						{
							qClick.push(p1);
							qClick.push(p2);
							cnt += 2;
						}
					}
				}
			}
		}
	}

	//run!
	void nice()
	{
		while (!qClick.empty())
		{
			int time = rand() % 600 + 170;
			if (rand() % 5 < 1)
			{
				time = 1000;
			}
			if (cnt == 40)
			{
				time = rand() % 400 + 70;
				cout << "加速了" << endl;
			}
                                               
			time = 10;
			Sleep(time);
			if (KEY_DOWN(VK_SPACE))
			{
				break;
			}
			PointDir p;
			p = qClick.front();

			SetCursorPos(windowX + raceX + p.x * (blockSizeX + blank), windowY + raceY + p.y * (blockSizeY + blank));

			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(10); //要留给某些应用的反应时间
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			cnt--;
			qClick.pop();
		}
	}
};

int main()
{
	srand(time(0));
	SetWindowPos(GetForegroundWindow(), HWND_TOP, 1000, 100, 300, 300, SWP_NOACTIVATE);
	cout << "按回车键开始" << endl;
	while (1)
	{
		if (KEY_DOWN(VK_RETURN))
		{
			linkGameSolver linkGameSolver;
			linkGameSolver.getMap();
			//linkGameSolver.showMap();

			linkGameSolver.caculate();
			cout << "地图匹配完成" << endl;
			linkGameSolver.nice();

			system("cls");
			cout << "按回车键开始" << endl;
		}
	}
	return 0;
}
