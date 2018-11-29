#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int weight;
    int parent;
    int lchild;
    int rchild;
    string code;
};
struct HuffmanTree
{
    Node *tree;
    int size;
};

HuffmanTree *buildHuffman(int *weightArray, int n)
{
    int size = 2 * n - 1;
    Node *huffmanTree = new Node[size];

    int min1 , min2 ;
    int indexMin1, indexMin2;
    int max=0;
    //数据预处理
    for (int i = 0; i < size; i++)
    {
        if (i < n)
        {
            huffmanTree[i].weight = weightArray[i];
            max+=huffmanTree[i].weight;
        }
        else
        {
            huffmanTree[i].weight = -1;
        }
        huffmanTree[i].lchild = -1;
        huffmanTree[i].rchild = -1;
        huffmanTree[i].parent = -1;
        huffmanTree[i].code="";
    }
    
    for (int i = n; i < size; i++)
    {
        min1=max;
        min2=max;
        for (int j = 0; j < i; j++)
        {
            if (huffmanTree[j].parent == -1)
            {
                if (huffmanTree[j].weight < min1)
                {
                    min2 = min1;
                    indexMin2 = indexMin1;
                    min1 = huffmanTree[j].weight;
                    indexMin1 = j;
                }
                else if (huffmanTree[j].weight < min2)
                {
                    min2 = huffmanTree[j].weight;
                    indexMin2 = j;
                }
            }
        }

        huffmanTree[i].weight = min1 + min2;
        huffmanTree[i].lchild = indexMin1;
        huffmanTree[i].rchild = indexMin2;
        huffmanTree[indexMin1].parent = i;
        huffmanTree[indexMin2].parent = i;
    }
    
    huffmanTree=getHuffmanCode(huffmanTree,size-1);
    
    
    HuffmanTree *temp = new HuffmanTree;
    temp->tree = huffmanTree;
    temp->size = size;
    
    
    return temp;
}
Node *getHuffmanCode(Node *h ,int index)
{
    if(h[index].lchild!=-1)
    {
        h[h[index].lchild].code=h[index].code+"0";
        h=getHuffmanCode(h,h[index].lchild);
    }
    if(h[index].rchild!=-1)
    {
        h[h[index].rchild].code=h[index].code+"1";
        h=getHuffmanCode(h,h[index].rchild);
    }
    return h;
}

void print(HuffmanTree *h)
{
    cout << "index\tweight\tparent\tlchild\trchild\tcode" << endl;
    for (int i = 0; i < h->size; i++)
    {
        cout << i << '\t' << h->tree[i].weight << '\t' << h->tree[i].parent<< '\t' << h->tree[i].lchild << '\t'<< h->tree[i].rchild << '\t'<<h->tree[i].code<< endl;
    }
}

void printHuffmanCode(HuffmanTree *h)
{
    cout<<"weight\tcode"<<endl;
    int n=(h->size+1)/2;
    for(int i=0;i<n;i++)
    {
        cout << h->tree[i].weight<<'\t'<<h->tree[i].code<<endl;
    }
}

int main()
{
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
    }

    HuffmanTree *t = buildHuffman(a, n);
    print(t);
    printHuffmanCode(t);
    delete t;
    delete []a;
    return 0;
}
