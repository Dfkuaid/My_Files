#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3f3f3f3f;

struct Edge {
    int u, v;
    int c, w;
    int nxt;
};
Edge e[N];

int n, m, s, t, cnt = 2, head[N];
int dist[N], inq[N], pre[N];
int q[N], frt, tal, maxflow, res;

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

inline void add(int u, int v, int w, int c) {
    e[cnt].u = u, e[cnt].v = v;
    e[cnt].w = w, e[cnt].c = c;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

bool SPFA() {
    mset(dist, 0x3f); mset(inq, 0);
    mset(pre, 0); frt = 0, tal = -1;
    q[++ tal] = s, inq[s] = 1, dist[s] = 0;
    while (frt <= tal) {
        int now = q[frt ++]; inq[now] = 0;
        for (int i = head[now]; i; i = e[i].nxt)
          if (e[i].w && dist[e[i].v] > dist[now] + e[i].c) {
              dist[e[i].v] = dist[now] + e[i].c;
              pre[e[i].v] = i;
              if (!inq[e[i].v]) {
                  inq[e[i].v] = true,
                  q[++ tal] = e[i].v;
              }
          }
    }
    return dist[t] != INF;
}

void update() {
    int flow = INF, i;
    for (int u = t; u != s; u = e[i ^ 1].v)
      i = pre[u], flow = Min(flow, e[i].w);
    for(int u = t; u != s; u = e[i ^ 1].v) {
		i = pre[u], e[i].w -= flow;
        e[i ^ 1].w += flow;
		res += e[i].c * flow;
	}
	maxflow += flow;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; i ++) {
        int u, v, w, c;
        scanf("%d%d%d%d", &u, &v, &w, &c);
        add(u, v, w, c); add(v, u, 0, -c);
    }
    while (SPFA()) update();
    printf("%d %d", maxflow, res);
    return 0;
}