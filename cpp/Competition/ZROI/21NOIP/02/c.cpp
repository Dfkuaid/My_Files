#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define pii pair <int, int>
#define mp(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T>
inline T Max(const T a, const T b) {return a > b ? a : b;}

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

char s[N];
int t, n, m, fa[N], lsiz[N], rsiz[N], ans, sum, vis[N];

vector <pii > v;

inline int calc(int x) {return x * x;}

inline void init() {
    for (int i = 1; i <= n << 1; ++ i)
      fa[i] = i, lsiz[i] = (i <= n), rsiz[i] = (i > n);
}

inline int find(int x) {
    while (x != fa[x])
      x = fa[x] = fa[fa[x]];
    return x;
}

inline void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        fa[x] = y;
        lsiz[y] += lsiz[x];
        rsiz[y] += rsiz[x];
    }
}

void dfs(int k, int lst, int tot, int ltot, int rtot, int delta) {
    if (sum + Max(ltot, rtot) >= ans) return;
    if (!(~lst)) {
        if (k == v.size()) {ans = Min(ans, sum + ltot); return;}
    } else {
        sum += calc(tot + Max(0, delta));
        if (delta > 0) {
            if (ltot >= delta) dfs(k, -1, 0, ltot - delta, rtot, 0);
        } else {
            if (rtot + delta >= 0) dfs(k, -1, 0, ltot, rtot + delta, 0);
        }
        sum -= calc(tot + Max(0, delta));
    }
    pii now = mp(0, 0);
    for (int i = lst + 1; i < v.size(); ++ i)
      if (!vis[i] && v[i] != now) {
          now = v[i]; vis[i] = 1;
          dfs(k + 1, i, tot + v[i].first, ltot, rtot, delta - v[i].first + v[i].second);
          vis[i] = 0;
      }
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d", &t);
    while (t --) {
        scanf("%d", &n); init(); v.clear();
        ans = n * n, sum = m = 0;
        for (int i = 1; i <= n; ++ i) {
            scanf("%s", s + 1);
            for (int j = 1; j <= n; ++ j)
              if (s[j] == '1') ++ m, merge(i, j + n);
        }
        int ltot = 0, rtot = 0;
        for (int i = 1; i <= n << 1; ++ i)
          if (fa[i] == i) {
              if (lsiz[i] == rsiz[i])
                sum += calc(lsiz[i]);
              else if (!lsiz[i]) ++ rtot;
              else if (!rsiz[i]) ++ ltot;
              else v.push_back(mp(lsiz[i], rsiz[i]));
          }
        sort(v.begin(), v.end());
        dfs(0, -1, 0, ltot, rtot, 0);
        printf("%d\n", ans - m);
    }
    return 0;
}