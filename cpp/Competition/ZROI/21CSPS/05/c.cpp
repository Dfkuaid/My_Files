#define LOCAL
#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int INF = 0x3fffffff;

struct Edge {int u, v, nxt;} e[N], ae[N];

int ecnt(1), icnt[N], head[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v, ++ icnt[v];
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

int n, m, q[N], frt, tal, T1, T2, T3, type[N][3];

/*Use topo to divide the node to different groups.*/
void topo() {
    frt = 0, tal = -1;
    for (int i = 1; i <= n; ++ i)
      if (!icnt[i]) q[++ tal] = i;
    while (frt <= tal) {
        int now = q[frt ++]; (++ T1) %= 42;
        if (T1 % 42 == 1) ++ T2; if (T2 % 42 == 1) ++ T3;
        type[now][2] = T3, type[now][1] = T2;
        for (int i = head[now]; i; i = e[i].nxt)
          if (!(-- icnt[e[i].v])) q[++ tal] = e[i].v;
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i) {
        scanf("%d%d", &ae[i].u, &ae[i].v);
        add_edge(ae[i].u, ae[i].v);
    }
    topo();
    for (int i = 1; i <= m; ++ i) {
        int u = ae[i].u, v = ae[i].v;
        if (type[u][1] == type[v][1]) printf("R\n");
        else if (type[u][2] == type[v][2]) printf("G\n");
        else printf("B\n");
    }
    return 0;
}
