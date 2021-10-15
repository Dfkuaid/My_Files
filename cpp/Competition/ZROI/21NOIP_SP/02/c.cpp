#define LOCAL
#include <bits/stdc++.h>
#define pii pair <int, int>
#define mp(a, b) make_pair(a, b)
using namespace std;

const int N = 300010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}
template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}

struct Edge {int u, v, nxt;} e[N << 1];

int n, a, b, head[N], ecnt(2), pre[N], op = 1;
int g[N], pass[N], pcnt, f[N], gcnt, tag;

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void get_path(int x, int fa) {
    if (x == b) {op = 0; return;}
    for (int i = head[x]; i && op; i = e[i].nxt) {
        if (e[i].v == fa) continue;
        pre[e[i].v] = i, get_path(e[i].v, x);
    }
}

inline void connect() {
    get_path(a, 0); int now = b;
    while (e[pre[now]].u != a)
      pass[++ pcnt] = pre[now], now = e[pre[now]].u;
   pass[++ pcnt] = pre[now];
   reverse(pass + 1, pass + pcnt + 1);
}

inline bool cmp(int a, int b) {return a > b;}

void dp(int x, int fa) {
    f[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && i != tag && (i ^ 1) != tag)
        dp(e[i].v, x);
    gcnt = 0;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && i != tag && (i ^ 1) != tag)
        g[++ gcnt] = f[e[i].v];
    if (!gcnt) return; sort(g + 1, g + gcnt + 1, cmp);
    for (int i = 1; i <= gcnt; ++ i)
      f[x] = Max(f[x], g[i] + i);
}

inline pii solve(int x) {
    tag = pass[x]; dp(a, 0), dp(b, 0);
    return make_pair(f[a], f[b]);
}

inline bool check(pii x) {return x.first <= x.second;}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(a), read(b);
    for (int i = 1; i < n; ++ i) {
        int u, v; read(u), read(v);
        add_edge(u, v), add_edge(v, u);
    }
    connect();
    int l = 1, r = pcnt, ans = 1;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(solve(mid)))
          l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    pii ans1 = solve(ans), ans2 = mp(-INF, INF);
    if (ans + 1 <= pcnt) ans2 = solve(ans + 1);
    ans = Min(Max(ans1.first, ans1.second), Max(ans2.first, ans2.second));
    printf("%d", ans); return 0;
}
