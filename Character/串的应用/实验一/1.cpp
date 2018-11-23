#include <iostream>
using namespace std;

int strlen(char *chs)
{
    int i = 0;
    int cnt = 0;
    while (chs[i++] != '\0')
    {
        cnt++;
    }
    return cnt;
}
bool find(char *src, char *p)//O(n)
{
    int i = 0;
    int j = 0;
    int lenSrc = strlen(src);
    int lenP = strlen(p);
    while (i < lenSrc && j < lenP)
    {
        if (src[i] == p[j])
        {
            j++;
        }
        i++;
    }
    if (j == lenP)
    {
        return true;
    }
    return false;
}

int main()
{
    //test example
    char a[] = "CK";
    char b[] = "CalvinKlein";
    char c[] = "ChenKun";
    cout << "模式:" << a << endl;
    cout << "主串A:" << b << endl;
    cout << "主串B:" << c << endl;
    cout << (find(b, a) && find(c, a) ? "YES" : "NO") << endl;

    cout << endl;

    char d[] = "abc";
    char e[] = "abcde";
    char f[] = "adbec";
    cout << "模式:" << d << endl;
    cout << "主串A:" << e << endl;
    cout << "主串B:" << f << endl;
    cout << (find(e, d) && find(f, e) ? "YES" : "NO") << endl;
    return 0;
}