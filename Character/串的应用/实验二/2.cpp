#include <iostream>
#include <memory.h>
#include <windows.h>

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
int *getNext(char *p)
{
    int lenP = strlen(p);
    int *next = new int[lenP];
    next[0] = -1;
    int i = 0;
    int j = -1;
    while (i < lenP - 1)
    {
        if (j == -1 || p[j] == p[i])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
    return next;
}
int kmp(char *src, char *p, int beg)
{
    int lenSrc = strlen(src);
    int lenP = strlen(p);
    int *next = getNext(p);

    int i = beg, j = 0;
    while (i < lenSrc && j < lenP)
    {
        if (j == -1 || src[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j == lenP)
    {
        return i - j;
    }
    return -1;
}
int kmp_cnt(char *src, char *p)
{
    int lenSrc = strlen(src);
    int lenP = strlen(p);
    int *next = getNext(p);

    int i = 0, j = 0, cnt = 0;
    while (i < lenSrc)
    {
        if (j == -1 || src[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
        if (j == lenP)
        {
            j = 0;
            cnt++;
        }
    }

    return cnt;
}

int main()
{
    char a[] = "aaaaacdcbcdsssdaddasasaaaacdcbcaaaaacsdcbcadaaaacdcbcaaaaacdcbcaaaaaacdcbcaaaaacdcbcaaaaacdcbcaaaaacdcbcadaaaacdcbcaaaaacdcbc";
    char b[] = "cdc";

    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

    int cnt = 0;
    int index = 0;
    while ((index = kmp(a, b, index)) != -1)
    {
        index++;
        cnt++;
    }
    cout << cnt << endl;

    QueryPerformanceCounter(&t2);
    printf("Use Time:%f\n", (t2.QuadPart - t1.QuadPart) * 1.0 / tc.QuadPart);

    cout << endl
         << endl;

    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

    cout << kmp_cnt(a, b) << endl;
    QueryPerformanceCounter(&t2);
    printf("Use Time:%f\n", (t2.QuadPart - t1.QuadPart) * 1.0 / tc.QuadPart);
    return 0;
}