#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t, W, H, w1, h1, w2, h2, x1, x2, y, y2;

int main() {
    scanf("%d", &t);
    while (t --) {
        scanf("%d%d", &W, &H); int ans = INF;
        scanf("%d%d%d%d", &x1, &y, &x2, &y2);
        w1 = x2 - x1, h1 = y2 - y;
        scanf("%d%d", &w2, &h2);
        if (w2 + w1 > W && h1 + h2 > H) {
            puts("-1"); continue;
        }
        if (w2 + w1 <= W) {
            ans = min(ans, max(w2 - x1, 0));
            ans = min(ans, max(x2 - W + w2, 0));
        }
        if (h2 + h1 <= H) {
            ans = min(ans, max(h2 - y, 0));
            ans = min(ans, max(y2 - H + h2, 0));
        }
        printf("%.9lf\n", (double)ans);
    }
    return 0;
}