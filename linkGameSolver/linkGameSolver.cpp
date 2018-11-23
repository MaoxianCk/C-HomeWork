// ������.cpp: �������̨Ӧ�ó������ڵ㡣
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

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0) //��Ҫ�ģ����Ǳ�������

using namespace std;

/*
//ԭʼ��׼����
//����λ��
static const int windowX = 50;
static const int windowY = 50;
//�����ڵ���ͼ��ƫ����
static const int raceX = 17;
static const int raceY = 184;
//��ͼ��С
static const int sizeX = 19;
static const int sizeY = 11;

//�����С
static const int blockSizeX = 25;
static const int blockSizeY = 29;
//ÿ������֮��ļ��
static const int blank = 6;
*/

//����ֵ��Ӱ���ٶ�
static const int radious = 11;
//����λ��
static const int windowX = 50;
static const int windowY = 50;
//�����ڵ���ͼ��ƫ����
static const int raceX = 17 + radious;
static const int raceY = 184 + radious;
//��ͼ��С
static const int sizeX = 19;
static const int sizeY = 11;
//�����С
static const int blockSizeX = 25 - radious * 2;
static const int blockSizeY = 29 - radious * 2;
//ÿ������֮��ļ��
static const int blank = 6 + radious * 2;

//ʣ�෽������
int cnt = 0;

//������������뵱ǰ����
struct PointDir
{
	int x;
	int y;
	int step;//bfs�о������ľ���
	int dir;//bfs�е�ǰ��չ�ķ���
};

//RGB��ɫ
class Color
{
  public:
	unsigned char R; //��ɫ������
	unsigned char G; //��ɫ������
	unsigned char B; //��ɫ������
	Color(); //��ʼ������Ϊ0
	Color(int r, int g, int b); //��rgbֵ��ʼ������
	void operator=(COLORREF c); //��COLORREF����ֵ
	bool operator==(Color &c);
	bool operator!=(Color &c);
	void displayRGBInfo();
};

