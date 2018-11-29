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


Node *getHuffmanCode(Node *h, int index)
{
    if (h[index].lchild != -1)
    {
        h[h[index].lchild].code = h[index].code + "0";
        h = getHuffmanCode(h, h[index].lchild);
    }
    if (h[index].rchild != -1)
    {
        h[h[index].rchild].code = h[index].code + "1";
        h = getHuffmanCode(h, h[index].rchild);
    }
    return h;
}
//Get the smallest two weight node index of tree
void getMin2(HuffmanTree *tree, int *index1, int *index2)
{
    //const int max = 2147483647;
    const int max = INT_MAX;
    int min1 = max;
    int min2 = max;
    Node *array = tree->tree;

    for (int i = 0; i < tree->size; i++)
    {
        if (array[i].parent == -1 && array[i].weight >= 0)
        {
            if (array[i].weight < min1)
            {
                min2 = min1;
                *index2 = *index1;
                min1 = array[i].weight;
                *index1 = i;
            }
            else if (array[i].weight < min2)
            {
                min2 = array[i].weight;
                *index2 = i;
            }
        }
    }
}
HuffmanTree *buildHuffman(int *weightArray, int n)
{
    int size = 2 * n - 1;
    Node *huffmanTree = new Node[size];

    HuffmanTree *temp = new HuffmanTree;
    temp->tree = huffmanTree;
    temp->size = size;

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
        huffmanTree[i].code = "";
    }
    for (int i = n; i < size; i++)
    {
        int indexMin1;
        int indexMin2;

        getMin2(temp, &indexMin1, &indexMin2);

        huffmanTree[i].weight = huffmanTree[indexMin1].weight + huffmanTree[indexMin2].weight;
        huffmanTree[i].lchild = indexMin1;
        huffmanTree[i].rchild = indexMin2;
        huffmanTree[indexMin1].parent = i;
        huffmanTree[indexMin2].parent = i;
    }

    huffmanTree = getHuffmanCode(huffmanTree, size - 1);

    return temp;
}


void print(HuffmanTree *h)
{
    cout << "index\tweight\tparent\tlchild\trchild" << endl;
    for (int i = 0; i < h->size; i++)
    {
        cout << i << '\t' << h->tree[i].weight << '\t' << h->tree[i].parent << '\t' << h->tree[i].lchild << '\t' << h->tree[i].rchild << endl;
    }
}

void printHuffmanCode(HuffmanTree *h)
{
    cout << "weight\tcode" << endl;
    int n = (h->size + 1) / 2;
    for (int i = 0; i < n; i++)
    {
        cout << h->tree[i].weight << '\t' << h->tree[i].code << endl;
    }
}

int main()
{
    int n;
    cout << "Please input the number of HuffmanTree's leaf :";
    cin >> n;
    int *a = new int[n];
    cout << "Please input the weight of leafs :" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    HuffmanTree *t = buildHuffman(a, n);
    print(t);
    cout << endl;
    printHuffmanCode(t);

    delete t;
    delete[] a;
    return 0;
}
