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
        bool flag = true; //标记是否纯数字
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
    //k为遍历的起始顶点序号
    void DFS(int k);
    void BFS(int k);
    void displayArc();
};
template <class DataType>
Graph<DataType>::Graph()
{
    int n, e;

    n = inputNumber("请输入无向图中的顶点数(不大于20)：", "顶点数输入错误...", MAXSIZE);

    int max_e = (n * (n - 1)) / 2;
    e = inputNumber("请输入无向图中的边数(不大于" + to_string(max_e) + ")：", "边数输入错误...", max_e);

    this->vertexNum = n;
    this->arcNum = e;

    //输入各顶点信息...(略)
    //cout<<"输入顶点信息:"<<endl;
    for (int i = 0; i < vertexNum; i++)
    {
        //cout << "v" << i << " :";
        //cin >> vertex[i];
        visited[i] = 0;
    }

    cout << "无向图中的顶点序号为：";
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

    cout << "请输入无向图的边:" << endl;
    for (int i = 0; i < arcNum; i++)
    {
        int a, b;
        cout << "输入第" << i + 1 << "条边的两端顶点：" << endl;
        while (true)
        {
            a = inputNumber(("输入第" + to_string(i + 1) + "条边的第一个顶点："), "输入错误...", vertexNum - 1);
            b = inputNumber(("输入第" + to_string(i + 1) + "条边的第二个顶点："), "输入错误...", vertexNum - 1);
            if (arc[a][b] == 1 && arc[b][a] == 1)
            {
                cout << "该边(v" << a << ",v" << b << ")已存在,请重新输入..." << endl;
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
    cout << "无向图的邻接矩阵:" << endl;
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
    cout << "深度优先搜索：";
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
    cout << "广度优先搜索：";

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