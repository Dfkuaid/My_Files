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

int t, n, k, cnt[N], cnt1, cnt2, ans, a[N];
char s[N];

int main() {
    k = 2; scanf("%d", &t);
    while (t --) {
        cnt1 = cnt2 = ans = 0;
        mset(cnt, 0);
        scanf("%s", s); n = strlen(s);
        // cout << s << endl;
        for (int i = 0; i < n; ++ i)
          a[i + 1] = s[i] - 'a' + 1, ++ cnt[a[i + 1]];
        for (int i = 1; i <= n; ++ i)
          if (cnt[a[i]] >= k) ans ++, cnt[a[i]] = 0;
          else if (cnt[a[i]]) ++ cnt2;
        // cout << ans << " " << cnt2 << endl;
        ans +=  cnt2 / k;
        printf("%d\n", ans);
    }
    return 0;
}