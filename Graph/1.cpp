#include <iostream>
#include <queue>
#include <windows.h>
using namespace std;

int inputNumber(string info, string errorInfo, int range)
{
    string str;
    while (true)
    {
        if (info != "")
        {
            cout << info;
        }
        bool flag = true; //����Ƿ�����
        cin >> str;
        for (unsigned int i = 0; i < str.length(); i++)
        {
            if (str[i] < '0' || str[i] > '9')
            {
                flag = false;
                break;
            }
        }
        if (flag == true)
        {
            int num = atoi(str.c_str());
            if (num <= range)
            {
                return num;
            }
            else
            {
                cout << errorInfo << endl;
                continue;
            }
        }
        else
        {
            cout << errorInfo << endl;
            continue;
        }
    }
}

template <class DataType>
class Graph
{
  private:
    static const int MAXSIZE = 20;
    int vertexNum, arcNum;

    DataType vertex[MAXSIZE];
    bool arc[MAXSIZE][MAXSIZE];
    bool visited[MAXSIZE];

    void DFSTraverse(int k);
    void cleanVisited();

  public:
    Graph();
    //kΪ��������ʼ�������
    void DFS(int k);
    void BFS(int k);
    void displayArc();
};
template <class DataType>
Graph<DataType>::Graph()
{
    int n, e;

    n = inputNumber("����������ͼ�еĶ�����(������20)��", "�������������...", MAXSIZE);

    int max_e = (n * (n - 1)) / 2;
    e = inputNumber("����������ͼ�еı���(������" + to_string(max_e) + ")��", "�����������...", max_e);

    this->vertexNum = n;
    this->arcNum = e;

    //�����������Ϣ...(��)
    //cout<<"���붥����Ϣ:"<<endl;
    for (int i = 0; i < vertexNum; i++)
    {
        //cout << "v" << i << " :";
        //cin >> vertex[i];
        visited[i] = 0;
    }

    cout << "����ͼ�еĶ������Ϊ��";
    for (int i = 0; i < vertexNum; i++)
    {
        cout << "v" << i << " ";
        //cout << vertex[i] << "  ";
    }
    cout << endl;

    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            arc[i][j] = 0;
        }
    }

    cout << "����������ͼ�ı�:" << endl;
    for (int i = 0; i < arcNum; i++)
    {
        int a, b;
        cout << "�����" << i + 1 << "���ߵ����˶��㣺" << endl;
        while (true)
        {
            a = inputNumber(("�����" + to_string(i + 1) + "���ߵĵ�һ�����㣺"), "�������...", vertexNum - 1);
            b = inputNumber(("�����" + to_string(i + 1) + "���ߵĵڶ������㣺"), "�������...", vertexNum - 1);
            if (arc[a][b] == 1 && arc[b][a] == 1)
            {
                cout << "�ñ�(v" << a << ",v" << b << ")�Ѵ���,����������..." << endl;
            }
            else
            {
                break;
            }
        }
        arc[a][b] = 1;
        arc[b][a] = 1;
    }

    displayArc();
}

template <class DataType>
void Graph<DataType>::cleanVisited()
{
    for (int i = 0; i < vertexNum; i++)
    {
        visited[i] = 0;
    }
}
template <class DataType>
void Graph<DataType>::displayArc()
{
    cout << "����ͼ���ڽӾ���:" << endl;
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            cout << arc[i][j] << " ";
        }
        cout << endl;
    }
}
template <class DataType>
void Graph<DataType>::DFS(int k)
{
    cleanVisited();
    cout << "�������������";
    DFSTraverse(0);
    cout << endl;
    cleanVisited();
}
template <class DataType>
void Graph<DataType>::DFSTraverse(int k)
{
    cout << "v" << k << " ";
    //cout << vertex[k] << "  ";
    visited[k] = 1;
    for (int i = 0; i < vertexNum; i++)
    {
        if (arc[k][i] == 1 && visited[i] == 0)
        {
            DFSTraverse(i);
        }
    }
}
template <class DataType>
void Graph<DataType>::BFS(int k)
{
    queue<int> q;
    cleanVisited();
    q.push(k);
    visited[k] = 1;
    cout << "�������������";

    cout << "v" << k << " ";
    //cout << vertex[k] << "  ";
    while (!q.empty())
    {
        k = q.front();
        q.pop();
        for (int i = 0; i < vertexNum; i++)
        {
            if (arc[k][i] == 1 && visited[i] == 0)
            {
                q.push(i);
                visited[i] = 1;
                cout << "v" << i << " ";
                //cout << vertex[k] << "  ";
            }
        }
    }
    cout << endl;
}
int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
    Graph<int> g;
    g.DFS(0);
    g.BFS(0);
    return 0;
}