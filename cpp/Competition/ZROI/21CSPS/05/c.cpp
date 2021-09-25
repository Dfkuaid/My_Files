#define LOCAL
#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

struct Edge {int u, v, nxt;} e[N], ae[N];

int n, m, ecnt(1), head[N], icnt[N], q[N], frt, tal, mx[N][3];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v, ++ icnt[v];
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

inline int GetType(int x) {
    // printf("%d %d %d %d\n", x, mx[x][1], mx[x][2], mx[x][3]);
    if (mx[x][1] <= mx[x][2] && mx[x][1] <= mx[x][3]) return 1;
    else if (mx[x][2] <= mx[x][1] && mx[x][2] <= mx[x][3]) return 2;
    else return 3;
}

void solve() {
    frt = 0, tal = -1;
    for (int i = 1; i <= n; ++ i)
      if (!icnt[i]) q[++ tal] = i;
    while (frt <= tal) {
        int now = q[frt ++], op = GetType(now);
        for (int i = head[now]; i; i = e[i].nxt) {
            mx[e[i].v][op] = max(mx[e[i].v][op], mx[now][op] + 1);
            -- icnt[e[i].v]; if (!icnt[e[i].v]) q[++ tal] = e[i].v;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        // printf("%d %d\n", u, v);
        add_edge(u, v); ae[i].u = u, ae[i].v = v;
    }
    solve();
    for (int i = 1; i <= m; ++ i) {
        // printf("%d %d", ae[i].u, ae[i].v);
        int op = GetType(ae[i].u);
        if (op == 1) printf("R\n");
        else if (op == 2) printf("G\n");
        else printf("B\n");
    }
    return 0;
}
