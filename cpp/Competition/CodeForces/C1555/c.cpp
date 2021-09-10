#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t, a[2][N], n, sum[2][N], ans;

int main() {
    scanf("%d", &t);
    while (t --) {
        scanf("%d", &n); ans = INF;
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &a[0][i]);
            a[0][i] += a[0][i - 1];
        }
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &a[1][i]);
            a[1][i] += a[1][i - 1];
        }
        for (int i = 1; i <= n; ++ i)
          ans = min(ans, max(a[0][n] - a[0][i], a[1][i - 1]));
        printf("%d\n", ans);
    }
    return 0;
}