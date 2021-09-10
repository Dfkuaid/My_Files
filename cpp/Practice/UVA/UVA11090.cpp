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
    int u, v;
    double w;
    int nxt;
};
Edge e[N];

int n, m, cnt = 1, head[N], tot[N];
int q[N], frt, tal, T, inq[N], mx;
double d[N];

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

inline void clear() {
    cnt = 1, tal = -1, frt = mx = 0;
    mset(tot, 0); mset(head, 0);
}

inline void add(int u, int v, double w) {
    e[cnt].u = n, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

bool check_ring() {
    frt = 0, tal = -1;
    mset(inq, 0); mset(tot, 0);
    for (int i = 1; i <= n; i ++)
      d[i] = 0, q[++ tal] = i;
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
    return false;
}

bool check(double x) {
    for (int i = 1; i <= m; i ++) e[i].w -= x;
    bool res = check_ring();
    for (int i = 1; i <= m; i ++) e[i].w += x;
    return res;
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    scanf("%d", &T);
    for (int t = 1; t <= T; t ++) {
        scanf("%d%d", &n, &m); clear();
        for (int i = 1; i <= m; i ++) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            add(u, v, (double)w); mx = Max(mx, w);
        }
        printf("Case #%d: ", t);
        if (!check(mx + 1)) printf("No cycle found.\n");
        else {
            double l = 0, r = mx, ans = 0;
            while (r - l > 1e-3) {
                double mid = (l + r) / 2;
                if (check(mid)) ans = mid, r = mid - 1e-12;
                else ans = mid, l = mid + 1e-12;
            }
            printf("%.2lf\n", ans);
        }
    }
    return 0;
}