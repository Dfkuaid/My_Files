#define LOCAL
#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T abs(T &x) {return x < 0 ? -x : x;}
template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}
template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}

struct Edge {int u, v, nxt;} e[N];

int n, head[N], ecnt(1), siz[N], ans = INF;

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

inline int calc(int x, int y, int z) {
    return Max(x, Max(y, z)) - Min(x, Min(y, z));
}

void get_size(int x, int f) {
    siz[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == f) continue;
        get_size(e[i].v, x);
        siz[x] += siz[e[i].v];
    }
}

set <int> lineal, colla, neg_lineal, neg_colla;

void solve(int x, int f) {
    if (!lineal.empty()) {
        int pos = *lineal.lower_bound((n + siz[x]) / 2);
        ans = Min(ans, calc(n - pos, siz[x], pos - siz[x]));
    }
    if (!colla.empty()) {
        int pos = *colla.lower_bound((n - siz[x]) / 2);
        ans = Min(ans, calc(siz[x], pos, n - siz[x] - pos));
    }
    if (!neg_lineal.empty()) {
        int pos = -(*neg_lineal.lower_bound(-(n + siz[x]) / 2));
        ans = Min(ans, calc(n - pos, siz[x], pos - siz[x]));
    }
    if (!neg_colla.empty()) {
        int pos = -(*neg_colla.lower_bound(-(n - siz[x]) / 2));
        ans = Min(ans, calc(siz[x], pos, n - siz[x] - pos));
    }
    lineal.insert(siz[x]); neg_lineal.insert(-siz[x]);
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != f) solve(e[i].v, x);
    lineal.erase(siz[x]); neg_lineal.erase(-siz[x]);
    colla.insert(siz[x]); neg_colla.insert(-siz[x]);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i < n; ++ i) {
        int u, v; read(u), read(v);
        add_edge(u, v); add_edge(v, u);
    }
    get_size(1, 0); solve(1, 0);
    printf("%d", ans); return 0;
}
