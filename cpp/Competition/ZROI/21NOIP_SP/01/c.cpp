#define LOCAL
#include <bits/stdc++.h>
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge{int u, v, nxt;} e[N];

int T, n, k, head[N], ecnt(1), f[N], siz[N], son[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void get_ans(int x) {
    siz[x] = 1; son[x] = 0, f[x] = 0; int t = 0;
    for (int i = head[x]; i; i = e[i].nxt) {
        get_ans(e[i].v); f[x] += f[e[i].v];
        siz[x] += siz[e[i].v]; ++ son[x];
        if (!f[e[i].v] && siz[e[i].v] > 1) t = 1;
    }
    if (son[x] >= k && t) ++ f[x];
    for (int i = head[x]; i; i = e[i].nxt)
      if (siz[e[i].v] >= k + 1)
        f[x] = max(f[x], f[e[i].v] + 1);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(T);
    while (T --) {
        ecnt = 1; mset(head, 0);
        read(n), read(k); int x = 0;
        for (int i = 2; i <= n; ++ i)
          read(x), add_edge(x, i);
        get_ans(1); printf("%d\n", f[1]);
    }
    return 0;
}
