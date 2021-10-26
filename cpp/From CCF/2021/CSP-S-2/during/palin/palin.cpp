#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 500010;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int t, n, a[N], b[N], ans;

inline void print(int x) {
    for (int i = n; i >= 1; -- i)
      if ((x >> i - 1) & 1) putchar('R');
      else putchar('L');
    putchar('\n');
}

int main() {
    freopen("palin.in", "r", stdin);
    freopen("palin.out", "w", stdout);
    read(t);
    while (t --) {
        read(n); n <<= 1; ans = -1;
        for (int i = 1; i <= n; ++ i) read(a[i]);
        for (ll i = 0; i < 1ll << n; ++ i) {
            int l = 1, r = n, op = 1;
            for (int j = n; j >= 1; -- j)
              if ((i >> j - 1) & 1) b[j] = a[r --];
              else b[j] = a[l ++];
            for (int j = n >> 1; j >= 1; -- j)
              if (b[j] != b[n - j + 1]) {
                  op = 0; break;
              }
            if (op) {ans = i; break;}
        }
        if (~ans) print(ans);
        else printf("-1\n");
    }
    return 0;
}


