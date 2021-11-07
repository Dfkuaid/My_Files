#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int M = 101;
const int N = 200010;
const ll MOD = 1e9 + 7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

char s[N], t[N];
int n, m, k, cnt[M], pos[M][M]; ll f[M], g[M], ans;

inline void madd(ll &x, ll y) {x = (x + y >= MOD) ? (x + y - MOD) : (x + y);}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m), read(k);
    scanf("%s%s", s + 1, t + 1);
    if (m == 1) {puts("0"); return 0;}
    for (int i = 2; i <= m - 1; ++ i)
      pos[t[i] - 'a'][++ cnt[t[i] - 'a']] = i;
    for (int i = n - k; i; -- i) {
        for (int j = 1; j <= cnt[s[i + k] - 'a']; ++ j)
          madd(g[pos[s[i + k] - 'a'][j] - 1], g[pos[s[i + k] - 'a'][j]]);
        if (s[i + k] == t[m]) madd(g[m - 1], 1);
        if (s[i] == t[1]) {
            for (int j = 1; j <= m; ++ j) f[j] = 0;
            f[1] = f[2] = 1;
            for (int j = i + 1; j <= i + k - 1; ++ j)
              for (int l = cnt[s[j] - 'a']; l; -- l)
                madd(f[pos[s[j] - 'a'][l] + 1], f[pos[s[j] - 'a'][l]]);
            for (int j = 1; j <= m; ++ j)
              madd(ans, g[j - 1] * f[j] % MOD);
        }
    }
    printf("%d", ans); return 0;
}
