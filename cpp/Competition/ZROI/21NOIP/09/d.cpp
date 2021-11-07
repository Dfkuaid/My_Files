/*Haven't finished.*/
#define LOCAL
#include <bits/stdc++.h>
#define ld long double
#define ll long long
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

template<typename T> inline void read(T &x) {
    x=0; int f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n, a[N], b[N]; ld ans, sum[N]; bool sub1 = 1;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) {
        read(a[i]); if (a[i] != i) sub1 = 0;
    }
    for (int i = 1; i <= n; ++ i) {
        read(b[i]); if (b[i] != i) sub1 = 0;
    }
    if (n <= 5000) {
        for (int i = 1; i <= n; ++ i) {
            ans = 0.0;
            for (int j = 1; j <= n; ++ j)
              ans += (ld)b[i] / ((ld)a[j] + (ld)b[i]);
            printf("%0.10Lf ", ans);
        }
    } else if (sub1) {
        for (int i = 1; i <= n * 2; ++ i)
          sum[i] = sum[i - 1] + (ld)1 / (ld) i;
        for (int i = 1; i <= n; ++ i)
          printf("%0.10Lf ", (ld)i * (sum[i + n] - sum[i]));
    }
    return 0;
}
