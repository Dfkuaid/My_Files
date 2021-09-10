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
Edge e[N], ne[N];

int n, m, cnt, ncnt, head[N], nhead[N];
int inq[N], q[N], frt, tal, tot[N];
ll d[N];

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

bool check_ring(int x) {
    inq[x] = true;
    for (int i = head[x]; i; i = e[i].nxt)
      if (d[e[i].v] > d[x] + e[i].w) {
          d[e[i].v] = d[x] + e[i].w;
          if (inq[e[i].v] || check_ring(e[i].v))
            return true;
      }
    inq[x] = false;
    return false;
}

bool check(ll x) {
    mset(d, 0x3f); mset(inq, 0);
    d[0] = 0, inq[0] = 1;
    for (int i = 1; i <= m; i ++) e[i].w -= x;
    bool res = check_ring(0);
    for (int i = 1; i <= m; i ++) e[i].w += x;
    return res;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        cnt = 1; mset(head, 0);
        for (int i = 1; i <= m; i ++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w);
        }
        for (int i = 1; i <= n; i ++) add(0, i, 0);
        int l = 0, r = 1e9;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (check(mid)) r = mid - 1;
            else l = mid;
        }
        if (l == 0) printf("No Solution\n");
        else if (l >= 1e7) printf("Infinite\n");
        else printf("%d\n", l);
    }
    return 0;
}