#include <cmath>
#include <iostream>
#include <string>
using namespace std;
bool isChar(char c)
{
    if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c >= '0' && c <= '9')
        return true;
    else
        return false;
}
int main()
{
    int t;
    cin >> t;
    string str;
    getline(cin, str);
    while (t--)
    {
        getline(cin, str);
        int index;
        for (index = str.length() - 1; index >= 0; index--)
        {
            if (isChar(str[index]))
            {
                break;
            }
        }
        cout << (index != -1 ? str.substr(0, index + 1)+"\n" : "\n");
    }
    return 0;
}