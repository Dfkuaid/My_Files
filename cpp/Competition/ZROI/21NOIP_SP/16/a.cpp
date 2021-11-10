#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 110;
const __int128 ONE = 1;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, k, w[N], odr[N], mapping[N], wt[N]; __int128 G[N]; char s[N][N], s2[N][N];

inline bool cmp(const int &x, const int &y) {return w[x] < w[y];}

int lowbit(__int128 x) {
    if ((x & ((ONE << 50) - 1)) == 0)
      return __builtin_ctzll((ll)(x >> 50)) + 50;
    else return __builtin_ctzll((ll)(x & ((ONE << 50) - 1)));
}

int cnt; ll lmt, sum;

void dfs(__int128 now, __int128 can, ll sum) {
    if (sum <= lmt) ++ cnt; else return; if (cnt >= k) return;
    while (can) {
        int p = lowbit(can); can ^= (ONE << p);
        dfs(now | (ONE << p), can & G[p], sum + w[p]);
        if (sum + w[p] > lmt || cnt >= k) return;
    }
}

bool check(ll x) {cnt = 0, lmt = x; dfs(0, (ONE << n) - 1, 0); return cnt >= k;}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(k);
    for (int i = 0; i < n; ++ i) read(w[i]);
    for (int i = 0; i < n; ++ i) sum += w[i];
    for (int i = 0; i < n; ++ i) odr[i] = i;
    sort(odr, odr + n, cmp);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", s[i]);
        for (int j = 0; j < n; ++ j) s[i][j] -= '0';
    }
    for (int i = 0; i < n; ++ i) wt[i] = w[i];
    for (int i = 0; i < n; ++ i) mapping[odr[i]] = i;
    for (int i = 0; i < n; ++ i) w[mapping[i]] = wt[i];
    for (int i = 0; i < n; ++ i)
      for (int j = 0; j <= n; ++ j)
        s2[i][j] = s[i][j];
    for (int i = 0; i < n; ++ i)
      for (int j = 0; j <= n; ++ j)
        s[mapping[i]][mapping[j]] = s2[i][j];
    for (int i = 0; i < n; ++ i) {
        G[i] = 0;
        for (int j = 0; j < n; ++ j)
          if (s[i][j]) G[i] |= (ONE << j);
    }
    ll l = 0, r = sum, res = -1;
    while (l <= r) {
        ll mid = l + r >> 1;
        if (check(mid)) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%lld", res); return 0;
}
