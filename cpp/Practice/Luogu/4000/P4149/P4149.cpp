#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 2000100;
const int INF = 0x3fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N];

int n, k, head[N], cnt = 1, frt, tal, ans = INF;
int siz[N], rt, sum, mx[N], d[N << 2], ccnt, b[N << 2];
int vis[N], dist[N], ecnt[N], q[N], qc[N];

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

void calcsiz(int x, int fa) {
    siz[x] = 1, mx[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v]) {
          calcsiz(e[i].v, x);
          siz[x] += siz[e[i].v];
          mx[x] = Max(mx[x], siz[e[i].v]);
      }
    mx[x] = Max(mx[x], sum - siz[x]);
    if (mx[x] < mx[rt]) rt = x;
}

void calcdist(int x, int fa) {
    ecnt[x] = ecnt[fa] + 1;
    if (dist[x] <= 1e6 + 10) {
        qc[++ ccnt] = dist[x];
        b[dist[x]] = Min(b[dist[x]], ecnt[x]);
    }
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v]) {
          dist[e[i].v] = dist[x] + e[i].w;
          calcdist(e[i].v, x);
      }
    ecnt[x] = 0;
}

void dfz(int x, int fa) {
    frt = 0, tal = -1, d[0] = 0, vis[x] = true;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa || vis[e[i].v]) continue;
        dist[e[i].v] = e[i].w; calcdist(e[i].v, x);
        for (int j = 1; j <= ccnt; j ++) if (k >= qc[j])
          ans = Min(d[k - qc[j]] + b[qc[j]], ans);
        for (int i = 1; i <= ccnt; i ++) {
            if (qc[i] < 1e6 + 10) {
                d[qc[i]] = Min(d[qc[i]], b[qc[i]]);
                q[++ tal] = qc[i];
            } b[qc[i]] = INF;
        } ccnt = 0;
    }
    while (frt <= tal) d[q[frt ++]] = INF;
    for (int i = head[x]; i; i = e[i].nxt){
        if (e[i].v == fa || vis[e[i].v]) continue;
        sum = siz[e[i].v], mx[rt = 0] = INF;
        calcsiz(e[i].v, x); calcsiz(rt, -1);
        dfz(rt, x);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i ++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        u ++, v ++; add(u, v, w); add(v, u, w);
    }
    mx[rt = 0] = INF, sum = n;
    mset(d, 0x3f); mset(b, 0x3f);
    calcsiz(1, -1); calcsiz(rt, -1);
    dfz(rt, -1);
    if (ans <= 1e6) printf("%d", ans);
    else printf("-1");
    return 0;
}