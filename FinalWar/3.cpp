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
    static const int MAXSIZE = 100;
    int vertexNum, arcNum;

    char vertex[MAXSIZE];
    int arc[MAXSIZE][MAXSIZE];
    bool visited[MAXSIZE];

    void cleanVisited();

  public:
    Graph();
    //kΪ��������ʼ�������
    void Prim(int k);
    void Kruskal();
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

    for (int i = 0; i < vertexNum; i++)
    {
        vertex[i] = (char)('a' + i);
    }

    cout << "����ͼ�еĶ���Ϊ��";
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
                cout << "�ñ�(i" << a << ",i" << b << ")�Ѵ���,����������..." << endl;
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

void Graph::Prim(int k)
{
    cleanVisited();
    ArcVertexVal ans[MAXSIZE];
    // ÿ��δ�������еĶ��㵽������С����
    int cost[MAXSIZE];
    // ����С������Ӧ��δ�������еĶ�����
    int pathCost[MAXSIZE];

    int min = INT_MAX;
    int minIndex = k;

    // ���
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

        //ֻ��Ҫ�������¼���ĵ������Ŀ���
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
//���鼯���
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
    //���鼯
    int v[MAXSIZE];
    ArcVertexVal KruskalArc[MAXSIZE];
    ArcVertexVal ans[MAXSIZE];
    int m = 0;

    for (int i = 0; i < vertexNum; i++)
    {
        //��ʼ�����鼯
        v[i] = i;
        //����������
        for (int j = i + 1; j < vertexNum; j++)
        {
            //��ͼתΪ�߽ṹ���� KruskalArc
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
    //����С�ķ��������μ���mst
    for (int i = 0; i < arcNum; i++)
    {
        int a, b;
        a = getRoot(v, KruskalArc[i].vertex[0]);
        b = getRoot(v, KruskalArc[i].vertex[1]);
        //���鼯�жϼ������
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