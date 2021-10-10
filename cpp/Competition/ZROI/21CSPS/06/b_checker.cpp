#include <bits/stdc++.h>
using namespace std;

const int M = 1010;
const int N = 1000100;

struct Edge {int u, v, nxt;} e[N];

ll a[N], col[M][M];
int head[N], ecnt(1), len[N][3], icnt[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v; ++ icnt[v];
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

bool check() {
    int q[N], frt = 0, tal = -1;
    for (int i = 1; i <= n; ++ i)
      if (!icnt[i]) q[++ tal] = i;
    while (frt <= tal) {
        int now = q[++ frt];
        if (len[now][0] > 3 || len[now][1] > 3 || len[now][2] > 3) return false;
        for (int i = head[now]; i; i = e[i].nxt) {
            -- icnt[e[i].v];
            if (a[e[i].v] % a[now] == 0) {
                int c = col[now][e[i].v] - 1;
                len[e[i].v][c] = max(len[e[i].v][c], len[now][c] + 1);
            }
            if (!icnt[e[i].v]) q[++ tal] = e[i].v;
        }
    }
    return true;
}

int main() {
    freopen("out.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i)
      scanf("%lld", &a[i]);
    for (int i = 2; i <= n; ++ i)
      for (int j = 1; j < i; ++ j)
        scanf("%d", &col[j][i]);
    for (int i = 2; i <= n; ++ i)
      for (int j = 1; j < i; ++ j)
        add_edge(j, i);
    if (check()) printf("Accepted!");
    else printf("Wrong Answer.");
    return 0;
}
