#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define pii pair<int, int>
#define mp(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 105;
const int M = 1005;
const int INF = 0x3fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[M << 1];

int n, m, l, cnt = 2, head[N], ans1, ans2, ise[N][M];
int pre[N][N], d[M][N][N], vis[N], uabd[M << 1];

priority_queue <pii > q;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

inline void clear() {
    cnt = 2, ans1 = ans2 = 0;
    mset(head, 0); mset(ise, 0);
    mset(pre, 0); mset(d, 0x3f);
    mset(vis, 0); mset(uabd, 0);
}

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

void Dijkstra(const int s,const int E) {
    mset(vis, 0);
    q.push(mp(0, s)); d[E][s][s] = 0;
    while (q.size()) {
        int now = q.top().second; q.pop();
        if (vis[now]) continue;
        vis[now] = true;
        for (int i = head[now]; i; i = e[i].nxt) {
            if (d[E][s][e[i].v] > d[E][s][now] + e[i].w) {
              if (uabd[i]) continue;
              d[E][s][e[i].v] = d[E][s][now] + e[i].w;
              if (!E) ise[s][pre[s][e[i].v] >> 1] = false, pre[s][e[i].v] = i, ise[s][i >> 1] = true;
              q.push(mp(-d[E][s][e[i].v], e[i].v));
          }
        }
          
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    while (scanf("%d%d%d", &n, &m, &l) != EOF) {
        clear();
        for (int i = 1; i <= m; i ++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w); add(v, u, w);
        }
        for (int i = 1; i <= n; i ++)
          Dijkstra(i, 0);
        for (int i = 1; i <= n; i ++)
          for (int j = 1; j <= n; j ++) {
              if (d[0][i][j] == 1061109567) continue;
              if (i == j) continue;
              uabd[pre[i][j]] = uabd[pre[i][j] ^ 1] = true;
              Dijkstra(i, pre[i][j] / 2);
              uabd[pre[i][j]] = uabd[pre[i][j] ^ 1] = false;
          }
        for (int i = 1; i <= n; i ++)
          for (int j = 1; j <= n; j ++)
            if (d[0][i][j] != 1061109567)
              ans1 += d[0][i][j];
            else ans1 += l;
        for (int k = 1; k <= m; k ++) {
            int tmp = 0;
            for (int i = 1; i <= n; i ++)
              for (int j = 1; j <= n; j ++) {
                  int len = ise[i][k] ? d[k][i][j] : d[0][i][j];
                  if (len != 1061109567) tmp += len;
                  else tmp += l;
               }
             ans2 = Max(ans2, tmp);
        }
        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}