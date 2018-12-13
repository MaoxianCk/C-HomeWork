#include <iostream>
#include <queue>
#include <stack>
using namespace std;

const int MaxSize = 20; //ͼ�е���ඥ�����

class MGraph
{
  public:
    MGraph(){};
    MGraph(int a[], int n, int e); //���캯������������n������e���ߵ�ͼ
    ~MGraph(){};                   //��������Ϊ��
    void DFSTraverse(int v);       //�������
    void BFSTraverse(int v);       //�������
    void Print();

  private:
    int vertex[MaxSize];       //���ͼ�ж��������
    int arc[MaxSize][MaxSize]; //���ͼ�бߵ�����
    int vertexNum, arcNum;     //ͼ�Ķ������ͱ���
};

MGraph::MGraph(int a[], int n, int e)
{
    vertexNum = n;
    arcNum = e;
    for (int i = 0; i < vertexNum; i++)
    {
        vertex[i] = a[i];
    }
    for (int i = 0; i < vertexNum; i++) //��ʼ���ڽӾ���
    {
        for (int j = 0; j < vertexNum; j++)
        {
            arc[i][j] = 0;
        }
    }
    cout << "������ͼ�еıߣ�" << endl;
    for (int k = 0; k < arcNum; k++)
    { //��������ÿһ����
        int i, j;
        cout << "��" << k + 1 << "���ߵ������յ���ŷֱ�Ϊ��";
        cin >> i >> j;
        if (i == j)
        {
            cout << "�������б�,����������..." << endl;
            k--;
            continue;
        }
        arc[i][j] = 1;
        arc[j][i] = 1; //�����б߱�־
    }
}

void MGraph::DFSTraverse(int v)
{
    bool visited[MaxSize] = {0}; //���������ڱ��ĳ�����Ƿ񱻱�����
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
    bool visited[MaxSize]; //���������ڱ��ĳ�����Ƿ񱻱�����
    queue<int> que;
    for (int i = 0; i < vertexNum; i++)
    {
        visited[i] = false;
    }
    //�����ﲹ��
    cout << "v" << v << " ";
    //cout << vertex[v];
    que.push(v);
    visited[v] = 1;
    while (!que.empty())
    {
        v = que.front(); //v=���еĶ�ͷԪ�س���
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
    cout << "����ͼ���ڽӾ���" << endl;
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
    cout << "����������ͼ�ж���ĸ���(������" << MaxSize << "��)��";
    cin >> n;
    while (n > MaxSize)
    {
        cout << "������������������������..." << endl;
        cout << "����������ͼ�ж���ĸ���(������" << MaxSize << "��)��";
        cin >> n;
    }
    cout << "����������ͼ�бߵ�����(������ " << n << " ��" << (n - 1) << " ��2 ��)��";
    cin >> e;
    while (e > n * (n - 1) / 2)
    {
        cout << "�ߵ����������������������..." << endl;
        cout << "����������ͼ�бߵ�����(������ " << n << " ��" << (n - 1) << " ��2 ��)��";
        cin >> e;
    }
    cout << "����ͼ�ж������ŷֱ�Ϊ��";
    int *vertex = new int[n];
    for (int i = 0; i < n; i++)
    {
        vertex[i] = i;
        cout << " v" << vertex[i];
    }
    cout << endl;
    MGraph *mGraph = new MGraph(vertex, n, e);
    mGraph->Print();

    cout << "��������������У� ";
    mGraph->DFSTraverse(0); //��0Ϊ��������ʼ��
    cout << endl;
    cout << "��������������У� ";
    mGraph->BFSTraverse(0); //��0Ϊ��������ʼ��
    delete[] vertex;
    delete mGraph;
    return 0;
}
