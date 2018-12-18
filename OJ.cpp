// ConsoleApplication11.cpp : 定义控制台应用程序的入口点。
//

#include<iostream>
#include<string>
#include <stack>
using namespace std;

const int MAX = 2147483647;
struct element
{
	int weight;
	int lchild, rchild, parent;
	string code; //存哈夫曼树每个结点对应的哈夫曼编码
	void print()
	{
		cout << weight << "\t" << parent << "\t" << lchild << "\t" << rchild << endl;
	}
};
struct ch_f_code
{
	char ch;
	int weight;
	string code;   //ch对应的哈弗曼编码
	void print()
	{
		cout << ch << "\t" << weight << "\t" << code << endl;
	}

};
void Select(element huffTree[], int &i1, int &i2, int n)
{
	//给min1和min2赋初始值--最大值 （min1最终存放的是最小值，min2最终存放的是第二小值）
	int min1 = MAX;
	int min2 = MAX;

	for (int i = 0; i < 2 * n - 1; i++)
	{
		//结点的双亲不为-1,表示已经处理过了,不需要再处理 
		if (huffTree[i].parent != -1)
		{
			continue;
		}
		int weight = huffTree[i].weight;
		if (weight == 0)
		{
			break;
		}
		if (weight < min1) // 把min1的值给min2 ,下标也对调，再把权值给min1
		{
			min2 = min1;
			i2 = i1;
			min1 = weight;
			i1 = i;
		}
		else if (weight < min2)
		{
			min2 = weight;
			i2 = i;
		}
	}
}
void HuffmanTreeCode(element huffTree[], int index)
{
	//一开始index传进来的是根结点的下标
	int lchild = huffTree[index].lchild;
	int rchild = huffTree[index].rchild;
	if (lchild != -1)
	{
		huffTree[lchild].code = huffTree[index].code + "0";  //左孩子的编码就会等于父亲的编码加0
		HuffmanTreeCode(huffTree, lchild);
	}
	if (rchild != -1)
	{
		huffTree[rchild].code = huffTree[index].code + "1";
		HuffmanTreeCode(huffTree, rchild);

	}

}
void HuffmanTree(element huffTree[], int quanzhi[], int n)
{
	for (int i = 0; i < 2 * n - 1; i++) //初始化，所有结点均没有双亲和孩子
	{
		huffTree[i].code = "";  //初始化存编码的字符串为空串
		huffTree[i].weight = 0;
		huffTree[i].parent = -1;
		huffTree[i].lchild = -1;
		huffTree[i].rchild = -1;
	}
	for (int i = 0; i < n; i++)  //构造n棵只含有根结点的二叉树
	{
		huffTree[i].weight = quanzhi[i];//赋权值
	}
	for (int k = n; k < 2 * n - 1; k++)
	{
		int i1 = 0, i2 = 0;
		Select(huffTree, i1, i2, n); //查找权值最小的两个根结点，下标为i1和i2
		huffTree[i1].parent = k;  //将i1和i2合并，且i1和i2的双亲是k
		huffTree[i2].parent = k;
		huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
		huffTree[k].lchild = i1;
		huffTree[k].rchild = i2;
	}
	HuffmanTreeCode(huffTree, 2 * n - 2);//2n-2是根结点的下标  
}
bool find(string code, string p, int start)
{
	int i = start; //主串的下标起始位置
	int j = 0;  //子串的下标位置
	while (i < code.length() && j < p.length())
	{
		if (code[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			return false;  //只要有一个不匹配就return false
		}
	}
	if (j == p.length())
	{
		return true;
	}
	return false;
}
string change_string(string str)
{
	string str_buffer = "";
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 'a'&&str[i] <= 'z')
			str_buffer += str[i];
	}
	return str_buffer;

}

int main()
{
		cout << "请输入所需要的英文：";
		string s;
		cin >> s;
		s = change_string(s); //判断是否为空串，即没有小写字母，都是其他字符
		if (s == "")
		{
			cout << "啥都没有哦！" << endl;;
			return 0;
		}

		ch_f_code a[26];  //只存小写字母
		for (int i = 0; i < 26; i++)
		{
			a[i].weight = 1;   //先将结构数组里的权值全部初始化为1
		}
		int m = 0;  //用来记录当前存的个数，一开始是存了0个
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] >= 'a'&&s[i] <= 'z')
			{
				bool flag = false;
				for (int j = 0; j < m; j++)
				{
					if (s[i] == a[j].ch)  //判断当前的字母和之前存的有没有重复过，有的话就在之前的位置频率+1
					{
						a[j].weight++;
						flag = true;
						break;
					}
				}
				if (flag == false)
				{
					a[m].ch = s[i];   //把当前位置的s[i]存入a中
					m++;
				}
			}
			else
			{
				continue;
			}
		}
		int *quanzhi = new int[m];  //m就为叶子结点个数
		for (int i = 0; i < m; i++)
		{
			quanzhi[i] = a[i].weight;
		}
		element *huffTree = new element[2 * m - 1]; //建一棵长度为2m-1的树
		HuffmanTree(huffTree, quanzhi, m);

		for (int i = 0; i < m; i++)
		{
			a[i].code = huffTree[i].code;//  把树里面存的编码存到a的数组里面
		}
		cout << endl;
		cout << "下标\tweight\tparent\tlchild\trchild" << endl;
		for (int i = 0; i < 2 * m - 1; i++)
		{
			cout << i << "\t";
			huffTree[i].print();
		}
		cout << endl;
		cout << "下标\tchar\tweight\tcode" << endl;
		for (int i = 0; i < m; i++)
		{
			cout << i << "\t";
			a[i].print();
		}
		cout << endl;
	
	while (true)
	{
		cout << endl;
		cout << "请输入字符串：";
		string str;
		cin >> str;

		bool flag = false;
		for (int i = 0; i < str.length(); i++)
		{
			flag = false;
			for (int j = 0; j < m; j++)
			{
				if (str[i] == a[j].ch) //找到一样的，break跳出循环接着遍历下一个str
				{
					flag = true;
					break;
				}

			}
			if (flag == false)    //只要有一个是错的 都提示有误
			{
				cout << "输入的字符串有误！" << endl;
				break;
			}
		}
		if (flag == true)
		{
			cout << "输出对应字符串的编码：";
			for (int i = 0; i < str.length(); i++)
			{
				for (int j = 0; j < m; j++)
				{
					if (str[i] == a[j].ch)
					{
						cout << a[j].code;
						break;
					}
				}
			}
			cout << endl;
			break;
		}
	}
	while (true)
	{
		cout << endl;
		cout << "请输入编码：";
		string code;
		cin >> code;
		int begin = 0;  //定义一开始的下标位置为0
		bool isfind = true;
		string result = "";  //用来存最后正确结果的字符串，先初始化为空串
		while (begin< code.length() && isfind)
		{
			isfind = false;
			for (int j = 0; j < m; j++)
			{
				if (find(code, a[j].code, begin)) //将主串子串和起始位置传进去，如果找到
				{
					begin += a[j].code.length();  //起始位置就变为下一个子串开始找的位置
					result += a[j].ch;
					isfind = true;
					break;
				}
			}
		}
		if (isfind == false)
		{
			cout << "输入的编码有误" << endl;
		}
		else
		{
			cout << "输入的编码所对应的字符串为：" << result << endl;
			break;
		}
	}
	cout << endl;

	return 0;
}


