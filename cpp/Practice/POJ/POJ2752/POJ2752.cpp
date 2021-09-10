#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

int len, nxt[N], cnt, ans[N];
char s[N];

int main() {
    while (scanf("%s", s) != EOF) {
        int p = -1; nxt[0] = -1, cnt = 0;
        len = strlen(s);
        for (int q = 0; q < len; ++ q) {
            while (~p && s[p] != s[q]) p = nxt[p];
            ++ p, nxt[q + 1] = p;
        }
        p = len;
        while (p) ans[++ cnt] = p, p = nxt[p];
        for (int i = cnt; i >= 1; -- i)
          printf("%d ", ans[i]);
        printf("\n");
    }
    return 0;
}