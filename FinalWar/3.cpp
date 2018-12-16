#include <iostream>
#include <queue>
#include <windows.h>
using namespace std;

struct ArcVertexVal
{
    int vertex[2];
    int value;
};
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

int inputVertex(string info, string errorInfo, int range)
{
    string str;
    while (true)
    {
        if (info != "")
        {
            cout << info;
        }
        bool flag = true; //标记
        cin >> str;
        if (str.length() > 1)
        {
            flag = false;
        }
        char ch = str[0];
        if (flag == true)
        {
            if (ch >= 'a' && ch <= 'a' + range)
            {
                return ch - 'a';
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

class Graph
{
  private:
    static const int MAXSIZE = 20;
    int vertexNum, arcNum;

    char vertex[MAXSIZE];
    int arc[MAXSIZE][MAXSIZE];
    bool visited[MAXSIZE];

    void DFSTraverse(int k);
    void cleanVisited();

  public:
    Graph();
    //k为遍历的起始顶点序号
    void DFS(int k);
    void BFS(int k);
    void Prim(int k);
    void displayArc();
};

Graph::Graph()
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
        vertex[i] = (char)('a' + i);
    }

    cout << "无向图中的顶点为：";
    for (int i = 0; i < vertexNum; i++)
    {
        cout << vertex[i] << " ";
        //cout << vertex[i] << "  ";
    }
    cout << endl;

    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            arc[i][j] = INT_MAX;
        }
    }

    cout << "请输入无向图的边:" << endl;
    for (int i = 0; i < arcNum; i++)
    {
        int a, b;
        int value;
        cout << "输入第" << i + 1 << "条边的两端顶点：" << endl;
        while (true)
        {
            a = inputVertex(("输入第" + to_string(i + 1) + "条边的第一个顶点："), "输入错误...", vertexNum - 1);
            b = inputVertex(("输入第" + to_string(i + 1) + "条边的第二个顶点："), "输入错误...", vertexNum - 1);
            value = inputNumber(("输入第" + to_string(i + 1) + "条边的权重："), "输入错误...", INT_MAX);
            if (arc[a][b] != INT_MAX && arc[b][a] != INT_MAX)
            {
                cout << "该边(v" << a << ",v" << b << ")已存在,请重新输入..." << endl;
            }
            else
            {
                break;
            }
        }
        cout << endl;
        arc[a][b] = value;
        arc[b][a] = value;
    }

    displayArc();
}

void Graph::cleanVisited()
{
    for (int i = 0; i < vertexNum; i++)
    {
        visited[i] = 0;
    }
}

void Graph::displayArc()
{
    cout << "无向图的邻接矩阵:" << endl;
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            if (arc[i][j] == INT_MAX)
            {
                cout << "∞";
            }
            else
            {
                cout << arc[i][j];
            }
            cout << "\t";
        }
        cout << endl;
    }
}

void Graph::DFS(int k)
{
    cleanVisited();
    cout << "深度优先搜索：";
    DFSTraverse(0);
    cout << endl;
    cleanVisited();
}

void Graph::DFSTraverse(int k)
{
    cout << vertex[k] << " ";
    //cout << vertex[k] << "  ";
    visited[k] = 1;
    for (int i = 0; i < vertexNum; i++)
    {
        if (arc[k][i] != INT_MAX && visited[i] == 0)
        {
            DFSTraverse(i);
        }
    }
}

void Graph::BFS(int k)
{
    queue<int> q;
    cleanVisited();
    q.push(k);
    visited[k] = 1;
    cout << "广度优先搜索：";

    cout << vertex[k] << " ";
    //cout << vertex[k] << "  ";
    while (!q.empty())
    {
        k = q.front();
        q.pop();
        for (int i = 0; i < vertexNum; i++)
        {
            if (arc[k][i] != INT_MAX && visited[i] == false)
            {
                q.push(i);
                visited[i] = 1;
                cout << vertex[i] << " ";
                //cout << vertex[k] << "  ";
            }
        }
    }
    cout << endl;
}
void Graph::Prim(int k)
{
    cleanVisited();
    ArcVertexVal dist[MAXSIZE];
    ArcVertexVal shortEdge[MAXSIZE];
    for (int i = 0; i < vertexNum;i++)
    {
        shortEdge[i].value = arc[k][i];
        shortEdge[i].vertex[0] = k;
    }
    shortEdge[k].value = 0;
    int index=-1;
    int m = 0;
    for (int i = 0; i < vertexNum-1;i++)
    {
        int temp = INT_MAX;
        for (int j = 0; j < vertexNum;j++)
        {
            if(temp>shortEdge[j].value && visited[j]==false)
            {
                index = j;
                temp = shortEdge[j].value;
            }
        }
        visited[index] = true;
        cout << "(" << (char)('a'+dist[i].vertex[0]) << "," << (char)('a'+dist[i].vertex[1]) << ") value: " << dist[i].value << endl;
    dist[m].vertex[0] = index;
    dist[m].vertex[1] = shortEdge[index].vertex[0];
    dist[m++].value = shortEdge[index].value;

    shortEdge[index].value = 0;
    for (int j = 0; j < vertexNum-1; j++)
    {
        if (arc[index][j] < shortEdge[j].value)
        {
            shortEdge[j].value = arc[index][j];
            shortEdge[j].vertex[0] = index;
        }
        }
    }
    int sum = 0;
    for (int i = 0; i < m;i++)
    {
        sum += dist[i].value;
        cout << "(" << vertex[dist[i].vertex[0]] << "," << vertex[dist[i].vertex[1]] << ") value: " << dist[i].value << endl;
    }
    cout << sum << endl;
}

int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
    Graph g;
    g.DFS(0);
    g.BFS(0);
    g.Prim(0);
    return 0;
}