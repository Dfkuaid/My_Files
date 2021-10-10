#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 5e5;
const ll INF = 1e12;

char s[N];
int t, n, a[N]; ll f[N], ans;

int main() {
    scanf("%d", &t);
    for (int i = 1; i <= t; ++ i) {
        printf("Case #%d: ", i);
        memset(f, 0x3f, sizeof(f));
        scanf("%d%s", &n, s); ans = 0;
        for (int i = 0; i < n; ++ i)
          a[i + 1] = s[i] - '0';
        ll lst = -INF;
        for (int i = 1; i <= n; ++ i) {
            if (a[i]) lst = i;
            f[i] = min(f[i], (ll)i - lst);
        }
        lst = INF;
        for (int i = n; i >= 1; -- i) {
            if (a[i]) lst = i;
            f[i] = min(f[i], lst - (ll)i);
        }
        for (int i = 1; i <= n; ++ i)
          ans += f[i];
        printf("%lld\n", ans);
    }
    return 0;
}
