#define LOCAL
#include <bits/stdc++.h>
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T &a, T &b) {return a > b ? a : b;}
template <typename T> inline T Min(T &a, T &b) {return a < b ? a : b;}

struct Edge {int u, v, nxt;} e[N];

int n, a[N], head[N], ecnt(1), vis[N], tot, ans;

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void get_ring(int x) {
    vis[x] = true; a[++ tot] = x; 
    for (int i = head[x]; i; i = e[i].nxt)
      if (!vis[e[i].v]) get_ring(e[i].v);
}

#define lb(t, l, x) lower_bound(t + 1, t + l + 1, x)

void get_ans() {
    int f[N], st[N], stp; 
    for (int i = 1; i <= n; ++ i) a[i + n] = a[i];
    for (int i = 1; i <= n; ++ i) {
        mset(f, 0); mset(st, 0); stp = 0;
        for (int j = i; j <= i + n - 1; ++ j) {
            if (a[j] > st[stp]) st[++ stp] = a[j];
            else {
                int pos = lb(st, stp, a[j]) - st;
                st[pos] = a[j];
            }
            f[j - i + 1] = stp;
        }
        ans = Max(ans, f[n]);
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while (1) {
        read(n); if (!n) break;
        mset(head, 0); ecnt = 1, tot = ans = 0;
        for (int i = 1; i <= n; ++ i) {
            int x, y; read(x), read(y);
            add_edge(i, x); add_edge(i, y);
        }
        mset(vis, 0); mset(a, 0); get_ring(1);
        if (tot != n) {printf("Not solvable.\n"); continue;}
        else printf("Knot solvable.\n");
        get_ans(); reverse(a + 2, a + n + 1);
        get_ans(); printf("%d\n", n - ans);
    }
    return 0;
}
