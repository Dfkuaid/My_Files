#define LOCAL
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt;} e[N];

int t, n, scnt[N], head[N], f[N], ecnt;

vector <int> q[N];

inline void reset() {
    memset(head, 0, sizeof head);
    memset(f, 0, sizeof f); ecnt = 1;
    for (int i = 1; i <= n; ++ i) q[i].clear();
}

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

inline bool cmp(int x, int y) {return x > y;}

void solve(int x) {
    if (!scnt[x]) {f[x] = 1; return;}
    for (int i = head[x]; i; i = e[i].nxt)
      solve(e[i].v), q[x].push_back(f[e[i].v]);
    sort(q[x].begin(), q[x].end(), cmp);
    int rst = 0;
    for (int i = 0; i < q[x].size(); ++ i) {
        f[x] += rst < q[x][i] ? q[x][i] - rst : 0;
        rst = rst < q[x][i] ? q[x][i] - 1 : rst - 1;
    }
}

void MAIN() {
    read(n); reset();
    for (int i = 1, x = 0; i <= n; ++ i) {
        read(x), read(scnt[x]);
        for (int j = 1, y = 0; j <= scnt[x]; ++ j)
          read(y), add_edge(x, y);
    }
    solve(1); printf("%d\n", f[1]);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) MAIN(); return 0;
}
