#define DEBUG

#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int M = 105;
const int N = 4e4 + 5;
const int INF = 0x3fffffff;

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

struct Node {int ls, rs, tag, minn;} p[N * M << 1];

int n, m, cnt, rt[N], a[N], lst[N], f[N][M], ans = INF;

inline void update(int k, int x) {
    p[k].minn += x, p[k].tag += x;
}

inline void pushup(int k) {
    p[k].minn = Min(p[p[k].ls].minn, p[p[k].rs].minn);
}

inline void pushdown(int k) {
    update(p[k].ls, p[k].tag);
    update(p[k].rs, p[k].tag);
    p[k].tag = 0;
}

inline void build(int &k, int l, int r) {
    if (!k) k = ++ cnt;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p[k].ls, l, mid);
    build(p[k].rs, mid + 1, r);
}

void modify(int k, int l, int r, int x, int y, int c) {
    if (x <= l && r <= y) {update(k, c); return;}
    int mid = l + r >> 1; pushdown(k);
    if (x <= mid) modify(p[k].ls, l, mid, x, y, c);
    if (mid < y) modify(p[k].rs, mid + 1, r, x , y, c);
    pushup(k);
}

int query(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y) return p[k].minn;
    int mid = l + r >> 1, ans = INF; pushdown(k);
    if (x <= mid) ans = Min(ans, query(p[k].ls, l, mid, x, y));
    if (mid < y) ans = Min(ans, query(p[k].rs, mid + 1, r, x, y));
    return ans;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d%d", &n, &m); mset(f, 0x3f);
    for (int i = 1; i <= n; ++ i) scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++ i) build(rt[i], 1, n);
    f[0][0] = 0;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= Min(i, m); ++ j) {
            modify(rt[j], 1, n, i, i, f[i - 1][j - 1]);
            if (lst[a[i]]) modify(rt[j], 1, n, 1, lst[a[i]], i - lst[a[i]]);
            f[i][j] = query(rt[j], 1, n, 1, i);
        }
        lst[a[i]] = i;
    }
    printf("%d", f[n][m]);
    return 0;
}