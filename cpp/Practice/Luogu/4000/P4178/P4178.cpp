#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x7fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N];

int n, m, cnt = 1, head[N], dd[N], dcnt, res;
int siz[N], mx[N], rt, sum, vis[N], dist[N];
int q[N], frt, tal, b[N], subt[N], scnt[N];

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

inline int cmp(const int &a, const int &b) {
    return dist[a] < dist[b];
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
    if (fa != rt) b[x] = b[fa];
    else b[x] = x;
    subt[++ dcnt] = x, scnt[b[x]] ++;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v])
        dist[e[i].v] = dist[x] + e[i].w,
        calcdist(e[i].v, x);
}

void dfz(int x, int fa) {
    subt[++ dcnt] = x, b[x] = x, dist[x] = scnt[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v]) {
          dist[e[i].v] = e[i].w;scnt[e[i].v] = 0;
          calcdist(e[i].v, x);
      }
    sort(subt + 1, subt + dcnt + 1, cmp);
    int l = 1, r = dcnt; vis[x] = true;
    while (l < r) {
        while (dist[subt[l]] + dist[subt[r]] > m)
          scnt[b[subt[r]]] --, r --;
        res += r - l - scnt[b[subt[l]]];
        l ++, scnt[b[subt[l]]] --;
    }
    dcnt = 0;
    for (int i = head[x]; i;i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v]){
          sum = siz[e[i].v], mx[rt = 0] = INF;
          calcsiz(e[i].v, x); calcsiz(rt, -1);
          dfz(rt, x);
      }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i ++) {
        int u, v, w;scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    mx[rt = 0] = INF, sum = n;
    calcsiz(1, -1); calcsiz(rt, -1);
    scanf("%d", &m); dfz(rt, -1);
    printf("%d", res);
    return 0;
}
