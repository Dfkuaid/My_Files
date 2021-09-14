#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 200010;
const ull BASE = 9973;
const ull MOD = 1e9 + 7;
const int INF = 0x3fffffff;

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

template <typename T>
inline T Max(const T a, const T b) {return a > b ? a : b;}

int n, p[N], h[N], hr[N]; char s[N], sr[N];
ll f[N][26], fk[N], fl[N], init_val;

inline void init_hash(char *S, int *H) {
    int len = strlen(S); H[0] = 1;
    for (int i = 0; i < len; ++ i)
      H[i + 1] = (1ull * H[i] * BASE % MOD + (ll)(S[i] - 'a')) % MOD;
}

inline ull getHash(int* H, int a, int b) {
    return ((1ull * H[b + 1] - 1ull * H[a] * p[b - a + 1] % MOD) + MOD) % MOD;
}

inline bool check(int a, int b, int c, int d) {
    return getHash(h, a, b) == getHash(hr, n - d - 1, n - c - 1);
}

int getRadius(int l, int r, int x, int y){
    int L = x, R = y, res = 0;
    while (L <= R) {
        int mid = (L + R + 1) >> 1;
        if (check(l - mid + 1, l, r, r + mid - 1))
          res = mid, L = mid + 1;
        else R = mid - 1;
    }
    return res;
}

signed main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%s", s); n = strlen(s); p[0] = 1;
    for (int i = 0; i <= n; ++ i)
      p[i + 1] = (1ull * p[i] * BASE) % MOD;
    for (int i = 0; i < n; ++ i)
      sr[i] = s[n - i - 1];
    init_hash(s, h); init_hash(sr, hr);
    for (int i = 0; i < n; ++ i)
      for (int j = i; j <= i + 1; ++ j) {
          int r = 0; r = getRadius(i, j, 0, Min(i + 1, n - j));
          if (i == j) {
              fk[j + 1] += -1, fk[j + r] -= -1;
              fl[j + 1] += j + r, fl[j + r] -= j + r;
              fk[i - r + 1] += 1, fk[i] -= 1;
              fl[i - r + 1] += -(i - r), fl[i] -= -(i - r);
          } else {
              fk[j] += -1, fk[j + r] -= -1;
              fl[j] += j + r, fl[j + r] -= j + r;
              fk[i - r + 1] += 1, fk[i + 1] -= 1;
              fl[i - r + 1] += -(i - r), fl[i + 1] -= -(i - r);
          }
          int x = i - r, y = j + r; init_val += r;
          if (x < 0 || y >= n) continue;
          ++ r; r = getRadius(x - 1, y + 1, 0, Min(i + 1, n - j) - r);
          f[x][s[y] - 'a'] += r + 1;
          f[y][s[x] - 'a'] += r + 1;
      }
    ll best_change = 0, k = 0, l = 0;
    for (int i = 0; i < n; ++ i) {
        k += fk[i], l += fl[i];
        for (int j = 0; j < 26; ++ j)
          if (j + 'a' != s[i])
            best_change = Max(best_change, f[i][j] - (1ll * i * k + l));
    }
    printf("%lld\n", init_val + best_change);
    return 0;
}