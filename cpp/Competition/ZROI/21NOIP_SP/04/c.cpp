#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const ll MOD = 998244353;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, fa[N], t[N], vis[N], lst[N], inc[N];
ll p[N], q[N], f[N], part1[N], g[N], m[N];

vector <int> trees[N];

inline ll fpow(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) (res *= x) %= MOD;
        y >>= 1, (x *= x) %= MOD;
    }
    return res;
}

inline int find(int x) {while (x != fa[x]) x = fa[x] = fa[fa[x]]; return x;}

int que[N], frt, tal;

void solve(vector <int> &tree) {
    /*Get the ring on the tree.*/
    int now = tree[0];
    while (!vis[now]) vis[now] = true, now = t[now];
    vector <int> ring(0); int nnow = now;
    do {
        ring.push_back(nnow);
        inc[nnow] = true; nnow = t[nnow];
    } while (nnow != now);
    for (int i = 0; i < ring.size(); ++ i) {
        int j = (i + 1) % ring.size();
        lst[ring[j]] = ring[i];
    }
    /*Use queue to run DP on the tree.*/
    for (auto u : tree) vis[u] = false;
    for (auto u : tree) ++ vis[t[u]];
    frt = 0; tal = -1; for (auto u : tree) f[u] = 1;
    for (auto u : tree) if (!vis[u]) que[++ tal] = u;
    while (frt <= tal) {
        int x = que[frt ++];
        if (!inc[t[x]] && !(-- vis[t[x]])) que[++ tal] = t[x];
        f[x] = f[x] * (MOD + 1 - p[x]) % MOD;
        f[x] = (MOD + 1 - f[x]) % MOD;
        (f[t[x]] *= (MOD + 1 - q[x] * f[x] % MOD)) %= MOD;
    }
    for (auto u : ring) {
        f[u] = f[u] * (MOD + 1 - p[u]) % MOD;
        (f[u] = MOD + 1 - f[u]) %= MOD;
    } 
    /*Calculate the answers on the ring.*/
    ll M = 1;
    for (auto u : ring) {
        m[u] = (MOD + 1 - f[u]) * q[lst[u]] % MOD,
        (M *= m[u]) %= MOD;
    }	
    now = ring[0]; ll ans0 = 0, tim = 1;
    do {
        (ans0 += tim * f[now]) %= MOD;
        tim = tim * m[now] % MOD; now = lst[now];
    } while(now != ring[0]);
    for (auto u : ring) {
        g[u] = ans0; ans0 = ans0 * m[t[u]] % MOD;
        ans0 = ans0 - M * f[t[u]] + f[t[u]];
        ans0 = ((ans0 % MOD) + MOD) % MOD;
    }
    for (auto u : ring) f[u] = g[u];
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) fa[i] = i;
    for (int i = 1, a, b; i <= n; ++ i) {
        read(a), read(b);
        p[i] = 1ll * a * fpow(b, MOD - 2) % MOD;
    }
    for (int i = 1; i <= n; ++ i) read(t[i]);
    for (int i = 1, a, b; i <= n; ++ i) {
        read(a), read(b);
        q[i] = 1ll * a * fpow(b, MOD - 2) % MOD;
    }
    for (int i = 1; i <= n; ++ i)
      if (find(i) != find(t[i]))
        fa[fa[i]] = fa[t[i]];
    for (int i = 1; i <= n; ++ i)
      trees[find(i)].push_back(i);
    for (int i = 1; i <= n; ++ i)
      if (trees[i].size()) solve(trees[i]);
    for (int i = 1; i <= n; ++ i)
      printf("%lld ", f[i]);
    return 0;
}
