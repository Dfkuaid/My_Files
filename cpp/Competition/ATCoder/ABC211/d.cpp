#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 500010;
const int MOD = 1e9 + 7;
const int INF = 0x3fffffff;

struct Edge {
    int u, v;
    int nxt;
};
Edge e[N];

int cnt = 1, head[N], n, m, d[N], sum[N], vis[N];

inline void add(const int &u, const int &v) {
    e[cnt].u = u, e[cnt].v = v;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

inline void solve() {
    queue <int> q;
    sum[1] = d[1] = 1; q.push(1);
    while (q.size()) {
        int now = q.front(); q.pop();
        if (vis[now]) continue;
        vis[now] = true;
        for (int i = head[now]; i; i = e[i].nxt)
          if (!d[e[i].v] || d[e[i].v] == d[now] + 1) {
              d[e[i].v] = d[now] + 1;
              (sum[e[i].v] += sum[now]) %= MOD;
              q.push(e[i].v);
          }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        add(u, v); add(v, u);
    }
    solve();
    printf("%d", sum[n]);
    return 0;
}