#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

char s[N]; int n, cnt[N][26], standard[26];

inline bool check(int l, int r) {
    for (int i = 0; i < 26; ++ i)
      if (cnt[r][i] - cnt[l - 1][i] != standard[i])
        return false;
    return true;
}

int main() {
    scanf("%s", s); n = strlen(s);
    for (int i = 0; i < n; ++ i)
      ++ cnt[i + 1][s[i] - 'a'];
    for (int i = 1; i <= n; ++ i)
      for (int j = 0; j < 26; ++ j)
        cnt[i][j] += cnt[i - 1][j];
    for (int l = 1; l <= n >> 1; ++ l) if (!(n % l)) {
        int is_answer = true;
        for (int i = 0; i < 26; ++ i)
          standard[i] = cnt[l][i];
        for (int i = l + 1; i <= n; i += l)
          if (!check(i, i + l - 1)) {
              is_answer = false; break;
          }
        if (is_answer) {
            for (int i = 0; i < l; ++ i)
              putchar(s[i]);
            return 0;
        }
    }
    puts("-1"); return 0;
}