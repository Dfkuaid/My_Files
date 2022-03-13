#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Point {int id; ll d;} p[N];

int n, siz[N], ans[N][2], cnt; ll dis;

inline int binary_search(ll x) {
    int l = 1, r = n, res = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (p[mid].d >= x)
          res = mid, l = mid + 1;
        else r = mid - 1;
    }
    return p[res].d == x ? res : -1;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) p[i].id = i;
    for (int i = 1; i <= n; ++ i) read(p[i].d);
    auto cmp = [](Point a, Point b){return a.d > b.d;};
    sort(p + 1, p + n + 1, cmp);
    for (int i = 1; i <= n; ++ i) siz[i] = 1;
    for (int i = 1; i < n; ++ i) {
        ll x = p[i].d + siz[p[i].id] * 2 - n;
        int pos = binary_search(x);
        if (!(~x)) {puts("-1"); return (0 - 0);}
        ans[++ cnt][0] = p[i].id;
        ans[cnt][1] = p[pos].id;
        siz[p[pos].id] += siz[p[i].id];
        dis += siz[p[i].id];
    }
    if (dis != p[n].d) {puts("-1"); return (0 - 0);}
    for (int i = 1; i <= cnt; ++ i)
      printf("%d %d\n", ans[i][0], ans[i][1]);
    return (0 - 0);
}
