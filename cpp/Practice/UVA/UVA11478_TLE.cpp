/*Bellman-Ford TLE*/
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
int d[N];

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

bool check_ring() {
    frt = 0, tal = -1;
    for (int i = 1; i <= n; i ++)
      d[i] = inq[i] = 0, q[++ tal] = i;
    while (frt <= tal) {
        int now = q[frt ++]; inq[now] = false;
        for (int i = head[now]; i; i = e[i].nxt)
          if (d[now] + e[i].w < d[e[i].v]) {
              d[e[i].v] = d[now] + e[i].w;
              if (!inq[e[i].v]) {
                  q[++ tal] = e[i].v, inq[e[i].v] = true;
                  if (++ tot[e[i].v] > n) return true;
              }
          }     
    }
    // for (int i = 1; i <= n; i ++) printf("tot[%d]: %d\n", i, tot[i]);
    return false;
}

bool check(int x) {
    // printf("CHECK: %d\n", x);
    for (int i = 1; i <= m; i ++) e[i].w -= x;
    // for (int i = 1; i <= m; i ++)
    //   printf("%d -> %d : %d\n", e[i].u, e[i].v, e[i].w);
    bool res = check_ring();
    for (int i = 1; i <= m; i ++) e[i].w += x, tot[i] = 0;
    return res;
}

int main() {
    // freopen("out.txt", "w", stdout);
    while (scanf("%d%d", &n, &m) != EOF) {
        cnt = 1; mset(head, 0);
        for (int i = 1; i <= m; i ++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add(v, u, w);
        }
        for (int i = 1; i <= n; i ++)
          add(0, i, 0);
        int l = 0, r = 1e6, ans = 0;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (check(mid)) r = mid - 1;
            else l = mid;
        }
        if (ans == 0) printf("No Solution\n");
        else if (ans >= 5e5) printf("Infinite\n");
        else printf("%d\n", ans);
    }
    return 0;
}