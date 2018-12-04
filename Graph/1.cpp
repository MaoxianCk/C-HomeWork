#include <iostream>
using namespace std;

template <class DataType>
class Graph
{
  private:
    static const int MAXSIZE = 20;
    DataType vertex[MAXSIZE];
    bool arc[MAXSIZE][MAXSIZE];
    int vertexNum, arcNum;
    bool visited[MAXSIZE];

    void DFSTraverse(int k);

  public:
    Graph();
    ~Graph();
    //k为遍历的起始顶点序号
    void DFS(int k);
    void BFS(int k);
    void cleanVisited();
};
template <class DataType>
Graph<DataType>::Graph()
{
    int n, e;
    cout << "请输入图的顶点数：";
    cin >> n;
    //如果 > MAXSIZE 处理...
    cout << "请输入图的边数：";
    cin >> e; //如果 > MAXSIZE 处理...

    this->vertexNum = n;
    this->arcNum = e;
    for (int i = 0; i < vertexNum; i++)
    {
        vertex[i] = i;
        visited[i] = 0;
    }

    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            arc[i][j] = 0;
        }
    }

    for (int i = 0; i < arcNum; i++)
    {
        int a, b;
        cout << "输入第" << i + 1 << "条边的两端顶点：";
        cin >> a >> b;
        arc[a][b] = 1;
        arc[b][a] = 1;
    }
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
void Graph<DataType>::DFS(int k)
{
    cleanVisited();
    DFSTraverse(0);
    cleanVisited();
}
template <class DataType>
void Graph<DataType>::DFSTraverse(int k)
{
    cout << vertex[k];
    visited[k] = 1;
    for (int i = 0; i < vertexNum; i++)
    {
        if (arc[k][i] == 1 && visited[i] == 0)
        {
            DFSTraverse(i);
        }
    }
}

int main()
{
    return 0;
}