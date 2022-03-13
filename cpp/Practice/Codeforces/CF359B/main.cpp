#define LOCAL
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

int n, k, a[N], p, q, tmp;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(k); p = 1, q = 0;
    for (int i = 1; i <= n << 1; ++ i) a[i] = i;
    while (k) {
        ++ q, -- k; swap(a[p << 1], a[p + q << 1]);
        if ((p + q) << 1 == n << 1) ++ p, q = 0;
    }
    for (int i = 1; i <= n << 1; ++ i) printf("%d ", a[i]);
    return (0 - 0);
}
