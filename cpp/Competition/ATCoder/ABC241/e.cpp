#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, a[N], cnt, p, q, t[N], vis[N], tot; ll k, sum[N], pre[N];

int main() {
    read(n); read(k);
    for (int i = 0; i < n; ++ i) read(a[i]), t[i] = a[i];
    for (int i = 0; i < n; ++ i) a[i] = (a[i] + i) % n;
    while (!vis[p]) vis[p] = 1, p = a[p];
    while (q != p) ++ tot, pre[tot] = pre[tot - 1] + t[q], q = a[q];
    sum[1] = t[p]; ++ cnt; q = a[p];
    while (q != p) ++ cnt, sum[cnt] = sum[cnt - 1] + t[q], q = a[q];
    if (k <= tot) {printf("%lld\n", pre[k]); return 0;}
    k -= tot; ll d = k / cnt; k %= cnt;
    printf("%lld", pre[tot] + d * sum[cnt] + sum[k]);
    return (0 - 0);
}
