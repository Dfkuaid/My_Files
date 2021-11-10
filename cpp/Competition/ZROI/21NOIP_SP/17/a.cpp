#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 105;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

ll dp[N][2][2]; int n, a[N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    sort(a + 1, a + 1 + n);
    for (int i = n; i; -- i) {
        if (a[i] >= 4) {
            if (dp[i + 1][1][0] + a[i] - 4 > dp[i][1][0]) {
                dp[i][0][0] = dp[i + 1][0][0] + 4;
                dp[i][1][0] = dp[i + 1][1][0] + a[i] - 4;
            }
            if (dp[i + 1][0][1] + a[i] - 4) {
                dp[i][1][1] = dp[i + 1][1][1] + 4;
                dp[i][0][1] = dp[i + 1][0][1] + a[i] - 4;
            }
        }
        if (dp[i + 1][1][1] + a[i] > dp[i][1][0]) {
            dp[i][0][0] = dp[i + 1][0][1];
            dp[i][1][0] = dp[i + 1][1][1] + a[i];
        }
        if (dp[i + 1][0][0] + a[i] > dp[i][0][1]) {
            dp[i][1][1] = dp[i + 1][1][0];
            dp[i][0][1] = dp[i + 1][0][0] + a[i];
        }
    }
    printf("%lld %lld", dp[1][0][0], dp[1][1][0]);
    return 0;
}
