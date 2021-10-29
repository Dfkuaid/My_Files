#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}

struct Alpinists {
    int s, a;
    inline bool operator < (const Alpinists b) const {
        int mx1 = Max(s, a), mx2 = Max(b.s, b.a);
        if (mx1 != mx2) return mx1 < mx2;
        else return s == b.s ? a < b.a : s < b.s;
    }
} p[N];

int n, d, ans;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); read(d);
    for (int i = 1; i <= n; ++ i)
      read(p[i].s), read(p[i].a);
    sort(p + 1, p + n + 1);
    for (int i = 1; i <= n; ++ i)
      if (p[i].s >= d) ++ ans, d = Max(d, p[i].a);
    printf("%d", ans); return 0;
}
