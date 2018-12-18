#include <algorithm>
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
    static const int MAXSIZE = 100;
    int vertexNum, arcNum;

    char vertex[MAXSIZE];
    int arc[MAXSIZE][MAXSIZE];
    bool visited[MAXSIZE];

    void cleanVisited();

  public:
    Graph();
    //k为遍历的起始顶点序号
    void Prim(int k);
    void Kruskal();
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

    for (int i = 0; i < vertexNum; i++)
    {
        vertex[i] = (char)('a' + i);
    }

    cout << "无向图中的顶点为：";
    for (int i = 0; i < vertexNum; i++)
    {
        cout << vertex[i] << " ";
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
                cout << "该边(i" << a << ",i" << b << ")已存在,请重新输入..." << endl;
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

void Graph::Prim(int k)
{
    cleanVisited();
    ArcVertexVal ans[MAXSIZE];
    // 每个未加入树中的顶点到树的最小开销
    int cost[MAXSIZE];
    // 与最小开销对应的未加入树中的顶点编号
    int pathCost[MAXSIZE];

    int min = INT_MAX;
    int minIndex = k;

    // 起点
    visited[k] = true;
    for (int i = 0; i < vertexNum; i++)
    {
        cost[i] = arc[k][i];
        pathCost[i] = k;
    }

    for (int i = 0; i < vertexNum - 1; i++)
    {
        min = INT_MAX;
        for (int j = 0; j < vertexNum; j++)
        {
            if (!visited[j] && cost[j] < min)
            {
                minIndex = j;
                min = cost[j];
            }
        }

        ans[i].vertex[0] = pathCost[minIndex];
        ans[i].vertex[1] = minIndex;
        ans[i].value = min;

        visited[minIndex] = true;

        //只需要更新与新加入的点相连的开销
        for (int j = 0; j < vertexNum; j++)
        {
            if (!visited[j] && arc[minIndex][j] < cost[j])
            {
                cost[j] = arc[minIndex][j];
                pathCost[j] = minIndex;
            }
        }
    }

    int sum = 0;
    cout << "Prim:" << endl;
    for (int i = 0; i < vertexNum - 1; i++)
    {
        cout << "( " << (char)('a' + ans[i].vertex[0]) << " , " << (char)('a' + ans[i].vertex[1]) << " ) = " << ans[i].value << endl;
        sum += ans[i].value;
    }
    cout << "sum : " << sum << endl;
}

bool cmp(ArcVertexVal a, ArcVertexVal b)
{
    return a.value < b.value;
}
//并查集求根
int getRoot(int a[], int x)
{
    while (a[x] != x)
    {
        x = a[x];
    }
    return x;
}

void Graph::Kruskal()
{
    //并查集
    int v[MAXSIZE];
    ArcVertexVal KruskalArc[MAXSIZE];
    ArcVertexVal ans[MAXSIZE];
    int m = 0;

    for (int i = 0; i < vertexNum; i++)
    {
        //初始化并查集
        v[i] = i;
        //遍历上三角
        for (int j = i + 1; j < vertexNum; j++)
        {
            //将图转为边结构存入 KruskalArc
            if (arc[i][j] != INT_MAX)
            {
                KruskalArc[m].vertex[0] = i;
                KruskalArc[m].vertex[1] = j;
                KruskalArc[m++].value = arc[i][j];
            }
        }
    }
    sort(KruskalArc, KruskalArc + m, cmp);
    m = 0;
    //将最小的非树点依次加入mst
    for (int i = 0; i < arcNum; i++)
    {
        int a, b;
        a = getRoot(v, KruskalArc[i].vertex[0]);
        b = getRoot(v, KruskalArc[i].vertex[1]);
        //并查集判断集合情况
        if (a != b)
        {
            v[a] = b;
            ans[m].vertex[0] = KruskalArc[i].vertex[0];
            ans[m].vertex[1] = KruskalArc[i].vertex[1];
            ans[m++].value = KruskalArc[i].value;
        }
    }
    int sum = 0;
    cout << "Kruskal:" << endl;
    for (int i = 0; i < m; i++)
    {
        cout << "( " << (char)('a' + ans[i].vertex[0]) << " , " << (char)('a' + ans[i].vertex[1]) << " ) = " << ans[i].value << endl;
        sum += ans[i].value;
    }
    cout << "sum : " << sum << endl;
}
int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
    Graph g;
    cout << endl;
    g.Prim(0);
    cout << endl;
    g.Kruskal();
    return 0;
}