#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 200010;
const int INF = 0x3fffffff;

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

int n, m, ans = INF, mp[20][20], tmp[20][20];

inline int bitcount(int x) {
    int cnt = 0;
    while (x) cnt += (x & 1), x >>= 1;
    return cnt;
}

int get_res(int x) {
    // cout << "CHECK: " << x << endl;
    int res = 0;
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= m; ++ j)
        tmp[i][j] = mp[i][j];
    for (int i = 0; i < m; ++ i)
      if (x & (1 << i)) {
          tmp[1][i + 1] ^= 1, tmp[1][i] ^= 1;
          tmp[1][i + 2] ^= 1, tmp[2][i + 1] ^= 1;
      }
    // for (int i = 1; i <= n; ++ i) {
    //     for (int j = 1; j <= m; ++ j)
    //       cout << tmp[i][j];
    //     cout << endl;
    // }
    for (int i = 1; i < n; ++ i)
      for (int j = 1; j <= m; ++ j)
        if (tmp[i][j]) {
            ++ res; tmp[i][j] ^= 1;
            tmp[i + 1][j] ^= 1;
            tmp[i + 1][j - 1] ^= 1;
            tmp[i + 1][j + 1] ^= 1;
            tmp[i + 2][j] ^= 1;
        }
    for (int i = 1; i<= m; ++ i)
      if (tmp[n][i]) return INF;
    // cout << "OK: " << res + bitcount(x) << endl;
    return res + bitcount(x);
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= m; ++ j) {
          char c; cin >> c;
          if (c == 'X') mp[i][j] = 1;
          else mp[i][j] = 0;
      }
    for (int i = 0; i < 1 << m; ++ i)
      ans = Min(ans, get_res(i));
    cout << ans;
    return 0;
}