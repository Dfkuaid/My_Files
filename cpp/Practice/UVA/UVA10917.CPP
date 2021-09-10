#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define pii pair<int, int>
#define ll long long
#define mp(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x7fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N], ne[N];

int cnt = 1, ncnt = 1, head[N], nhead[N];
int dist[N], vis[N], tot[N], s, t, icnt[N];
int qx[N], frt, tal, tag[N], n, m;

priority_queue <pii > q;

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

inline void addn(const int &u, const int &v) {
    ne[ncnt].u = u, ne[ncnt].v = v, icnt[v] ++;
    ne[ncnt].nxt = nhead[u], nhead[u] = ncnt ++;
}

void Dijkstra() {
    mset(dist, 0x3f);
    q.push(mp(0,2)); dist[2] = 0;
    while (q.size()) {
        int now = q.top().second; q.pop();
        if (vis[now]) continue; vis[now] = true;
        for (int i = head[now]; i; i = e[i].nxt)
          if (dist[e[i].v] > dist[now] + e[i].w) {
              dist[e[i].v] = dist[now] + e[i].w;
              q.push(mp(-dist[e[i].v], e[i].v));
          }
    }
}

inline void clear() {
    frt = 0, tal = -1; 
    ncnt = cnt = 1; mset(tot, 0);
    mset(icnt, 0); mset(tag, 0);
    mset(vis, 0); mset(dist, 0x3f);
    mset(head, 0); mset(nhead, 0);
}

void topo() {
    
    for (int i = 1; i <= n; i ++) 
      if (!icnt[i] || i == 1) qx[++ tal] = i;
    tag[1] = tot[1] = vis[1] = 1;
    while (frt <= tal) {
        int now = qx[frt ++];
        for (int i = nhead[now]; i;i = ne[i].nxt) {
            icnt[ne[i].v] --;
            if (tag[now]) {
                tot[ne[i].v] += tot[now], 
                tag[ne[i].v] |= tag[now];
            }
            if (!icnt[ne[i].v] && !vis[ne[i].v]) {
                qx[++ tal] = ne[i].v;
                vis[ne[i].v] == true;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    while (n) {
        scanf("%d", &m); s = 1, t = 2; clear();
        for (int i = 1; i <= m; i ++) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            add(u, v, w); add(v, u, w);
        }
        Dijkstra();
        for (int i = 1; i <= n; i ++)
          for (int j = head[i]; j; j = e[j].nxt)
            if (dist[i] > dist[e[j].v])
              addn(i, e[j].v);
        mset(vis, 0); topo();
        printf("%d\n", tot[t]);
        scanf("%d", &n);
    }
    return 0;
}
