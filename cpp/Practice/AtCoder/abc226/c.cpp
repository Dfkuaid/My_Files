#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, k, vis[N]; ll f[N], ans;

vector <int> pre[N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) {
        read(f[i]), read(k);
        for (int j = 1, x; j <= k; ++ j)
          read(x), pre[i].push_back(x);
    }
    vis[n] = 1;
    for (int i = n; i >= 1; -- i) if (vis[i]) {
        ans += f[i]; for (auto x : pre[i]) vis[x] = 1;
    }
    printf("%lld", ans); return 0;
}
