
// Random_Pick
#include <algorithm>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <io.h>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <random>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;
struct Student;
/**************************
* 全局变量定义
*/
bool TEST = false;                             //测试模式，为真跳过所有动画
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //窗口句柄
random_device rd;                              //随机生成器
int selectRandNumber;                          //选取人数
int classesNumber;                             //班级数量
int classNum;                                  //当前的班级编号
int classesStudentsNumber;                     //班级学生数量
string *classesName, isSelectClass;
int *classesStudentsNumberArrary;
int winX;
//Student stu[150];

/**************************
*枚举，类，结构定义
*/

//特殊键位
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
//学生结构
struct Student
{
    int num;
    string id;
    string name;
} stu[150];

/**************************
* 函数部分
*/
//获取特定格式的文件名
// 该函数有两个参数，第一个为路径字符串(string类型，最好为绝对路径)；
// 第二个参数为文件夹与文件名称存储变量(vector类型,引用传递)。
// 第三个参数为文件后缀格式
void GetAllFormatFiles(string path, vector<string> &files, string format)
{
    //文件句柄
    long hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
                    //files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
                    GetAllFormatFiles(p.assign(path).append("\\").append(fileinfo.name), files, format);
                }
            }
            else
            {
                files.push_back(p.assign(fileinfo.name)); //将文件路径保存，也可以只保存文件名:    p.assign(path).append("\\").append(fileinfo.name)
            }
        } while (_findnext(hFile, &fileinfo) == 0);

        _findclose(hFile);
    }
}

//读取txt文件，获取班级名称，班级人数
void f()
{
    string filePath = "..\\Release\\className";
    vector<string> files;
    //读取所有格式为txt的文件
    string format = ".txt";
    GetAllFormatFiles(filePath, files, format);
    int size = files.size(); //读取到的班级数量(.txt后缀名称文件数量)
    int posS;                //.txt前面字符的数量,用于截取班级名称

    //classesNumber = size;
    classesNumber = size;
    classesName = new string[classesNumber];              //储存班级名称
    classesStudentsNumberArrary = new int[classesNumber]; //储存班级人数

    //
    for (int i = 0; i < size; i++)
    {
        //cout << files[i] << endl;//输出到屏幕
        posS = files[i].find(".txt");
        classesName[i] = files[i].substr(0, posS); //获取班级名称比如 15软工.txt，得到 15软工
        fstream fin5("..\\Release\\className\\" + files[i], ios::in);
        if (!fin5)
        {
            cerr << "can not open file" << endl;
        }
        char C;
        int lineCnt = 1; //计算班级人数
                         //读取班级人数，实际上读取换行数量，一个换行符==一个人
        while (fin5.get(C))
        {
            if (C == '\n')
                lineCnt++;
        }
        //cout << lineCnt << endl;
        classesStudentsNumberArrary[i] = lineCnt;
        fin5.close();
    }
}
//光标控制 第一个参数表示 是否隐藏光标
void hideCursor(bool b)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;   //光标厚度
    info.bVisible = b; //是否显示

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

//定位光标位置
void location(HANDLE hOut, int x, int y) //定位
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut, pos);
}

//居中定位光标位置
void locationCenter(HANDLE hOut, int strLength, int y) //定位
{
    COORD pos;
    pos.X = (winX - strLength) / 2;
    pos.Y = y;
    SetConsoleCursorPosition(hOut, pos);
}

//键盘输入
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
//以 t字/ms 输出字符串
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
void GetList()
{
    int number;
    string Sid, Sname;
    string str;
    str = "..\\Release\\className\\" + isSelectClass + ".txt";
    ifstream fin(str);
    //读取学生信息
    for (int i = 0; i < classesStudentsNumber; i++)
    {
        fin >> number >> Sid >> Sname;
        stu[i].num = number;
        stu[i].id = Sid;
        stu[i].name = Sname;
    }
    //int Round = rd() % 8 + 3;
    //随机打乱，洗牌
    int Round = rd() % 7777 + 7777; // Nice Seven
    int temp3 = 0;                  // 前后迭代交换
    while (Round--)
    {
        int temp1 = rd() % classesStudentsNumber;
        int temp2 = rand() % classesStudentsNumber;
        swap(stu[temp1], stu[temp2]);
        swap(stu[temp3], stu[temp3 + 1]);
        temp3++;
        temp3 %= classesStudentsNumber - 1;
    }
}

