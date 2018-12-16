#include <algorithm>
#include <iostream>
#include <string>
#include <windows.h>
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
struct ch_value
{
    char ch;
    int value;
    string code;
};

Node *getHuffmanCode(Node *h, int index)
{
    int lchild = h[index].lchild;
    if (h[index].lchild != -1)
    {
        h[lchild].code = h[index].code + "0";
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
HuffmanTree *buildHuffman(ch_value *array, int n)
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
            huffmanTree[i].weight = array[i].value;
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

    for (int i = 0; i < n; i++)
    {
        array[i].code = huffmanTree[i].code;
    }

    return temp;
}
bool find(string src, string p, int beg)
{
    int i = beg;
    int j = 0;
    int lenSrc = src.length();
    int lenP = p.length();
    while (i < lenSrc && j < lenP)
    {
        if (src[i] == p[j])
        {
            j++;
            i++;
        }
        else
        {
            return false;
        }
    }
    if (j == lenP)
    {
        return true;
    }
    return false;
}
string returnByHuffman(ch_value *a, int n, string code)
{
    string ans = "";
    int beg = 0;
    while (beg < code.length())
    {
        bool isfind = false;
        for (int i = 0; i < n; i++)
        {
            if (find(code, a[i].code, beg))
            {
                isfind = true;
                beg += a[i].code.length();
                ans += a[i].ch;
                break;
            }
        }

        if (!isfind)
        {
            return "";
        }
    }

    return ans;
}
string toCodeByHuffman(ch_value *a, int m, string str)
{
    string code = "";
    for (int i = 0; i < str.length(); i++)
    {
        bool isfind = false;
        for (int j = 0; j < m; j++)
        {
            if (str[i] == a[j].ch)
            {
                code += a[j].code;
                isfind = true;
                break;
            }
        }
        if (!isfind)
        {
            return "";
        }
    }
    return code;
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

void printChValue(ch_value *a, int n)
{
    cout << "char\tvalue\tcode\t" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << a[i].ch << "\t" << a[i].value << "\t" << a[i].code << endl;
    }
}

bool isSmallWord(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return true;
    }
    return false;
}

bool cmp(ch_value a, ch_value b)
{
    return a.ch < b.ch;
}
int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
    cout << "Please input the string :" << endl;
    string str;
    cin >> str;

    //pre deal
    ch_value a[26];
    int m = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (!isSmallWord(str[i]))
        {
            //if its illeagal , jump over it!
            cout << "There are some error character!" << endl;
            system("pause");
            exit(0);
        }
        bool isfind = false;
        for (int j = 0; j < m; j++)
        {
            if (str[i] == a[j].ch)
            {
                a[j].value++;
                isfind = true;
                break;
            }
        }
        if (!isfind)
        {
            a[m].value = 1;
            a[m++].ch = str[i];
        }
    }
    if (m == 0)
    {
        cout << "There are no legal characters!" << endl;
        system("pause");
        exit(0);
    }
    //sort by char order
    sort(a, a + m, cmp);

    HuffmanTree *t = buildHuffman(a, m);

    print(t);
    cout << endl;
    printChValue(a, m);
    cout << endl;
    //printHuffmanCode(t);
    cout << "Please input str:" << endl;
    string str1, ans;
    cin >> str1;
    ans = toCodeByHuffman(a, m, str1);
    cout << (ans == "" ? "string error!" : ans) << endl;

    cout << "Please input code" << endl;
    string code;
    cin >> code;
    ans = returnByHuffman(a, m, code);
    cout << (ans == "" ? "string error!" : ans) << endl;

    delete t;
    return 0;
}
