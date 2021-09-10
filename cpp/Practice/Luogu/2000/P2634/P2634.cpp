#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N];

int n, cnt = 1, head[N], vis[N], db[5], res;
int siz[N], mx[N], rt, sum, b[5], dist[N], dcnt;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

int gcd(int a, int b){
    if (!b) return a;
    return gcd(b, a % b);
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
    b[dist[x] % 3] ++;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v])
        dist[e[i].v] = dist[x] + e[i].w,
        calcdist(e[i].v, x);
}

void dfz(int x, int fa) {
    vis[x] = true, db[0] = db[1] = db[2] = 0, dist[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa || vis[e[i].v]) continue;
        b[0] = b[1] = b[2] = 0;
        dist[e[i].v] = e[i].w;
        calcdist(e[i].v, x);
        res += b[0] * db[0] + b[1] * db[2] + b[2] * db[1];
        db[0] += b[0], db[1] += b[1], db[2] += b[2];
    }
    res += db[0];
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa || vis[e[i].v]) continue;
        sum = siz[e[i].v], mx[rt = 0] = INF;
        calcsiz(e[i].v, x); calcsiz(rt, -1);
        dfz(rt, x);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i ++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    sum = n, mx[rt = 0] = INF;
    calcsiz(1, -1); calcsiz(rt, -1);
    dfz(rt, -1); res = res * 2 + n;
    int gd = gcd(res, n * n);
    printf("%d/%d", res / gd, n * n / gd);
    return 0;
}
