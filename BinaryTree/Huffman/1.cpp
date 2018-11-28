#include <iostream>
using namespace std;

struct Node
{
    int weight;
    int parent;
    int lchild;
    int rchild;
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

    int min1 = weightArray[0], min2 = weightArray[1];
    int indexMin1 = 0, indexMin2 = 1;

    for (int i = 0; i < size; i++)
    {
        if (i < n)
        {
            huffmanTree[i].weight = weightArray[i];
        }
        else
        {
            huffmanTree[i].weight = -1;
        }
        huffmanTree[i].lchild = -1;
        huffmanTree[i].rchild = -1;
        huffmanTree[i].parent = -1;
    }
    for (int i = n; i < size; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (huffmanTree[j].parent != -1)
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
    HuffmanTree *temp = new HuffmanTree;
    temp->tree = huffmanTree;
    temp->size = size;
    return temp;
}

void print(HuffmanTree *h)
{
    cout << "下标\t权值\tparent\tlchild\trchild" << endl;
    for (int i = 0; i < h->size; i++)
    {
        cout << i << '\t' << h->tree[i].weight << '\t' << h->tree[i].parent << h->tree[i].lchild << h->tree[i].rchild << endl;
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
    delete []t;
    delete []a;
    return 0;
}