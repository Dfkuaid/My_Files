#define LOCAL
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
#define ll long long
#define lb(l, len, x) lower_bound(l + 1, l + len + 1, x)
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

char s1[N], s2[N], c[N]; int n, m, id[N], p, q[N], stk[N], stp;

bool cmp(int x, int y) {return s1[x] != s1[y] ? s1[x] < s1[y] : x > y;}

inline void reset() {p = stp = 0;}

void MAIN() {
    n = strlen(s1 + 1), m = strlen(s2 + 1);
    for (int i = 1; i <= n; ++ i) id[i] = i;
    sort(id + 1, id + n + 1, cmp);
    for (int i = 1; i <= n; ++ i) c[i] = s1[id[i]];
    for (int i = 1; i <= m; ++ i) {
        int k = lb(c, n, s2[i]) - c;
        while (k <= n && c[k] == s2[i])
          q[++ p] = id[k], k ++;
    }
    for (int i = 1; i <= p; ++ i)
      if (!stp || q[i] > stk[stp]) stk[++ stp] = q[i];
      else stk[lb(stk, stp, q[i]) - stk] = q[i];
    printf("%d\n", stp); reset();
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while (~scanf("%s%s", s1 + 1, s2 + 1)) MAIN(); return 0;
}
