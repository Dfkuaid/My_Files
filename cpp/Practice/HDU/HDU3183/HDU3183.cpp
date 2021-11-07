#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, m, mn[10][N], lg[N]; char s[N], ans[N];

inline int MIN(int x, int y) {return s[x] <= s[y] ? x : y;}

inline int query(int l, int r) {
    int k = lg[r - l + 1];
    return MIN(mn[k][l], mn[k][r - (1 << k) + 1]);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    for (int i = 2; i <= 1000; ++ i) lg[i] = lg[i >> 1] + 1;
    while (~scanf("%s%d", s + 1, &m)) {
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++ i) mn[0][i] = i;
        for (int i = 1; i <= lg[n]; ++ i)
          for (int j = 1; j + (1 << i) - 1 <= n; ++ j)
            mn[i][j] = MIN(mn[i - 1][j], mn[i - 1][j + (1 << i - 1)]);
        int pos = 1, apos = 1, st = 1;
        for (int i = n - m - 1; ~i; -- i) {
            pos = query(pos, n - i);
            ans[apos] = s[pos ++], apos ++;
        }
        for (st = 1; st < apos && ans[st] == '0'; ++ st) ;
        if (st >= apos) {puts("0"); continue;}
        for (int i = st; i < apos; ++ i) putchar(ans[i]); puts("");
    }
    return 0;
}
