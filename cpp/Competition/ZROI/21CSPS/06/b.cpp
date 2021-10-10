#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1000010;
const int M = 1010;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

ll n, f[N], x[N];

inline int calc(int a, int b) {
    if (f[a] / 4 == f[b] / 4) return 1;
    else if (f[a] / 16 == f[b] / 16) return 2;
    else return 3;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) read(x[i]);
    for (int i = 1; i <= n; ++ i) {
        f[i] = f[i - 1];
        while ((1ll << f[i]) <= x[i]) ++ f[i];
        -- f[i];
    }
    for (int i = 2; i <= n; ++ i) {
        for (int j = 1; j < i; ++ j)
          printf("%d ", calc(j, i));
        puts("");
    }
    return 0;
}
