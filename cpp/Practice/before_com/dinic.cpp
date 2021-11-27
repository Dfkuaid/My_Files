#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 200010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt; ll w;} e[N];

int head[N], ecnt(2), n, m, s, t, d[N], now[N]; ll maxflow;

queue <int> q;

inline void add_edge(int u, int v, ll w) {
    e[ecnt].u = u, e[ecnt].v = v, e[ecnt].w = w;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;

    e[ecnt].u = v, e[ecnt].v = u, e[ecnt].w = 0;
    e[ecnt].nxt = head[v], head[v] = ecnt ++;
}

ll dinic(int x, ll flow) {
    if (x == t) return flow; ll rst = flow;
    for (int i = now[x]; i && rst; i = e[i].nxt) {
        if (d[e[i].v] == d[x] + 1 && e[i].w) {
            ll k = dinic(e[i].v, min(e[i].w, rst));
            if (!k) d[e[i].v] = 0;
            rst -= k; e[i].w -= k; e[i ^ 1].w += k;
        }
        now[x] = i;
    }
    return flow - rst;
}

inline bool bfs() {
    mset(d, 0); while (q.size()) q.pop();
    d[s] = 1; now[s] = head[s]; q.push(s);
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int i = head[x]; i; i = e[i].nxt)
          if (!d[e[i].v] && e[i].w) {
              d[e[i].v] = d[x] + 1;
              now[e[i].v] = head[e[i].v];
              q.push(e[i].v);
              if (e[i].v == t) return true;
          }
    }
    return false;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m), read(s), read(t); ll flow = 0;
    for (int i = 1; i <= m; ++ i) {
        int u, v; ll w; read(u), read(v);
        read(w), add_edge(u, v, w);
    }
    while (bfs()) while (flow = dinic(s, INF)) maxflow += flow;
    printf("%lld", maxflow); return 0;
}