Color::Color()
{
	//Ĭ�Ϲ��캯����ʼ������
	R = 0;
	G = 0;
	B = 0;
}
Color::Color(int r, int g, int b)
{
	//���캯�������ݴ���rgbֵ��ʼ������
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

//һ������
class Block
{
  public:
	Color rect[blockSizeY][blockSizeX];//һ�������ڵ��������ص���Ϣ
	Block();// ��ʼ��0
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

//���ÿ���̨���λ��
void setPos(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//���ݴ����image���飬������ȡ��ͼƬ��������ʱ����
void creatBmp(string str, Color image[blockSizeY][blockSizeX])
{

	ofstream fout;
	fout.open(str, ios::binary);

	unsigned short BmpFileType = 19778;							 //�ļ�����BM
	unsigned int BmpFileSize = blockSizeX * blockSizeY * 3 + 54; //ָ���ļ���С
	unsigned short BmpFileReserved1 = 0;						 //���� ����Ϊ0
	unsigned short BmpFileReserved2 = 0;						 //���� ����Ϊ0
	unsigned int BmpFileOffbits = 54;							 //���ļ�ͷ��λͼ��ƫ����

	unsigned int InfoSize = 40;								 //���ṹ�Ĵ�С 40B
	unsigned int BmpWidth = blockSizeX;						 //���
	unsigned int BmpHeight = blockSizeY;					 //�߶�
	unsigned short BmpPlanes = 1;							 //Ŀ���豸�ļ��� ����Ϊ1
	unsigned short BmpCount = 24;							 //λ��� ÿ�����ص��λ�� ����Ϊ 1 4 8 24 �˴���ֵ��ʾΪ2^nɫ
	unsigned int BmpCompression = 0;						 //ѹ������ ������ 0(��ѹ��), 1(BI_RLE8ѹ������)��2(BI_RLE4ѹ������)
	unsigned int BmpSizeImage = blockSizeX * blockSizeY * 3; //ʵ��λͼ����ռ���� B
	unsigned int BmpXPelsPerMeter = 0;						 //X ˮƽ�ֱ���
	unsigned int BmpYPelsPerMeter = 0;						 //Y ��ֱ�ֱ���
	unsigned int BmpClrUsed = 0;							 //ʵ����ɫ��
	unsigned int BmpClrImportant = 0;						 //��Ҫ��ɫ��

	int zeroNum = (4 - ((BmpWidth * BmpCount / 8) % 4)) % 4;

	//���� �߶� ��� λ��� ��������
	BmpFileSize = 14 + 40 + BmpHeight * (BmpWidth + zeroNum) * (BmpCount / 8);
	BmpFileOffbits = (BmpCount <= 8 ? 14 + 40 + 4 * (int)pow(2, BmpCount) : 14 + 40);
	InfoSize = 40;
	BmpSizeImage = BmpHeight * (BmpWidth + zeroNum) * (BmpCount / 8);

	//д����Ϣ

	//�ļ�ͷ
	cout << "д���ļ�ͷ..." << endl;
	fout.write((char *)&BmpFileType, 2);
	fout.write((char *)&BmpFileSize, 4);
	fout.write((char *)&BmpFileReserved1, 2);
	fout.write((char *)&BmpFileReserved2, 2);
	fout.write((char *)&BmpFileOffbits, 4);
	//��Ϣͷ
	cout << "д����Ϣͷ..." << endl;
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

	//ͼ��
	cout << "д��ͼ����Ϣ..." << endl;

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
	cout << "�ļ�" << str << "����ɹ�" << endl;
	fout.close();
}

//*************************************************************************************

class linkGameSolver
{
  private:
	const char *titleName = "QQ��Ϸ - ��������ɫ��";
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

	//HWND hwnd=NULL //��ʼ�����ھ��
	void findAndSetPos()
	{

		cout << "���ڲ��Ҵ��� <<" << titleName << ">>..." << endl;
		while (hwnd == NULL)
		{
			hwnd = FindWindow(NULL, TEXT("QQ��Ϸ - ��������ɫ��"));
			Sleep(500);
		}
		system("cls");

		cout << "�������ҵ�" << endl;
		cout << "���ô���λ��" << endl;
		SetWindowPos(hwnd, HWND_TOP, windowX, windowY, 0, 0, SWP_NOSIZE);// ���ô���λ�õ����ı��С
		SetForegroundWindow(hwnd);// �����
	}

	//��ת����ͼΪ��ά���� ������map
	//�����ڲ� ��������17*184
	//������   ����29*59  ����6
	void getMap()
	{
		cout << "��ȡ������Ϣ..." << endl;
		//����ÿ�������rgbֵ
		HDC hdc = GetDC(hwnd);
		Block block[sizeY][sizeX];

		for (int row = 0; row < sizeY; row++)
		{
			for (int col = 0; col < sizeX; col++)
			{
				setPos(0, 3);
				cout << "                                                           ";
				setPos(0, 3);
				cout << "���ڻ�ȡblock[" << row << "][" << col << "]����Ϣ..." << endl;
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
		//����ͼƬbmp
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
				//���ÿհ׷����rgbֵ
				space.rect[i][j].R = 48;
				space.rect[i][j].G = 76;
				space.rect[i][j].B = 112;
			}
		}

		int cnt = 1;//��ʼ���Ϊ1,0��ʾΪ�յ�
		Block pblock[50];//��ʱ�����������Ѿ����ֹ�����������
		pblock[0] = space;

		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				bool flag = false;
				for (int k = 0; k < cnt; k++)
				{
					//Խ�紦����ʾ��һ�㲻�����
					if (k == 49)
					{
						cout << "��������̫�࣡" << endl;
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

    //��bfs���жϵ��������Ƿ��ж�Ӧ�ɴ��յ㷽��
    //inX,inYΪ��㷽��,ansX,ansYΪ�ҵ��Ŀ����ӵ��յ㷽��
	bool bfs(int inX, int inY, int &ansX, int &ansY)
	{
		PointDir inp, curp, nextp;//��㣬��ǰ���ʵ㣬��һ���ʵ�
		//��ʼ�����
		inp.x = inX;
		inp.y = inY;
		inp.step = -1;// ����㿪ʼ�ĵ����ʱstep�ض�+1��Ϊ0
		inp.dir = -1;// ��㲻������Ч���򣬱���step����

		//q����bfs�����ʶ���
		queue<PointDir> q;
		curp = inp;
		q.push(curp);
		bool isFind = false;//�Ƿ��ҵ������ӵĶ�Ӧ����
		//�����в��ղ���û���ҵ���Ӧ�յ㷽��ʱ����ѭ��
		while (!q.empty() && isFind == false)
		{
			curp = q.front();
			q.pop();
			//���������ĸ�����dirs[][]����Ϊ�ĸ��������������
			for (int k = 0; k < 4; k++)
			{
				nextp.x = curp.x + dirs[k][0];
				nextp.y = curp.y + dirs[k][1];
				nextp.dir = k;
				nextp.step = curp.step;
				//����ǰ���ʵ㷽������һ�㷽����ͬ���ж�Ϊ�յ㣬step++
				if (curp.dir != k)
				{
					nextp.step++;
				}
				//���յ����2��(��������������������·��)������ǰ��ѭ��
				if (nextp.step > 2)
				{
					continue;
				}
				//����ǰ��Ϊ���ʱ������ǰ��ѭ��
				//��Ϊ������������·����С�ڿɵ���·�������ʲ��ж���ǰ���Ƿ��������߹�����һ��bool visited[][]�������״̬�����и��ý���취��ӭ���ۡ�
				if (nextp.x == inp.x && nextp.y == inp.y)
				{
					continue;
				}
				//�߽���
				if ((nextp.x >= 0) && (nextp.x < sizeX) && (nextp.y >= 0) && (nextp.y < sizeY))
				{
					//���ǿյؼ�������ʶ���
					if (map[nextp.y][nextp.x] == 0)
					{
						q.push(nextp);
					}
					//������㷽����ͬ�����ж��ҵ���Ӧ�յ㷽�飬��¼���˳�ѭ��
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

	//������˳�򲢱����ڴ��������qClick��
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
					//��ÿһ����bfsչ��
					if (map[i][j] != 0) //0�ǿյ�
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
				cout << "������" << endl;
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
			Sleep(10); //Ҫ����ĳЩӦ�õķ�Ӧʱ��
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
	cout << "���س�����ʼ" << endl;
	while (1)
	{
		if (KEY_DOWN(VK_RETURN))
		{
			linkGameSolver linkGameSolver;
			linkGameSolver.getMap();
			//linkGameSolver.showMap();

			linkGameSolver.caculate();
			cout << "��ͼƥ�����" << endl;
			linkGameSolver.nice();

			system("cls");
			cout << "���س�����ʼ" << endl;
		}
	}
	return 0;
}
