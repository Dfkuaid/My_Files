#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2000010;
const int MOD = 1e9 + 7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt;} e[N];

int n, m, a[N], b[N], k[N], col[N], cnt, vis[N], used[N], head[N], ecnt(2); char s[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

int fpow(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) res = 1ll * res * x % MOD;
        y >>= 1; x = 1ll * x * x % MOD;
    }
    return res;
}

int dfs(int x) {
    vis[x] = 1; int d = col[x];
    for (int i = head[x]; i; i = e[i].nxt) if (!vis[e[i].v])
      if (dfs(e[i].v)) used[i >> 1] = 1, d ^= 1;
    return d;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m); cnt = m - n - 1;
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++ i) a[i] = s[i] - '0';
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++ i) b[i] = s[i] - '0';
    for (int i = 1; i <= n + 1; ++ i)
      col[i] = a[i] ^ b[i] ^ a[i - 1] ^ b[i - 1];
    for (int i = 1; i <= m; ++ i) {
        int l, r; read(l), read(r);
        add_edge(l, r + 1), add_edge(r + 1, l);
    }
    for (int i = 1; i <= n + 1; ++ i) if (!vis[i]) {
        if (dfs(i)) {puts("0\nNO"); return 0;} else ++ cnt;
    }
    printf("%d\n", fpow(2, cnt)); puts("YES");
    for (int i = 1; i <= m; ++ i) putchar(used[i] + '0');
    return 0;
}
