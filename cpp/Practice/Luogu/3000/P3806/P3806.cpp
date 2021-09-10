#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int MXQ = 10000010;
const int INF = 0x7fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N];

int n, m, cnt = 1, head[N], qs[N], ans[N];
int rt, sum, siz[N], mx[N], vis[N], tf[MXQ];
int dist[N], dd[N], dcnt, q[N], frt, tal;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

void calcsiz(int x, int fa) {
    siz[x] = 1, mx[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa || vis[e[i].v]) continue;
        calcsiz(e[i].v,x); siz[x] += siz[e[i].v];
        mx[x] = Max(mx[x], siz[e[i].v]);
    }
    mx[x] = Max(mx[x], sum - siz[x]);
    if (mx[x] < mx[rt]) rt = x;
}

void calcdist(int x, int fa) {
    dd[++ dcnt] = dist[x];
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v]) {
          dist[e[i].v] = dist[x] + e[i].w;
          calcdist(e[i].v, x);
      }
}

void dfz(int x, int fa) {
    frt = 0, tal = -1, q[++ tal] = 0;
    tf[0] = true, vis[x] = true;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa || vis[e[i].v]) continue;
        dist[e[i].v] = e[i].w;calcdist(e[i].v, x);
        for (int k = 1; k <= dcnt;k ++)
          for (int j = 1; j <= m;j ++)
            if (qs[j] >= dd[k]) ans[j] |= tf[qs[j] - dd[k]];
        for (int j = 1; j <= dcnt; j ++)
          if (dd[j] < MXQ) q[++ tal] = dd[j], tf[dd[j]] = true;
        dcnt = 0;
    }
    while (frt <= tal) tf[q[frt ++]] = false;
    for (int i = head[x]; i; i = e[i].nxt){
        if (e[i].v == fa || vis[e[i].v]) continue;
        sum = siz[e[i].v], mx[rt = 0] = INF;
        calcsiz(e[i].v, x); calcsiz(rt, -1);
        dfz(rt, x);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i ++) {
        int u, v, w;scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);add(v, u, w);
    }
    for (int i = 1; i <= m; i ++) scanf("%d", qs + i);
    mx[rt = 0] = INF, sum = n;
    calcsiz(1, -1); calcsiz(rt, -1);
    dfz(rt, -1);
    for (int i = 1;i <= m;i ++)
      if (ans[i]) printf("AYE\n");
      else printf("NAY\n");
    return 0;
}
