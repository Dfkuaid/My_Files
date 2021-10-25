#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;
 
const int N = 4010;
const int INF = 0x3fffffff;
 
template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}
 
int t, n, a[N], q, b[N][N], tot[N];
 
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t);
    while (t --) {
        read(n);
        for (int i = 1; i <= n; ++ i) read(b[i][0]);
        for (int i = 1; i <= n; ++ i) tot[i] = 0;
        for (int i = 1; i <= n; ++ i) ++ tot[b[i][0]];
        for (int i = 1; i <= 2000; ++ i) {
            for (int j = 1; j <= n; ++ j) b[j][i] = tot[b[j][i - 1]];
            for (int j = 1; j <= n; ++ j) tot[j] = 0;
            for (int j = 1; j <= n; ++ j) ++ tot[b[j][i]];
        }
        read(q);
        while (q --) {
            int x, k; read(x), read(k);
            if (k >= 2000) printf("%d\n", b[x][2000]);
            else printf("%d\n", b[x][k]);
        }
    }
    return 0;
}
