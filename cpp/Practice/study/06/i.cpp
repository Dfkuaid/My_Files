#define LOCAL
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

const int N = 200010;
const ll INF = 1e18;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Abs(T x) {return x < 0 ? -x : x;}
template <typename T> inline T Min(T x, T y) {return x < y ? x : y;}

struct Edge {int u, v, nxt;} e[N << 1];

int T, n, m, head[N], icnt[N], ecnt; ll siz[N], w[N], ans, sum;

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v; ++ icnt[v];
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void solve(int x, int fa) {
    siz[x] = w[x];
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa) continue;
        solve(e[i].v, x), siz[x] += siz[e[i].v];
    }
    ans = Min(ans, Abs(sum - siz[x] - siz[x]));
}

void MAIN() {
    memset(icnt, 0, sizeof icnt); ans = INF, sum = 0;
    memset(head, 0, sizeof head); ecnt = 1;
    for (int i = 1; i <= n; ++ i) read(w[i]), sum += w[i];
    for (int i = 1, x = 0, y = 0; i <= m; ++ i)
      read(x), read(y), add_edge(y, x), add_edge(x, y);
    solve(1, 0); printf("Case %d: %lld\n", ++ T, ans);
    read(n), read(m);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m); while (n || m) MAIN(); return 0;
}
