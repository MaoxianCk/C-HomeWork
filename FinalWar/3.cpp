#include <iostream>
#include <queue>
#include <windows.h>
using namespace std;

struct ArcVertexVal
{
    char vertex[2];
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

int inputVertex(string info, string errorInfo, int range)
{
    string str;
    while (true)
    {
        if (info != "")
        {
            cout << info;
        }
        bool flag = true; //���
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
    //kΪ��������ʼ�������
    void DFS(int k);
    void BFS(int k);
    void Prim(int k);
    void displayArc();
};

Graph::Graph()
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
        vertex[i] = (char)('a' + i);
    }

    cout << "����ͼ�еĶ���Ϊ��";
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

    cout << "����������ͼ�ı�:" << endl;
    for (int i = 0; i < arcNum; i++)
    {
        int a, b;
        int value;
        cout << "�����" << i + 1 << "���ߵ����˶��㣺" << endl;
        while (true)
        {
            a = inputVertex(("�����" + to_string(i + 1) + "���ߵĵ�һ�����㣺"), "�������...", vertexNum - 1);
            b = inputVertex(("�����" + to_string(i + 1) + "���ߵĵڶ������㣺"), "�������...", vertexNum - 1);
            value = inputNumber(("�����" + to_string(i + 1) + "���ߵ�Ȩ�أ�"), "�������...", INT_MAX);
            if (arc[a][b] != INT_MAX && arc[b][a] != INT_MAX)
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
    cout << "�������������";

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
    int lowcost[MAXSIZE];
    int dist[MAXSIZE];
    int min, minIndex, sum = 0;
    ArcVertexVal ans[MAXSIZE];
    for (int i = 1; i < vertexNum; i++)
    {
        lowcost[i] = arc[k][i];
        dist[i] = k;
    }
    dist[0] = 0;
    for (int i = 0; i < vertexNum - 1; i++)
    {
        min = INT_MAX;
        minIndex = 0;
        for (int j = 1; j < vertexNum; j++)
        {
            if (lowcost[j] < min && lowcost[j] != 0)
            {
                min = lowcost[j];
                minIndex = j;
            }
        }
        ans[i].vertex[0] = vertex[dist[minIndex]];
        ans[i].vertex[1] = vertex[minIndex];
        ans[i].value = min;
        //cout << "( " << vertex[dist[minIndex]] << " , " << vertex[minIndex] << " ) = " << min << endl;
        sum += min;
        lowcost[minIndex] = 0;
        for (int j = 1; j < vertexNum; j++)
        {
            if (arc[minIndex][j] < lowcost[j])
            {
                lowcost[j] = arc[minIndex][j];
                dist[j] = minIndex;
            }
        }
    }
    for (int i = 0; i < vertexNum-1;i++)
    {
        cout << "( " << ans[i].vertex[0] << " , " << ans[i].vertex[1] << " ) = " << ans[i].value << endl;
    }
        cout << "sum : " << sum << endl;
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