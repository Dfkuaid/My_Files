#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define lb(l, len, x) lower_bound(l + 1, l + len + 1, x)
using namespace std;

const int N = 310;
const int M = 1010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Enermy {int l, r, d;} p[N];

int t, n, pos[M], cnt, f[M][M];

inline void reset() {
    cnt = 0; memset(f, 0x3f, sizeof f);
}

inline void MAIN() {
    read(n); reset();
    for (int i = 1; i <= n; ++ i) {
        read(p[i].l), pos[++ cnt] = p[i].l;
        read(p[i].r), pos[++ cnt] = p[i].r;
        read(p[i].d);
    }
    sort(pos + 1, pos + 1 + cnt);
    cnt = unique(pos + 1, pos + 1 + cnt) - pos - 1;
    for (int i = 1; i <= n; ++ i) {
        p[i].l = lb(pos, cnt, p[i].l) - pos;
        p[i].r = lb(pos, cnt, p[i].r) - pos;
    }
    for (int x = 1; x <= cnt; ++ x)
      for (int l = 1, r = l + x - 1; r <= cnt; ++ l, ++ r) {
          int nl = 0, nr = 0, d = 0;
          for (int i = 1; i <= n; ++ i) if (l <= p[i].l && p[i].r <= r)
            if (d < p[i].d) nl = p[i].l, nr = p[i].r, d = p[i].d;
            else if (d == p[i].d) nl = min(nl, p[i].l), nr = max(nr, p[i].r);
          if (!d) {f[l][r] = 0; continue;}
          for (int i = nl; i <= nr; ++ i) {
              int val = d;
              if (i > l) val += f[l][i - 1];
              if (i < r) val += f[i + 1][r];
              f[l][r] = min(f[l][r], val);
          }
      }
    printf("%lld\n", f[1][cnt]);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) MAIN(); return 0;
}
