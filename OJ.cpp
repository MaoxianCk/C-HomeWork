#include <iostream>
#include <queue>
#include <stack>
using namespace std;

const int MaxSize = 20; //图中的最多顶点个数

class MGraph
{
  public:
    MGraph(){};
    MGraph(int a[], int n, int e); //构造函数，建立具有n个顶点e条边的图
    ~MGraph(){};                   //析构函数为空
    void DFSTraverse(int v);       //深度优先
    void BFSTraverse(int v);       //广度优先
    void Print();

  private:
    int vertex[MaxSize];       //存放图中顶点的数组
    int arc[MaxSize][MaxSize]; //存放图中边的数组
    int vertexNum, arcNum;     //图的顶点数和边数
};

MGraph::MGraph(int a[], int n, int e)
{
    vertexNum = n;
    arcNum = e;
    for (int i = 0; i < vertexNum; i++)
    {
        vertex[i] = a[i];
    }
    for (int i = 0; i < vertexNum; i++) //初始化邻接矩阵
    {
        for (int j = 0; j < vertexNum; j++)
        {
            arc[i][j] = 0;
        }
    }
    cout << "请输入图中的边：" << endl;
    for (int k = 0; k < arcNum; k++)
    { //依次输入每一条边
        int i, j;
        cout << "第" << k + 1 << "条边的起点和终点序号分别为：";
        cin >> i >> j;
        if (i == j)
        {
            cout << "自身不能有边,请重新输入..." << endl;
            k--;
            continue;
        }
        arc[i][j] = 1;
        arc[j][i] = 1; //设置有边标志
    }
}

void MGraph::DFSTraverse(int v)
{
    bool visited[MaxSize] = {0}; //该数组用于标记某顶点是否被遍历过
    stack<int> s;
    cout << "v" << v << " ";
    visited[v] = true;
    s.push(v);

    while(!s.empty())
    {
        for (int j = 0; j < vertexNum;j++)
        {
            if(arc[s.top()][j]==1 && visited[j]==false)
            {
                cout << "v" << j << " ";
                s.push(j);
                visited[j] = true;
            }
        }
        s.pop();
    }
}

void MGraph::BFSTraverse(int v)
{
    bool visited[MaxSize]; //该数组用于标记某顶点是否被遍历过
    queue<int> que;
    for (int i = 0; i < vertexNum; i++)
    {
        visited[i] = false;
    }
    //从这里补充
    cout << "v" << v << " ";
    //cout << vertex[v];
    que.push(v);
    visited[v] = 1;
    while (!que.empty())
    {
        v = que.front(); //v=队列的队头元素出队
        que.pop();
        for (int j = 0; j < vertexNum; j++)
        {
            if (arc[v][j] == 1 && visited[j] == 0)
            {
                que.push(j);
                visited[j] = 1;
                cout << "v" << j << " ";
            }
        }
    }
}

void MGraph::Print()
{
    cout << "无向图的邻接矩阵：" << endl;
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            cout << arc[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int n = 0;
    int e = 0;
    cout << "请输入无向图中顶点的个数(不大于" << MaxSize << "个)：";
    cin >> n;
    while (n > MaxSize)
    {
        cout << "顶点个数输入错误，请重新输入..." << endl;
        cout << "请输入无向图中顶点的个数(不大于" << MaxSize << "个)：";
        cin >> n;
    }
    cout << "请输入无向图中边的条数(不大于 " << n << " ×" << (n - 1) << " ÷2 个)：";
    cin >> e;
    while (e > n * (n - 1) / 2)
    {
        cout << "边的条数输入错误，请重新输入..." << endl;
        cout << "请输入无向图中边的条数(不大于 " << n << " ×" << (n - 1) << " ÷2 个)：";
        cin >> e;
    }
    cout << "无向图中顶点的序号分别为：";
    int *vertex = new int[n];
    for (int i = 0; i < n; i++)
    {
        vertex[i] = i;
        cout << " v" << vertex[i];
    }
    cout << endl;
    MGraph *mGraph = new MGraph(vertex, n, e);
    mGraph->Print();

    cout << "深度优先搜索序列： ";
    mGraph->DFSTraverse(0); //令0为搜索的起始点
    cout << endl;
    cout << "广度优先搜索序列： ";
    mGraph->BFSTraverse(0); //令0为搜索的起始点
    delete[] vertex;
    delete mGraph;
    return 0;
}
