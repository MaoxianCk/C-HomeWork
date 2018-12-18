// ConsoleApplication11.cpp : �������̨Ӧ�ó������ڵ㡣
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
	string code; //���������ÿ������Ӧ�Ĺ���������
	void print()
	{
		cout << weight << "\t" << parent << "\t" << lchild << "\t" << rchild << endl;
	}
};
struct ch_f_code
{
	char ch;
	int weight;
	string code;   //ch��Ӧ�Ĺ���������
	void print()
	{
		cout << ch << "\t" << weight << "\t" << code << endl;
	}

};
void Select(element huffTree[], int &i1, int &i2, int n)
{
	//��min1��min2����ʼֵ--���ֵ ��min1���մ�ŵ�����Сֵ��min2���մ�ŵ��ǵڶ�Сֵ��
	int min1 = MAX;
	int min2 = MAX;

	for (int i = 0; i < 2 * n - 1; i++)
	{
		//����˫�ײ�Ϊ-1,��ʾ�Ѿ��������,����Ҫ�ٴ��� 
		if (huffTree[i].parent != -1)
		{
			continue;
		}
		int weight = huffTree[i].weight;
		if (weight == 0)
		{
			break;
		}
		if (weight < min1) // ��min1��ֵ��min2 ,�±�Ҳ�Ե����ٰ�Ȩֵ��min1
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
	//һ��ʼindex���������Ǹ������±�
	int lchild = huffTree[index].lchild;
	int rchild = huffTree[index].rchild;
	if (lchild != -1)
	{
		huffTree[lchild].code = huffTree[index].code + "0";  //���ӵı���ͻ���ڸ��׵ı����0
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
	for (int i = 0; i < 2 * n - 1; i++) //��ʼ�������н���û��˫�׺ͺ���
	{
		huffTree[i].code = "";  //��ʼ���������ַ���Ϊ�մ�
		huffTree[i].weight = 0;
		huffTree[i].parent = -1;
		huffTree[i].lchild = -1;
		huffTree[i].rchild = -1;
	}
	for (int i = 0; i < n; i++)  //����n��ֻ���и����Ķ�����
	{
		huffTree[i].weight = quanzhi[i];//��Ȩֵ
	}
	for (int k = n; k < 2 * n - 1; k++)
	{
		int i1 = 0, i2 = 0;
		Select(huffTree, i1, i2, n); //����Ȩֵ��С����������㣬�±�Ϊi1��i2
		huffTree[i1].parent = k;  //��i1��i2�ϲ�����i1��i2��˫����k
		huffTree[i2].parent = k;
		huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
		huffTree[k].lchild = i1;
		huffTree[k].rchild = i2;
	}
	HuffmanTreeCode(huffTree, 2 * n - 2);//2n-2�Ǹ������±�  
}
bool find(string code, string p, int start)
{
	int i = start; //�������±���ʼλ��
	int j = 0;  //�Ӵ����±�λ��
	while (i < code.length() && j < p.length())
	{
		if (code[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			return false;  //ֻҪ��һ����ƥ���return false
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
		cout << "����������Ҫ��Ӣ�ģ�";
		string s;
		cin >> s;
		s = change_string(s); //�ж��Ƿ�Ϊ�մ�����û��Сд��ĸ�����������ַ�
		if (s == "")
		{
			cout << "ɶ��û��Ŷ��" << endl;;
			return 0;
		}

		ch_f_code a[26];  //ֻ��Сд��ĸ
		for (int i = 0; i < 26; i++)
		{
			a[i].weight = 1;   //�Ƚ��ṹ�������Ȩֵȫ����ʼ��Ϊ1
		}
		int m = 0;  //������¼��ǰ��ĸ�����һ��ʼ�Ǵ���0��
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] >= 'a'&&s[i] <= 'z')
			{
				bool flag = false;
				for (int j = 0; j < m; j++)
				{
					if (s[i] == a[j].ch)  //�жϵ�ǰ����ĸ��֮ǰ�����û���ظ������еĻ�����֮ǰ��λ��Ƶ��+1
					{
						a[j].weight++;
						flag = true;
						break;
					}
				}
				if (flag == false)
				{
					a[m].ch = s[i];   //�ѵ�ǰλ�õ�s[i]����a��
					m++;
				}
			}
			else
			{
				continue;
			}
		}
		int *quanzhi = new int[m];  //m��ΪҶ�ӽ�����
		for (int i = 0; i < m; i++)
		{
			quanzhi[i] = a[i].weight;
		}
		element *huffTree = new element[2 * m - 1]; //��һ�ó���Ϊ2m-1����
		HuffmanTree(huffTree, quanzhi, m);

		for (int i = 0; i < m; i++)
		{
			a[i].code = huffTree[i].code;//  ���������ı���浽a����������
		}
		cout << endl;
		cout << "�±�\tweight\tparent\tlchild\trchild" << endl;
		for (int i = 0; i < 2 * m - 1; i++)
		{
			cout << i << "\t";
			huffTree[i].print();
		}
		cout << endl;
		cout << "�±�\tchar\tweight\tcode" << endl;
		for (int i = 0; i < m; i++)
		{
			cout << i << "\t";
			a[i].print();
		}
		cout << endl;
	
	while (true)
	{
		cout << endl;
		cout << "�������ַ�����";
		string str;
		cin >> str;

		bool flag = false;
		for (int i = 0; i < str.length(); i++)
		{
			flag = false;
			for (int j = 0; j < m; j++)
			{
				if (str[i] == a[j].ch) //�ҵ�һ���ģ�break����ѭ�����ű�����һ��str
				{
					flag = true;
					break;
				}

			}
			if (flag == false)    //ֻҪ��һ���Ǵ�� ����ʾ����
			{
				cout << "������ַ�������" << endl;
				break;
			}
		}
		if (flag == true)
		{
			cout << "�����Ӧ�ַ����ı��룺";
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
		cout << "��������룺";
		string code;
		cin >> code;
		int begin = 0;  //����һ��ʼ���±�λ��Ϊ0
		bool isfind = true;
		string result = "";  //�����������ȷ������ַ������ȳ�ʼ��Ϊ�մ�
		while (begin< code.length() && isfind)
		{
			isfind = false;
			for (int j = 0; j < m; j++)
			{
				if (find(code, a[j].code, begin)) //�������Ӵ�����ʼλ�ô���ȥ������ҵ�
				{
					begin += a[j].code.length();  //��ʼλ�þͱ�Ϊ��һ���Ӵ���ʼ�ҵ�λ��
					result += a[j].ch;
					isfind = true;
					break;
				}
			}
		}
		if (isfind == false)
		{
			cout << "����ı�������" << endl;
		}
		else
		{
			cout << "����ı�������Ӧ���ַ���Ϊ��" << result << endl;
			break;
		}
	}
	cout << endl;

	return 0;
}


