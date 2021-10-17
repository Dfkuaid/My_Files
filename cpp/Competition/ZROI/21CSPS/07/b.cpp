#define LOCAL
#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;

const int N = 200010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

map <int, int> Map;

struct Node {
    int l, r, x;
    inline Node() {}
    inline Node(int l, int r, int x) : l(l), r(r), x(x) { }
    inline bool operator < (const Node &b) const {return x > b.x;}
} a[N];

int T, n, m, tal;

inline int Solve() {
    int now = 0, lst = -1;
    for (auto p : Map) {
        if (now == 0) {
            now = p.second; lst = p.first;
            continue;
        }
        a[++ tal] = Node(lst, p.first - 1, now);
        lst = p.first; now += p.second;
    }
    sort(a + 1, a + tal + 1);
    int ans = 0;
    for (int i = 1; i <= tal; ++ i) {
        int len = a[i].r - a[i].l + 1;
        if (len > m) {ans += m * a[i].x; break;}
        else {ans += len * a[i].x; m -= len;}
    }
    return ans + n;
}

signed main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(T);
    for (int i = 1; i <= T; ++ i) {
        read(n); read(m); Map.clear(); tal = 0;
        for (int i = 1; i <= n; ++ i) {
            int l, r; read(l); read(r);
            if (r == l + 1) continue;
            ++ Map[l + 1]; -- Map[r];
        }
        printf("Case #%lld: %lld\n", i, Solve());
    }
    return 0;
}
