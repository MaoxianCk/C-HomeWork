#include <iostream>
#include <limits.h>
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

class Graph
{
  private:
    static const int MAXSIZE = 20;
    int vertexNum, arcNum;

    int vertex[MAXSIZE];
    int arc[MAXSIZE][MAXSIZE];
    bool visited[MAXSIZE];

    void DFSTraverse(int k);
    void cleanVisited();

  public:
    Graph();
    void topSort();
    //k为遍历的起始顶点序号
    void DFS(int k);
    void BFS(int k);
    void Dijkstra(int k);
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
void Graph::Dijkstra(int k)
{
    cleanVisited();
    //shortest path from start(k) to per Point
    int dist[MAXSIZE];
    int path[MAXSIZE];
    for (int i = 0; i < MAXSIZE; i++)
    {
        dist[i] = INT_MAX;
        path[i] = -1;
    }


    visited[k] = true;
    dist[k] = 0;
    path[k] = vertex[k];
    for (int i = 0; i < vertexNum; i++)
    {
        if (arc[k][i] != INT_MAX)
        {
            //
            //cout <<"----"<< k << "  arc:" << arc[k][i] << endl;
            dist[i] = arc[k][i];
            path[i] = vertex[k];
        }
    }
////////////////////////
        cout << endl;
        cout << "vertex\tnear\tdist" << endl;
        for (int i = 0; i < vertexNum; i++)
        {
            cout << vertex[i] << "\t" << path[i] << "\t" << dist[i] << endl;
        }
    while (true)
    {



        int minIndex = -1;
        int min = INT_MAX;
        for (int i = 0; i < vertexNum; i++)
        {
            if (min > dist[i] && visited[i] == false)
            {
                minIndex = i;
                min = dist[i];
            }
        }
        if (minIndex == -1)
        {
            break;
        }

        visited[minIndex] = true;
        for (int i = 0; i < vertexNum; i++)
        {
            if (arc[minIndex][i] != INT_MAX && visited[i] == false)
            {

                int minDist = dist[minIndex] + arc[minIndex][i];
                //
                //cout << "---minDist : " << dist[minIndex] << "+" << arc[minIndex][i] << endl;
                if (minDist < dist[i])
                {
                cout << "-----min:" << min << " minIndex:" << minIndex << endl;
                    dist[i] = minDist;
                    path[i] = vertex[minIndex];
                }
            }
        }
    }
    //cout << endl;
    //cout << "vertex\tnear\tdist" << endl;
    for (int i = 0; i < vertexNum; i++)
    {
        cout << vertex[i] << "\t" << path[i] << "\t" << dist[i] << endl;
    }
}

int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
    Graph g;

    g.BFS(0);
    g.DFS(0);
    g.Dijkstra(0);

    return 0;
}