//void LuckyDraw(int i)
//{
//	GetList();
//	system("pause");
//	string temp = "mode con cols=" + to_string(80) + " lines=" + to_string(selectRandNumber * 2 + 17);
//	char const *size = temp.c_str();
//	system(size);
//
//	system("cls");
//	int *R = new int[i];
//	location(hOut, 27, 3);
//
//	string Rule = "数字滚动中，请按任意键选取";
//	prints(Rule, 0);
//
//	for (int k = 0; k < i; k++)
//	{
//		location(hOut, 17, 6 + k * 2);
//		cout << "第" << k + 1 << "位幸运儿是    号！";
//	}
//
//	while (1)
//	{
//		//纯动画效果
//		for (int k = 0; k < i; k++)
//		{
//			Sleep(3); //随机间隔，减少短时间内随机相似性
//
//			R[k] = rd() % classesStudentsNumber + 1;
//
//			for (int p = 0; p < k; p++)           //重复判断
//			{
//				while (R[k] == R[p])              //如果出现与前面相同的数字
//				{
//					p = -1;
//					Sleep(3);
//					R[k] = rd() % classesStudentsNumber + 1;          //重新随机一次
//				}
//			}
//		}
//
//		if (!_kbhit())
//		{
//			for (int k = 0; k < i; k++)
//			{
//				if (k < 9)
//				{
//					location(hOut, 31, 6 + k * 2);
//				}
//				else
//				{
//					location(hOut, 32, 6 + k * 2);
//				}
//				if (R[k] < 10)
//				{
//					cout << "0";      //抽到个位数字补0增加美观性
//				}
//				cout << R[k];
//			}
//		}
//		else        //打印最终抽取结果
//		{
//			for (int k = 0; k < i; k++)
//			{
//				if (k < 9)
//				{
//					location(hOut, 31, 6 + k * 2);
//				}
//				else
//				{
//					location(hOut, 32, 6 + k * 2);
//				}
//				if (R[k] < 10)
//				{
//					cout << "0";
//				}
//				cout << R[k];
//			}
//			break;
//		}
//	}
//
//	for (int k = 0; k < i; k++)         //打印号码对应的名单
//	{
//		string id, name;
//		//GetList();
//		location(hOut, 41, 6 + k * 2);
//		cout << "  " << id << "  " << name;
//	}
//}

void LuckyDraw()
{
    isSelectClass = classesName[classNum - 1]; //确定抽取班级
    GetList();                                 //打乱学生数组
    system("cls");

    location(hOut, 27, 3);

    string Rule = "数字滚动中，请按任意键选取";
    prints(Rule, 0);

    // 抽取
    for (int i = 1;; i++)
    {
        location(hOut, 17, 4 + i * 2);
        cout << "第" << i << "位幸运儿是    号！";
        //string temp = "mode con cols=" + to_string(80) + " lines=" + to_string(i * 2 + 17);
        //char const *size = temp.c_str();
        //system(size);
        while (1)
        {

            if (_kbhit()) // 敲击一下，出现一个信息
            {
                if (i < 10)
                {
                    location(hOut, 31, 4 + i * 2);
                }
                else
                {
                    location(hOut, 32, 4 + i * 2);
                }
                if (stu[i - 1].num < 10)
                {
                    cout << "0";
                }
                cout << stu[i - 1].num;
                location(hOut, 41, 4 + i * 2);
                cout << "  " << stu[i - 1].id << "  " << stu[i - 1].name;
                break;
            }

            else //随机动画效果
            {
                Sleep(15);
                int RanNum = rd() % classesStudentsNumber + 1;
                if (i < 10)
                {
                    location(hOut, 31, 4 + i * 2);
                }
                else
                {
                    location(hOut, 32, 4 + i * 2);
                }
                if (RanNum < 10)
                {
                    cout << "0"; //抽到个位数字补0增加美观性
                }
                //cout << RanNum;

                cout << stu[RanNum - 1].num;
                location(hOut, 41, 4 + i * 2);
                cout << "  " << stu[RanNum - 1].id << "  " << stu[RanNum - 1].name;
            }
        }

        char TEMP = _getch();
        char Again = _getch();
        if (Again == 27)
        {
            break;
        }
    }
}

