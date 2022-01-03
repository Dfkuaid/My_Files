#define LOCAL
#include <bits/stdc++.h>
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

struct Edge {int u, v, w, col;} e[N];
struct UnionSet {
    int fa[N], siz[N], cnt;
    
    inline UnionSet() {cnt = 0;}
    inline void init(int x) {cnt = 0; while (cnt <= x) fa[cnt] = cnt, siz[cnt ++] = 1;}
    int find(int x) {while (x != fa[x]) x = fa[x] = fa[fa[x]]; return x;}
    inline bool connected(int x, int y) {return find(x) == find(y);}
    inline void unify(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (siz[x] > siz[y]) swap(x, y);
        fa[x] = y, siz[y] += siz[x];
    }
} us;

int n, m, ned, ans;

inline bool cmp(Edge x, Edge y) {return x.w == y.w ? x.col < y.col : x.w < y.w;}

inline int kruscal() {
    int wcnt = 0; us.init(n); ans = 0;
    sort(e + 1, e + m + 1, cmp);
    for (int i = 1; i <= m; ++ i) {
        if (us.connected(e[i].u, e[i].v)) continue;
        us.unify(e[i].u, e[i].v);
        wcnt += !e[i].col, ans += e[i].w;
    }
    return wcnt;
}

inline int check(int x) {
    for (int i = 1; i <= m; ++ i)
      e[i].w -= e[i].col ? 0 : x;
    int res = kruscal();
    for (int i = 1; i <= m; ++ i)
      e[i].w += e[i].col ? 0 : x;
    return res;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m), read(ned);
    for (int i = 1; i <= m; ++ i)
      read(e[i].u), read(e[i].v), read(e[i].w), read(e[i].col);
    int l = -100, r = 100, res = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid) < ned) l = mid + 1;
        else res = mid, r = mid - 1;
    }
    check(res); printf("%d", ans + res * ned); return 0;
}
