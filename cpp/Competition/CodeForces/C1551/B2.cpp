#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define pii pair <int, int>
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 300010;
const int INF = 0x3fffffff;

int t, n, k, cnt[N], col[N], cnt1, cnt2, lmt, ans[N];
pii a[N], b[N], c[N];

int main() {
    scanf("%d", &t);
    while (t --) {
        cnt1 = cnt2 = 0;
        mset(cnt, 0); mset(col, 0);
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &a[i].first);
            a[i].second = i;
            ++ cnt[a[i].first];
        }
        for (int i = 1; i <= n; ++ i)
          if (cnt[a[i].first] >= k) b[++ cnt1] = a[i];
          else c[++ cnt2] = a[i];
        sort(b + 1, b + cnt1 + 1);
        sort(c + 1, c + cnt2 + 1);
        for (int i = 1; i <= cnt1; ++ i)
          if (col[b[i].first] < k)
            ans[b[i].second] = ++ col[b[i].first];
        // cout << "ANS: ";
        // for (int i = 1; i <= n; ++ i) {
        //     printf("%d ", ans[i]);
        //     // ans[i] = 0;
        // }  
        // printf("\n");
        lmt = cnt2 / k * k;
        for (int i = 1; i <= lmt; ++ i)
          ans[c[i].second] = (i % k) + 1;
        // cout << "ANS: ";
        for (int i = 1; i <= n; ++ i) {
            printf("%d ", ans[i]);
            ans[i] = 0;
        }  
        printf("\n");
    }
    return 0;
}