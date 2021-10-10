#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1000010;
const int M = 1010;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt;} e[N];

ll x[M];
int n, head[M], ecnt(1), hvedge[M][M], icnt[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v; ++ icnt[v];
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

int cnt1, cnt2, cnt3, col[M][2];

void solve() {
    int q[N], tal = -1, frt = 0;
    for (int i = 1; i <= n; ++ i)
      if (!icnt[i]) q[++ tal] = i;
    while (frt <= tal) {
        int now = q[frt ++]; ++ cnt1;
        if (cnt1 % 4 == 1) {
            ++ cnt2; if (cnt2 % 4 == 1) ++ cnt3;
        }
        col[now][0] = cnt2, col[now][1] = cnt3;
        // printf("%d %d %d\n", now, col[now][0], col[now][1]);
        for (int i = head[now]; i; i = e[i].nxt)
          if (-- icnt[e[i].v] == 0) q[++ tal] = e[i].v;
    }
}

inline int calc(int a, int b) {
    if (col[a][1] != col[b][1]) return 3;
    else if (col[a][0] != col[b][0]) return 2;
    else return 1;
}

inline void print() {
    for (int i = 2; i <= n; ++ i) {
        for (int j = 1; j < i; ++ j)
          if (!hvedge[j][i]) printf("1 ");
          else printf("%d ", calc(j, i));
        printf("\n");
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) read(x[i]);
    for (int i = 2; i <= n; ++ i)
      for (int j = 1; j < i; ++ j)
        if (x[i] % x[j] == 0) {
            // printf("%d %d\n", j, i);
            hvedge[j][i] = 1;
            add_edge(j, i);
        }
    solve(); print(); return 0;
}
