#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define int long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int M = 20000010;
const int INF = 0x3ffffffffff;

struct Edge {int u, v, w, nxt;} e[N];
struct Query {int id, a1, b1, a2, b2;} Q[N], tmp[N];

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

int n, m, cnt = 1, head[N], d[N], ans[N];
int can[N], inq[N], q[M], frt, tal, t;

inline int id(int x, int y) {return (x - 1) * m + y;}

inline void add(int u, int v, int w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

inline void spfa(int s, int l1, int r1, int l2, int r2, int h) {
    int dx = d[s];
	for (int i = l1; i <= r1; ++ i)
      for (int j = l2; j <= r2; ++ j)
        d[id(i, j)] = h ? d[id(i, j)] + dx : INF;
    d[s] = 0, inq[s] = 1, frt = 0, tal = -1, q[++ tal] = s;
    while (frt <= tal) {
        int now = q[frt ++]; inq[now] = 0;
        for (int i = head[now]; i; i = e[i].nxt)
          if (can[e[i].v] && d[e[i].v] > d[now] + e[i].w) {
              d[e[i].v] = d[now] + e[i].w;
              if (!inq[e[i].v]) q[++ tal] = e[i].v, inq[e[i].v] = 1;
          }
    }
}

void solve(int l1, int r1, int l2, int r2, int ql, int qr) {
    if (ql > qr) return;
    if (r1 - l1 > r2 - l2) {
        int mid = l1 + r1 >> 1;
        for (int i = l1; i <= r1; ++ i)
          for (int j = l2; j <= r2; ++ j) can[id(i, j)] = 1;
        for (int i = l2; i <= r2; ++ i) {
            spfa(id(mid, i), l1, r1, l2, r2, i - l2);
            for (int j = ql; j <= qr; ++ j)
              ans[Q[j].id] = Min(ans[Q[j].id], d[id(Q[j].a1, Q[j].b1)] + d[id(Q[j].a2, Q[j].b2)]);
        }
        for (int i = l1; i <= r1; ++ i)
          for (int j = l2; j <= r2; ++ j)
            can[id(i, j)] = d[id(i, j)] = 0;
        int l = ql - 1, r = qr + 1;
        for (int i = ql; i <= qr; ++ i)
          if (Q[i].a1 < mid && Q[i].a2 < mid) tmp[++ l] = Q[i];
          else if (Q[i].a1 > mid && Q[i].a2 > mid) tmp[-- r] = Q[i];
        for (int i = ql; i <= l; ++ i) Q[i] = tmp[i];
        for (int i = qr; i >= r; -- i) Q[i] = tmp[i];
        solve(l1, mid - 1, l2, r2, ql, l);
        solve(mid + 1, r1, l2, r2, r, qr);
    } else {
        int mid = l2 + r2 >> 1;
        for (int i = l1; i <= r1; ++ i)
          for (int j = l2; j <= r2; ++ j) can[id(i, j)] = 1;
        for (int i = l1; i <= r1; ++ i) {
            spfa(id(i, mid), l1, r1, l2, r2, i - l1);
            for (int j = ql; j <= qr; ++ j)
              ans[Q[j].id] = Min(ans[Q[j].id], d[id(Q[j].a1, Q[j].b1)] + d[id(Q[j].a2, Q[j].b2)]);
        }
        for (int i = l1; i <= r1; ++ i)
          for (int j = l2; j <= r2; ++ j)
            can[id(i, j)] = d[id(i, j)] = 0;
        int l = ql - 1, r = qr + 1;
        for (int i = ql; i <= qr; ++ i)
          if (Q[i].b1 < mid && Q[i].b2 < mid) tmp[++ l] = Q[i];
          else if (Q[i].b1 > mid && Q[i].b2 > mid) tmp[-- r] = Q[i];
        for (int i = ql; i <= l; ++ i) Q[i] = tmp[i];
        for (int i = qr; i >= r; -- i) Q[i] = tmp[i];
        solve(l1, r1, l2, mid - 1, ql, l);
        solve(l1, r1, mid + 1, r2, r, qr);
    }
}

signed main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    mset(ans, 0x3f);
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++ i) 
      for (int j = 1; j < m; ++ j) {
          int w; scanf("%lld", &w);
          add(id(i, j), id(i, j + 1), w);
          add(id(i, j + 1), id(i, j), w);
      }
    for (int i = 1; i < n; ++ i)
      for (int j = 1; j <= m; ++ j) {
          int w; scanf("%lld", &w);
          add(id(i, j), id(i + 1, j), w);
          add(id(i + 1, j), id(i, j), w);
      }
    scanf("%d", &t);
    for (int i = 1; i <= t; ++ i) {
        int a1, b1, a2, b2;
        scanf("%lld%lld%lld%lld", &a1, &b1, &a2, &b2);
        Q[i].a1 = a1, Q[i].b1 = b1;
        Q[i].a2 = a2, Q[i].b2 = b2; Q[i].id = i;
    }
    solve(1, n, 1, m, 1, t);
    for (int i = 1; i <= t; ++ i)
      printf("%lld\n", ans[i]);
    return 0;
}