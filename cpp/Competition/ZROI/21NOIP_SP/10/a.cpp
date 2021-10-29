#define LOCAL
#include <bits/stdc++.h>
#define dd double
#define ll long long
#define pdi pair <double, int>
#define mp(a, b) make_pair(a, b)
using namespace std;

const int N = 100010;
const int M = 500010;
const int INF = 0x3f3f3f3f;
const dd eps = 1e-7;

template<typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (;!isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (;isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct edge {int u, v, nxt, w;} e[M << 1];

int head[N], ecnt(1);
int C, I, T, n, m;

dd d[N], TimeLimit[N];
bool vis[N];

inline void add_edge(int u, int v, int w) {
    e[ecnt].u = u, e[ecnt].v = v, e[ecnt].w = w;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

inline void init() {
    read(n); read(m);
    for (int i = 1; i <= m; ++ i) {
        int u, v, w; read(u), read(v), read(w);
        add_edge(u, v, w); add_edge(v, u, w);
    }
    read(C); read(I); read(T);
    fill(TimeLimit + 1, TimeLimit + n + 1, INF);
}

dd l = 0, r = 10000001;

priority_queue <pdi > q;

inline void dijkstra(int s, dd v) {
    fill(d + 1, d + n + 1, INF);
    fill(vis + 1, vis + n + 1, 0);
    if (TimeLimit[s] <= 0) return;
    q.push(mp(0, s)); d[s] = 0;
    while (q.size()) {
        int now = q.top().second; q.pop();
        if (vis[now]) continue; vis[now] = 1;
        for (int i = head[now]; i; i = e[i].nxt) {
            dd w = (dd)e[i].w / v;
            if (d[e[i].v] <= d[now] + w) continue;
            if (TimeLimit[e[i].v] <= d[now] + w) continue;
            d[e[i].v] = d[now] + w; 
            q.push(mp(-d[e[i].v], e[i].v));
        }
    }
}

inline bool Check(dd mid) {
    dijkstra(C, mid); return d[T] != INF;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    init(); dijkstra(I, 1);
    for (int i = 1; i <= n; ++ i) TimeLimit[i] = d[i];
    while (r - l > eps) {
        dd mid = (l + r) / 2;
        if (Check(mid)) r = mid;
        else l = mid;
    }
    if (l >= 10000000) {return puts("-1"), 0;}
    else printf("%lf", l);
    return 0;
}
