#define LOCAL
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;

const int N = 1010;
const int M = 2000000;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Min(T x, T y) {return x < y ? x : y;}

struct Edge {int u, v, nxt;} e[M];

int n, m, head[N], ecnt(1), nw[N][N], bel[N], col[N];
int dfn[N], low[N], T, cnt, ans, odd[N], stk[N], stp;

vector <int> bcc[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

inline void reset() {
    memset(head, 0, sizeof head); memset(nw, 0, sizeof nw);
    memset(col, -1, sizeof col); memset(bel, 0, sizeof bel);
    memset(dfn, 0, sizeof dfn); memset(odd, 0, sizeof odd);
    T = cnt = ans = 0; ecnt = 1;
}

bool check(int x) {
    for (int i = head[x]; i; i = e[i].nxt) {
        if (bel[e[i].v] != cnt) continue;
        if (col[e[i].v] == (col[x] ^ 1)) continue;
        if (col[e[i].v] == col[x]) return true;
        col[e[i].v] = col[x] ^ 1;
        if (check(e[i].v)) return true;
    }
    return false;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++ T; stk[++ stp] = x;
    for (int i = head[x]; i; i = e[i].nxt)
      if (!dfn[e[i].v]) {
          tarjan(e[i].v); low[x] = Min(low[x], low[e[i].v]);
          if (low[e[i].v] == dfn[x]) {
              int y, tmp = col[x], op = 0; bcc[++ cnt].clear();
              do {
                  y = stk[stp --]; bel[y] = cnt;
                  bcc[cnt].push_back(y);
              } while (y != e[i].v);
              bcc[cnt].push_back(x); bel[x] = cnt, col[x] = 1;
              if (op = check(x)) for (auto z : bcc[cnt]) odd[z] = 1;
              col[x] = tmp | op;
          }
      } else low[x] = Min(low[x], dfn[e[i].v]);
}

void MAIN() {
    reset();
    for (int i = 1; i <= m; ++ i) {
        int u, v; read(u), read(v);
        nw[u][v] = nw[v][u] = 1;
    }
    for (int i = 1; i <= n; ++ i)
      for (int j = i + 1; j <= n; ++ j)
        if (!nw[i][j]) add_edge(i, j), add_edge(j, i);
    for (int i = 1; i <= n; ++ i) if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; ++ i) if (!odd[i]) ++ ans;
    printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m); while (n || m) {MAIN(); read(n), read(m);} return 0;
}
