#include <iostream>
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define plli pair<long long, int>
#define mp(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

struct Edge {
    int u, v;
    int nxt;
};
Edge e[N];

int n, s, t, cs;
int cnt, head[N], vis[N], pre[N];
ll p, d[N];

priority_queue <plli > q;

inline void clear() {
    cnt = 1;
    mset(pre, 0); mset(head, 0); 
    mset(d, 0x3f); mset(vis, 0);
}

inline void add(int u, int v) {
    e[cnt].u = u, e[cnt].v = v;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

ll calc(int x, ll y) {
    if (x >= (int)'a' && x <= (int)'z') return y + 1;
    return y + ceil(y / 19.0);
}

void solve() {
    d[t] = (t == s) ? p : calc(t, p); q.push(mp(-d[t], t));
    while (q.size()) {
        int now = q.top().second; q.pop();
        if (vis[now]) continue;
        vis[now] = true;
        for (int i = head[now]; i; i = e[i].nxt) {
            ll cst = (e[i].v != s) ? calc(e[i].v, d[now]) : d[now];
            if (cst <= d[e[i].v]) {
                if (d[e[i].v] > cst || pre[e[i].v] > now)
                  pre[e[i].v] = now;
                d[e[i].v] = cst;
                q.push(mp(-d[e[i].v], e[i].v));
            }
        }
    }
}

void path(int x) {
    printf("%c", (char)x);
    if (pre[x]) {
        putchar('-'); path(pre[x]);
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        if (n == -1) break;
        clear(); ++ cs;
        for (int i = 1; i <= n; ++ i) {
            char u, v; cin >> u >> v;
            add((int)u, (int)v);
            add((int)v, (int)u);
        } 
        char a, b; cin >> p >> a >> b;
        s = (int)a, t = (int)b; solve();
        printf("Case %d:\n", cs);
        printf("%lld\n", d[s]);
        path(s); putchar('\n');
        scanf("%d", &n);
    }
    return 0;
}