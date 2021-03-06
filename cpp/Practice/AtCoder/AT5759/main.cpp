#define LOCAL
#include <bits/stdc++.h>
#define ll long long 
using namespace std;

const int N = 200010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt;} e[N << 1];

int n, head[N], ecnt(1), cnt[2], p0, p1, p2, ans[N], col[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void dfs(int x, int fa, int tp) {
    col[x] = tp; ++ cnt[tp];
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa) dfs(e[i].v, x, tp ^ 1);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); p0 = 3, p1 = 1, p2 = 2;
    for (int i = 1, u, v; i < n; ++ i)
      read(u), read(v), add_edge(u, v), add_edge(v, u);
    dfs(1, 0, 0);
    if (cnt[0] > n / 3 && cnt[1] > n / 3) {
        for (int i = 1; i <= n; ++ i)
          if (col[i] && p1 <= n)
            ans[i] = p1, p1 += 3;
          else if (!col[i] && p2 <= n)
            ans[i] = p2, p2 += 3;
          else ans[i] = p0, p0 += 3;
    } else if (cnt[0] <= n / 3) {
        for (int i = 1; i <= n; ++ i)
          if (!col[i]) ans[i] = p0, p0 += 3;
          else {
              if (p1 <= n) ans[i] = p1, p1 += 3;
              else if (p2 <= n) ans[i] = p2, p2 += 3;
              else ans[i] = p0, p0 += 3;
          }
    } else {
        for (int i = 1; i <= n; ++ i)
          if (col[i]) ans[i] = p0, p0 += 3;
          else {
              if (p1 <= n) ans[i] = p1, p1 += 3;
              else if (p2 <= n) ans[i] = p2, p2 += 3;
              else ans[i] = p0, p0 += 3;
          }
    }
    for (int i = 1; i <= n; ++ i) printf("%d ", ans[i]);
    return 0;
}
