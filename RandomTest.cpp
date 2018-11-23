
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
* ȫ�ֱ�������
*/
bool TEST = false;                             //����ģʽ��Ϊ���������ж���
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //���ھ��
random_device rd;                              //���������
int selectRandNumber;                          //ѡȡ����
int classesNumber;                             //�༶����
int classNum;                                  //��ǰ�İ༶���
int classesStudentsNumber;                     //�༶ѧ������
string *classesName, isSelectClass;
int *classesStudentsNumberArrary;
int winX;
//Student stu[150];

/**************************
*ö�٣��࣬�ṹ����
*/

//�����λ
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
//ѧ���ṹ
struct Student
{
    int num;
    string id;
    string name;
} stu[150];

/**************************
* ��������
*/
//��ȡ�ض���ʽ���ļ���
// �ú�����������������һ��Ϊ·���ַ���(string���ͣ����Ϊ����·��)��
// �ڶ�������Ϊ�ļ������ļ����ƴ洢����(vector����,���ô���)��
// ����������Ϊ�ļ���׺��ʽ
void GetAllFormatFiles(string path, vector<string> &files, string format)
{
    //�ļ����
    long hFile = 0;
    //�ļ���Ϣ
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
                files.push_back(p.assign(fileinfo.name)); //���ļ�·�����棬Ҳ����ֻ�����ļ���:    p.assign(path).append("\\").append(fileinfo.name)
            }
        } while (_findnext(hFile, &fileinfo) == 0);

        _findclose(hFile);
    }
}

//��ȡtxt�ļ�����ȡ�༶���ƣ��༶����
void f()
{
    string filePath = "..\\Release\\className";
    vector<string> files;
    //��ȡ���и�ʽΪtxt���ļ�
    string format = ".txt";
    GetAllFormatFiles(filePath, files, format);
    int size = files.size(); //��ȡ���İ༶����(.txt��׺�����ļ�����)
    int posS;                //.txtǰ���ַ�������,���ڽ�ȡ�༶����

    //classesNumber = size;
    classesNumber = size;
    classesName = new string[classesNumber];              //����༶����
    classesStudentsNumberArrary = new int[classesNumber]; //����༶����

    //
    for (int i = 0; i < size; i++)
    {
        //cout << files[i] << endl;//�������Ļ
        posS = files[i].find(".txt");
        classesName[i] = files[i].substr(0, posS); //��ȡ�༶���Ʊ��� 15��.txt���õ� 15��
        fstream fin5("..\\Release\\className\\" + files[i], ios::in);
        if (!fin5)
        {
            cerr << "can not open file" << endl;
        }
        char C;
        int lineCnt = 1; //����༶����
                         //��ȡ�༶������ʵ���϶�ȡ����������һ�����з�==һ����
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
//������ ��һ��������ʾ �Ƿ����ع��
void hideCursor(bool b)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;   //�����
    info.bVisible = b; //�Ƿ���ʾ

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

//��λ���λ��
void location(HANDLE hOut, int x, int y) //��λ
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut, pos);
}

//���ж�λ���λ��
void locationCenter(HANDLE hOut, int strLength, int y) //��λ
{
    COORD pos;
    pos.X = (winX - strLength) / 2;
    pos.Y = y;
    SetConsoleCursorPosition(hOut, pos);
}

