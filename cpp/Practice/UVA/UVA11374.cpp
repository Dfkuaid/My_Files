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

const int N = 100010;
const int INF = 0x3fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N], bus[N];

int n, s, t, m, k, cnt = 1, head[N], pre[N][3], use1;
int ans, bcnt = 1, dist[N][3], vis[N], use, st, ho;

priority_queue <pii > q;

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

void Dijkstra(int u, bool opt) {
    dist[u][opt] = 0; mset(vis, 0);
    q.push(mp(0, u));
    while (q.size()) {
        int now = q.top().second; q.pop();
        if (vis[now]) continue;
        vis[now] = true;
        for (int i = head[now]; i; i = e[i].nxt)
          if (dist[e[i].v][opt] > dist[now][opt] + e[i].w) {
              dist[e[i].v][opt] = dist[now][opt] + e[i].w;
              pre[e[i].v][opt] = now;
              q.push(mp(-dist[e[i].v][opt], e[i].v));
          }
    }
}

void print_1(int f, int x) {
    if (pre[x][0]) print_1(f + 1, pre[x][0]);
    printf("%d", x);
    if (f) cout << " ";
}

void print_2(int f, int x) {
    if (!f) cout << " ";
    printf("%d", x);
    if (pre[x][1]) {
        printf(" ");
        print_2(f + 1,pre[x][1]);
    }
}

int main() {
//    freopen("out.txt", "w", stdout);
    while (cin >> n >> s >> t) {
        cnt = bcnt = 1, st = use = use1 = 0;
        scanf("%d", &m); mset(head, 0);
        for (int i = 1; i <= m; i ++){
            int x, y, z; scanf("%d%d%d", &x, &y, &z);
            add(x, y, z); add(y, x, z);
        }
//        for (int i = 1; i < cnt; i ++) {
//            printf("%d: %d -> %d : %d, nxt:%d\n", i, e[i].u, e[i].v, e[i].w, e[i].nxt);
//        }
        mset(dist, 0x3f); mset(pre, 0);
        Dijkstra(s, 0); Dijkstra(t, 1);
        ans = dist[t][0];
        scanf("%d", &k);
        for (int i = 1; i <= k; i ++) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            bus[++ bcnt].u = u, bus[bcnt].v = v, bus[bcnt].w = w;
            bus[++ bcnt].u = v, bus[bcnt].v = u, bus[bcnt].w = w;
            if (dist[u][0] + dist[v][1] + w < ans)
              ans = dist[u][0] + dist[v][1] + w,
              use = i, use1 = bcnt - 1, st = u;
            if (dist[v][0] + dist[u][1] + w < ans)
              ans = dist[v][0] + dist[u][1] + w,
              use = i, st = v, use1 = bcnt;
        }
        if (ho) puts("");
        else ho = true;
        if (!use) {
            print_1(0, t);
            printf("\nTicket Not Used\n%d", ans);
        } else {
            print_1(0, bus[use1].u); print_2(0, bus[use1].v);
            printf("\n%d\n%d", st, ans);
        }
        puts("");
    }
    return 0;
}
