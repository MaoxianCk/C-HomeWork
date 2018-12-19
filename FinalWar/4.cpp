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
    void criticalPath();
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

void Graph::criticalPath()
{
    //���緢��ʱ��
    int ve[MAXSIZE] = {0};
    //������ʱ��
    int vl[MAXSIZE];
    //���翪ʼʱ��
    int ee[MAXSIZE];
    //����ʼʱ��
    int el[MAXSIZE];

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
        int min=INT_MAX;
        for (int j = vertexNum - 1; j >= 0; j--)
        {

            if (arc[i][j] !=INT_MAX &&  vl[j]-arc[i][j] < min)
            {
                min = vl[j] - arc[i][j];
                vl[i] = min;
            }
        }
    }
    for (int i = 0; i < vertexNum;i++)
    {
        cout << ve[i] << "  ";
    }
    cout << endl;
    for (int i = 0; i < vertexNum; i++)
    {
        cout << vl[i] << "  ";
    }
}
int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
    Graph g;
    g.criticalPath();
    return 0;
}