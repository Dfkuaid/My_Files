#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 300010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt;} e[N << 1];

int t, k, n, w[N], head[N], ecnt(1), f[N]; ll sum, siz[N];

vector <ll> all_siz[N];

inline void reset() {mset(head, 0); ecnt = 1, sum = 0;}

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void solve(int x, int fa, ll lmt) {
    f[x] = 0, siz[x] = 0; all_siz[x].clear();
    int cnt = 0; siz[x] = w[x];
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa) continue;
        solve(e[i].v, x, lmt); ++ cnt;
        all_siz[x].push_back(siz[e[i].v]);
        f[x] += f[e[i].v];
    }
    sort(all_siz[x].begin(), all_siz[x].end());
    for (auto k : all_siz[x]) {
        if (siz[x] + k <= lmt) siz[x] += k, -- cnt;
        else break;
    }
    f[x] += cnt;
}

inline bool check(ll x) {
    for (int i = 1; i <= n; ++ i) if (x < w[i]) return false;
    solve(1, 0, x); return f[1] <= k - 1;
}

void MAIN() {
    read(n), read(k); reset();
    for (int i = 1; i < n; ++ i) {
        int u, v; read(u), read(v);
        add_edge(u, v), add_edge(v, u);
    }
    for (int i = 1; i <= n; ++ i) read(w[i]), sum += w[i];
    ll l = 0, r = sum, res = sum;
    while (l <= r) {
        ll mid = l + r >> 1;
        if (check(mid)) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%lld\n", res);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); for (int i = 1; i <= t; ++ i) {printf("Case #%d: ", i); MAIN();} return 0;
}