//选择班级 根据班级数量选择班级，6个班级编号1-6,全局变量classNum为当前选择班级
void selectClass()
{
    const int posX = 33, posY = 5;
    int sel = 1;
    system("cls");
    location(hOut, posX - 15, 3);
    //cout << "请选择班级：";

    for (int i = 0; i < classesNumber; i++)
    {
        location(hOut, posX, posY + (i + 1) * 2 - 1);
        prints(classesName[i], 25);
    }

    location(hOut, posX - 3, posY + (sel + 1) * 2 - 1);
    //cout << "  ";
    prints("  ", 25);
    location(hOut, posX - 3, posY + sel * 2 - 1);
    //cout << ">>";
    prints(">>", 35);

    while (true)
    {
        int dir = getKeyboard();
        if (dir == UP)
        {
            sel = (sel <= 1 ? 1 : sel - 1);
            location(hOut, posX - 3, posY + (sel + 1) * 2 - 1);
            //cout << "  ";
            prints("  ", 25);
            location(hOut, posX - 3, posY + sel * 2 - 1);
            //cout << ">>";
            prints(">>", 25);
        }
        else if (dir == DOWN)
        {
            sel = (sel >= classesNumber ? classesNumber : sel + 1);
            location(hOut, posX - 3, posY + (sel - 1) * 2 - 1);
            //cout << "  ";
            prints("  ", 25);
            location(hOut, posX - 3, posY + sel * 2 - 1);
            //cout << ">>";
            prints(">>", 25);
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
void exportLaug(int n)
{
    string S;
    if (n == 1)
    {
        location(hOut, 23, 8);
        S = "输入数字超过班级人数，请重新输入！";
    }
    else
    {
        location(hOut, 31, 8);
        S = "输入数字要大于0！";
    }
    cout << S << endl;
    Sleep(1024);
    location(hOut, 27, 6);
    system("cls");         //清屏
    location(hOut, 27, 4); //字体显示位置
    cout << "您选择的班级是" << classesName[classNum - 1];
    location(hOut, 27, 6); //字体显示位置
    cout << "请输入要抽取的人数: ";
    cout << "(" << classesStudentsNumberArrary[classNum - 1] << "人) ";
}
void selectRandNum()
{
    system("cls");
    bool is_exceeding = false; //判断是否超过班级人数的布尔变量
    location(hOut, 27, 4);     //字体显示位置
                               //isSelectClass = classesName[classNum - 1];
    cout << "您选择的班级是" << classesName[classNum - 1];
    location(hOut, 27, 6); //字体显示位置
    hideCursor(true);      //显示光标
    cout << "请输入要抽取的人数: ";
    cout << "（" << classesStudentsNumberArrary[classNum - 1] << "人）";
    while (!is_exceeding) //
    {
        cin >> selectRandNumber;
        if (selectRandNumber > classesStudentsNumberArrary[classNum - 1])
        {
            exportLaug(1);
        }
        else if (selectRandNumber <= 0)
        {
            exportLaug(0);
        }
        else
        {
            is_exceeding = true;
        }
    }
    hideCursor(false);
}

void START()
{
    //开局动画效果
    //location(hOut, 27, 10);
    //cout << "程序启动中，请稍候..." << i;
    string str = "程序启动中，请稍候...";
    locationCenter(hOut, str.length(), 10);
    cout << str;
    for (int i = 0; i <= 100; i++)
    {

        str = i;
        locationCenter(hOut, str.length(), 12);

        cout << i << "%";
        Sleep(22);
    }
    Sleep(150);
    system("cls");

    string hello1 = "又到了一节课紧张而又刺激的“抽奖”环节！！";
    locationCenter(hOut, hello1.length(), 8);
    prints(hello1, 20);

    string hello2 = "今天会抽中哪几位幸运儿呢？？";
    locationCenter(hOut, hello2.length(), 10);
    prints(hello2, 20);
    Sleep(500);

    string hello3 = "按任意键进入“抽奖”界面....";
    locationCenter(hOut, hello3.length(), 12);
    prints(hello3, 23);
    char flag = _getch();
    system("cls");
}
void Begin()
{
    //测试专用省时间判断23333
    if (!TEST)
    {
        START();
    }

    //选择班级
    selectClass();

    //抽取人数
    //selectRandNum();

    //根据选取人数开始抽奖
    LuckyDraw();

    location(hOut, 11, 7 + selectRandNumber * 2);

    if (!TEST)
    {
        //获取抽取完的位置打印版权
        location(hOut, 11, 9 + selectRandNumber * 2);
        string end = "感谢你的使用，如有疑问欢迎发送邮件到664224027@qq.com！";
        prints(end, 27);
        location(hOut, 22, 11 + selectRandNumber * 2);
        string brand = "Power By CST17017 涂学彬, Maoxian";
        prints(brand, 27);
        location(hOut, 30, 13 + selectRandNumber * 2);
        system("pause");
    }
}

int main()
{
    f();
    winX = 80;
    system("mode con cols=80 lines=25"); //窗口大小
    srand((int)time(0));                 //随机种子
    hideCursor(false);                   //隐藏光标
    Begin();                             //开始函数
    return 0;
}