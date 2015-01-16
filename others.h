#include <iostream>
int *getNext(char * s)
{
    int n = strlen(s);
    int * p = (int *)malloc(sizeof(int)*(n+1));
    memset(p, 0, sizeof(int)*(n+1));
    p[0] = -1;
    for (int i = 1; i < n; ++i)
    {
        int tmp = p[i-1];
        while (tmp >= 0 && s[tmp] != s[i-1])
            tmp = p[tmp];
        p[i] = tmp+1;
    }
    return p;
}
int KMP(char * p, char * s) // p is main string, s is pattern string
{
    int pos1 = 0, pos2 = 0;
    int ans = -1;
    int * ne = getNext(s);
    while (p[pos1])
    {
        if (!s[pos2])
        {
            ans = pos1 - pos2;
            break;
        }
        if (p[pos1] == s[pos2])
        {
            pos1++; pos2++;
        }
        else if (pos2 == 0)
            pos1++;
        else
            pos2 = ne[pos2];
    }
    return ans; 
    // index of return value starts from 0. -1 for not found.
}
