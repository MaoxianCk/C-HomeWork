#include <iostream>
#include <queue>
#include <stack>
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

struct ArcVertexVal
{
    int vertex[2];
    int value;
};

class Graph
{
  private:
    static const int MAXSIZE = 20;
    int vertexNum, arcNum;

    int vertex[MAXSIZE];
    int arc[MAXSIZE][MAXSIZE];
    bool visited[MAXSIZE];
    ArcVertexVal arcs[MAXSIZE * (MAXSIZE - 1) / 2];

    void DFSTraverse(int k);
    void dfsprint(string ans,ArcVertexVal e[], int root);
    void cleanVisited();

  public:
    Graph();
    bool topSort();
    //k为遍历的起始顶点序号
    void DFS(int k);
    void BFS(int k);
    void criticalPath();
    void displayArc();
};

Graph::Graph()
{
    int n, e;

    n = inputNumber("请输入有向图中的顶点数(不大于20)：", "顶点数输入错误...", MAXSIZE);

    int max_e = n * (n - 1);
    e = inputNumber("请输入有向图中的边数(不大于" + to_string(max_e) + ")：", "边数输入错误...", max_e);

    this->vertexNum = n;
    this->arcNum = e;
    memset(vertex, 0, sizeof(vertex));
    //输入各顶点信息...(略)
    //cout<<"输入顶点信息:"<<endl;
    for (int i = 0; i < vertexNum; i++)
    {
        //cout << "v" << i << " :";
        //cin >> vertex[i];
        vertex[i] = i + 1;
    }

    cout << "有向图中的顶点序号为：";
    for (int i = 0; i < vertexNum; i++)
    {
        cout << "v" << vertex[i] << " ";
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

    cout << "请输入有向图的边:" << endl;
    int m = 0;
    for (int i = 0; i < arcNum; i++)
    {
        int a, b;
        int value;
        cout << "输入第" << i + 1 << "条边的两端顶点：" << endl;
        while (true)
        {
            a = inputNumber(("输入第" + to_string(i + 1) + "条边的第一个顶点："), "输入错误...", vertexNum) - 1;
            b = inputNumber(("输入第" + to_string(i + 1) + "条边的第二个顶点："), "输入错误...", vertexNum) - 1;
            value = inputNumber(("输入第" + to_string(i + 1) + "条边的权重："), "输入错误...", INT_MAX);
            if (arc[a][b] != INT_MAX)
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
        arcs[m].vertex[0] = a;
        arcs[m].vertex[1] = b;
        arcs[m++].value = value;
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
    cout << "有向图的邻接矩阵:" << endl;
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
    cout << "v" << vertex[k] << " ";
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

    cout << "v" << vertex[k] << " ";
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
                cout << "v" << vertex[i] << " ";
                //cout << vertex[k] << "  ";
            }
        }
    }
    cout << endl;
}
bool Graph::topSort()
{
    stack<int> s;
    int vertexIn[MAXSIZE] = {0};
    for (int i = 0; i < arcNum; i++)
    {
        vertexIn[arcs[i].vertex[1]]++;
    }
    for (int i = vertexNum - 1; i >= 0; i--)
    {
        if (vertexIn[i] == 0)
        {
            s.push(i);
        }
    }
    int cnt = 0; //circle
    while (!s.empty())
    {
        int v = s.top();
        s.pop();
        cout << " v" << vertex[v];
        cnt++;
        for (int i = vertexNum - 1; i >= 0; i--)
        {
            if (arc[v][i] != INT_MAX)
            {
                vertexIn[i]--;
                if (vertexIn[i] == 0)
                {
                    s.push(i);
                }
            }
        }
    }
    return (cnt == vertexNum ? true : false);
}
void Graph::criticalPath()
{
    if (!topSort())
    {
        cout << "该图有环无法计算关键路径！" << endl;
        return;
    }

    //最早发生时间
    int ve[MAXSIZE] = {0};
    //最晚发生时间
    int vl[MAXSIZE];
    //最早开始时间
    int ee[MAXSIZE * (MAXSIZE - 1) / 2];
    //最晚开始时间
    int el[MAXSIZE * (MAXSIZE - 1) / 2];

    ve[0] = 0;
    for (int i = 0; i < vertexNum; i++)
    {
        int max = 0;
        for (int j = 0; j < vertexNum; j++)
        {
            if (arc[j][i] != INT_MAX && arc[j][i] + ve[j] > max)
            {
                max = arc[j][i] + ve[j];
                ve[i] = max;
            }
        }
    }
    vl[vertexNum - 1] = ve[vertexNum - 1];
    for (int i = vertexNum - 1; i >= 0; i--)
    {
        int min = INT_MAX;
        for (int j = vertexNum - 1; j >= 0; j--)
        {

            if (arc[i][j] != INT_MAX && vl[j] - arc[i][j] < min)
            {
                min = vl[j] - arc[i][j];
                vl[i] = min;
            }
        }
    }

    for (int i = 0; i < arcNum; i++)
    {
        ee[i] = ve[arcs[i].vertex[0]];
        el[i] = vl[arcs[i].vertex[1]] - arcs[i].value;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);

    for (int i = 0; i < vertexNum; i++)
    {
        cout << "\tv" << i + 1;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);

    cout << endl;
    cout << "ve:\t";
    for (int i = 0; i < vertexNum; i++)
    {
        cout << ve[i] << "\t";
    }
    cout << endl;
    cout << "vl:\t";
    for (int i = 0; i < vertexNum; i++)
    {
        cout << vl[i] << "\t";
    }
    cout << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);

    for (int i = 0; i < arcNum; i++)
    {
        cout << "\ta" << i + 1;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);

    cout << endl;
    cout << "ee:\t";
    for (int i = 0; i < arcNum; i++)
    {
        cout << ee[i] << "\t";
    }
    cout << endl;
    cout << "el:\t";
    for (int i = 0; i < arcNum; i++)
    {
        cout << el[i] << "\t";
    }

    cout << endl;
    cout << "关键路径:";
    string ans[MAXSIZE];
    for (int i = 0; i < MAXSIZE; i++)
    {
        ans[i] = "";
    }
    ArcVertexVal e[MAXSIZE * (MAXSIZE - 1) / 2];
    int m = 0;
    for (int i = 0; i < arcNum; i++)
    {
        if (el[i] - ee[i] == 0)
        {
            e[m].vertex[0] = arcs[i].vertex[0];
            e[m].vertex[1] = arcs[i].vertex[1];
            e[m++].value = arcs[i].value;
            cout << e[i].vertex[0] << "  " << e[i].vertex[1] << endl;
        }
    }
    //dfsprint(("v" + to_string(e[0].vertex[0])), e, e[0].vertex[0]);
}
void Graph::dfsprint(string ans, ArcVertexVal e[], int root)
{
    bool flag = false;
    for (int i = 0; i < arcNum; i++)
    {
        if (e[i].vertex[0] == root)
        {
            flag = true;
            ans = ans + " -> v" + to_string(root + 1);
            dfsprint(ans, e, e[i].vertex[1]);
        }
    }
    if(!flag)
    {
        cout << ans << endl;
    }
}
int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
    Graph g;
    g.criticalPath();
    return 0;
}