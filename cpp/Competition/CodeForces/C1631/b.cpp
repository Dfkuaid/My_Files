#include <bits/stdc++.h>
using namespace std;

const int N = 300010;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int t, n, a[N], f[N][20], lg2[N], g[N][20];

inline void MAIN() {
    read(n); int len = 1, flag = 1, ans = 0;
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = n - 1; i; -- i)
      if (a[i] == a[n]) ++ len; else break;
    if (len == n) {printf("%d\n", 0); return;}
    while (true) {
        flag = 1;
        for (int i = 1; i <= n - len; ++ i)
          if (a[i] != a[n]) {flag = 0; break;}
        if (flag) break; else ++ ans, len <<= 1;
        for (int i = n - len; i > 0; -- i)
          if (a[i] == a[n]) ++ len; else break;
    }
    printf("%d\n", ans);
}

int main() {
    read(t); while (t --) MAIN(); return (0 - 0);
}