//��������
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
//�� t��/ms ����ַ���
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
void GetList()
{
    int number;
    string Sid, Sname;
    string str;
    str = "..\\Release\\className\\" + isSelectClass + ".txt";
    ifstream fin(str);
    //��ȡѧ����Ϣ
    for (int i = 0; i < classesStudentsNumber; i++)
    {
        fin >> number >> Sid >> Sname;
        stu[i].num = number;
        stu[i].id = Sid;
        stu[i].name = Sname;
    }
    //int Round = rd() % 8 + 3;
    //������ң�ϴ��
    int Round = rd() % 7777 + 7777; // Nice Seven
    int temp3 = 0;                  // ǰ���������
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
//	string Rule = "���ֹ����У��밴�����ѡȡ";
//	prints(Rule, 0);
//
//	for (int k = 0; k < i; k++)
//	{
//		location(hOut, 17, 6 + k * 2);
//		cout << "��" << k + 1 << "λ���˶���    �ţ�";
//	}
//
//	while (1)
//	{
//		//������Ч��
//		for (int k = 0; k < i; k++)
//		{
//			Sleep(3); //�����������ٶ�ʱ�������������
//
//			R[k] = rd() % classesStudentsNumber + 1;
//
//			for (int p = 0; p < k; p++)           //�ظ��ж�
//			{
//				while (R[k] == R[p])              //���������ǰ����ͬ������
//				{
//					p = -1;
//					Sleep(3);
//					R[k] = rd() % classesStudentsNumber + 1;          //�������һ��
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
//					cout << "0";      //�鵽��λ���ֲ�0����������
//				}
//				cout << R[k];
//			}
//		}
//		else        //��ӡ���ճ�ȡ���
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
//	for (int k = 0; k < i; k++)         //��ӡ�����Ӧ������
//	{
//		string id, name;
//		//GetList();
//		location(hOut, 41, 6 + k * 2);
//		cout << "  " << id << "  " << name;
//	}
//}

void LuckyDraw()
{
    isSelectClass = classesName[classNum - 1]; //ȷ����ȡ�༶
    GetList();                                 //����ѧ������
    system("cls");

    location(hOut, 27, 3);

    string Rule = "���ֹ����У��밴�����ѡȡ";
    prints(Rule, 0);

    // ��ȡ
    for (int i = 1;; i++)
    {
        location(hOut, 17, 4 + i * 2);
        cout << "��" << i << "λ���˶���    �ţ�";
        //string temp = "mode con cols=" + to_string(80) + " lines=" + to_string(i * 2 + 17);
        //char const *size = temp.c_str();
        //system(size);
        while (1)
        {

            if (_kbhit()) // �û�һ�£�����һ����Ϣ
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

            else //�������Ч��
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
                    cout << "0"; //�鵽��λ���ֲ�0����������
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

//ѡ��༶ ���ݰ༶����ѡ��༶��6���༶���1-6,ȫ�ֱ���classNumΪ��ǰѡ��༶
void selectClass()
{
    const int posX = 33, posY = 5;
    int sel = 1;
    system("cls");
    location(hOut, posX - 15, 3);
    //cout << "��ѡ��༶��";

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
        S = "�������ֳ����༶���������������룡";
    }
    else
    {
        location(hOut, 31, 8);
        S = "��������Ҫ����0��";
    }
    cout << S << endl;
    Sleep(1024);
    location(hOut, 27, 6);
    system("cls");         //����
    location(hOut, 27, 4); //������ʾλ��
    cout << "��ѡ��İ༶��" << classesName[classNum - 1];
    location(hOut, 27, 6); //������ʾλ��
    cout << "������Ҫ��ȡ������: ";
    cout << "(" << classesStudentsNumberArrary[classNum - 1] << "��) ";
}
void selectRandNum()
{
    system("cls");
    bool is_exceeding = false; //�ж��Ƿ񳬹��༶�����Ĳ�������
    location(hOut, 27, 4);     //������ʾλ��
                               //isSelectClass = classesName[classNum - 1];
    cout << "��ѡ��İ༶��" << classesName[classNum - 1];
    location(hOut, 27, 6); //������ʾλ��
    hideCursor(true);      //��ʾ���
    cout << "������Ҫ��ȡ������: ";
    cout << "��" << classesStudentsNumberArrary[classNum - 1] << "�ˣ�";
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
    //���ֶ���Ч��
    //location(hOut, 27, 10);
    //cout << "���������У����Ժ�..." << i;
    string str = "���������У����Ժ�...";
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

    string hello1 = "�ֵ���һ�ڿν��Ŷ��ִ̼��ġ��齱�����ڣ���";
    locationCenter(hOut, hello1.length(), 8);
    prints(hello1, 20);

    string hello2 = "���������ļ�λ���˶��أ���";
    locationCenter(hOut, hello2.length(), 10);
    prints(hello2, 20);
    Sleep(500);

    string hello3 = "����������롰�齱������....";
    locationCenter(hOut, hello3.length(), 12);
    prints(hello3, 23);
    char flag = _getch();
    system("cls");
}
void Begin()
{
    //����ר��ʡʱ���ж�23333
    if (!TEST)
    {
        START();
    }

    //ѡ��༶
    selectClass();

    //��ȡ����
    //selectRandNum();

    //����ѡȡ������ʼ�齱
    LuckyDraw();

    location(hOut, 11, 7 + selectRandNumber * 2);

    if (!TEST)
    {
        //��ȡ��ȡ���λ�ô�ӡ��Ȩ
        location(hOut, 11, 9 + selectRandNumber * 2);
        string end = "��л���ʹ�ã��������ʻ�ӭ�����ʼ���664224027@qq.com��";
        prints(end, 27);
        location(hOut, 22, 11 + selectRandNumber * 2);
        string brand = "Power By CST17017 Ϳѧ��, Maoxian";
        prints(brand, 27);
        location(hOut, 30, 13 + selectRandNumber * 2);
        system("pause");
    }
}

int main()
{
    f();
    winX = 80;
    system("mode con cols=80 lines=25"); //���ڴ�С
    srand((int)time(0));                 //�������
    hideCursor(false);                   //���ع��
    Begin();                             //��ʼ����
    return 0;
}