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
    //kΪ��������ʼ�������
    void DFS(int k);
    void BFS(int k);
    void Dijkstra(int k);
    void displayArc();
};

Graph::Graph()
{
    int n, e;

    n = inputNumber("����������ͼ�еĶ�����(������20)��", "�������������...", MAXSIZE);

    int max_e = n * (n - 1);
    e = inputNumber("����������ͼ�еı���(������" + to_string(max_e) + ")��", "�����������...", max_e);

    this->vertexNum = n;
    this->arcNum = e;
    memset(vertex, 0, sizeof(vertex));
    //�����������Ϣ...(��)
    //cout<<"���붥����Ϣ:"<<endl;
    for (int i = 0; i < vertexNum; i++)
    {
        //cout << "v" << i << " :";
        //cin >> vertex[i];
        vertex[i] = i + 1;
    }

    cout << "����ͼ�еĶ������Ϊ��";
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

    cout << "����������ͼ�ı�:" << endl;
    for (int i = 0; i < arcNum; i++)
    {
        int a, b;
        int value;
        cout << "�����" << i + 1 << "���ߵ����˶��㣺" << endl;
        while (true)
        {
            a = inputNumber(("�����" + to_string(i + 1) + "���ߵĵ�һ�����㣺"), "�������...", vertexNum) - 1;
            b = inputNumber(("�����" + to_string(i + 1) + "���ߵĵڶ������㣺"), "�������...", vertexNum) - 1;
            value = inputNumber(("�����" + to_string(i + 1) + "���ߵ�Ȩ�أ�"), "�������...", INT_MAX);
            if (arc[a][b] != INT_MAX)
            {
                cout << "�ñ�(v" << a << ",v" << b << ")�Ѵ���,����������..." << endl;
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
    cout << "����ͼ���ڽӾ���:" << endl;
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            if (arc[i][j] == INT_MAX)
            {
                cout << "��";
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
    cout << "�������������";
    DFSTraverse(0);
    cout << endl;
    cleanVisited();
}

void Graph::DFSTraverse(int k)
{
    cout << "v" << vertex[k] << " ";
    //cout << vertex[k] << "  ";
    visited[k] = true;
    for (int i = 0; i < vertexNum; i++)
    {
        if (arc[k][i] != INT_MAX && visited[i] == false)
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
    cout << "�������������";

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
    //�Ӹ������㵽���Ŀ���
    int cost[MAXSIZE];
    //���������·���У��õ����һ����±�
    int pathCost[MAXSIZE];
    for (int i = 0; i < MAXSIZE; i++)
    {
        cost[i] = INT_MAX;
        pathCost[i] = -1;
    }

    visited[k] = true;
    cost[k] = 0;
    pathCost[k] = k;
    for (int i = 0; i < vertexNum; i++)
    {
        if (arc[k][i] != INT_MAX)
        {
            cost[i] = arc[k][i];
            pathCost[i] = k;
        }
    }
    while (true)
    {

        int minIndex = -1;
        int min = INT_MAX;
        for (int i = 0; i < vertexNum; i++)
        {
            if (min > cost[i] && visited[i] == false)
            {
                minIndex = i;
                min = cost[i];
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

                int minDist = cost[minIndex] + arc[minIndex][i];
                if (minDist < cost[i])
                {
                    cost[i] = minDist;
                    pathCost[i] = minIndex;
                }
            }
        }
    }


    cout << "��v" << vertex[k] << "Ϊ��㵽��������·��Ϊ:" << endl;
    for (int i = 0; i < vertexNum; i++)
    {
        string ans = "v" + to_string(vertex[i]);
        int j = pathCost[i];
        while (true)
        {
            if (j == -1)
            {
                ans = "v" + to_string(vertex[k]) + " -> " + ans;
                break;
            }
            ans = "v" + to_string(vertex[j]) + " -> " + ans;
            if (j == k)
            {
                break;
            }
            j = pathCost[j];
        }

        cout << ans << " = ";
        if (pathCost[i] != -1)
        {
            cout << cost[i];
        }
        else
        {
            cout << "is no way";
        }
        cout << endl;
    }
}

int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
    Graph g;

    //g.BFS(0);
    //g.DFS(0);
    g.Dijkstra(0);

    return 0;
}