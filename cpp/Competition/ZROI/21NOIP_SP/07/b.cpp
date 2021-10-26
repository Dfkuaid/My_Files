#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 500010;
const ll MOD = 1e9 + 7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt;} e[N << 2];

int n, head[N], ecnt(1), K;

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

int son[N], mxd[N], *dp[N], buf[N << 3];

void dfs(int x, int fa) {
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa) continue; dfs(e[i].v, x);
        if (mxd[e[i].v] > mxd[son[x]]) son[x] = e[i].v;
    }
    mxd[x] = mxd[son[x]] + 1;
}

int *p = buf; ll cnt = 0;

void DP(int x, int fa) {
    dp[x] = p++; dp[x][0] = 1;
    if (son[x]) DP(son[x], x);
    if (mxd[x] > K) (cnt += dp[x][K]) %= MOD;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa || e[i].v == son[x]) continue;
        DP(e[i].v, x);
        for (int j = max(0, K - mxd[x]); j < mxd[e[i].v] && j < K; ++j)
          (cnt += 1ll * dp[e[i].v][j] * dp[x][K - j - 1]) %= MOD;
        for (int j = 1; j <= mxd[e[i].v]; ++j)
          dp[x][j] = (dp[x][j] + dp[e[i].v][j - 1]) % MOD;
	}
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(K);
    for (int i = 1; i < n; ++ i) {
        int u, v; read(u), read(v);
        add_edge(u, v), add_edge(v, u);
    }
    dfs(1, 0), DP(1, 0);
    printf("%lld", cnt * (1ll * (K + 1) * K / 2 % MOD) % MOD);
    return 0;
}
