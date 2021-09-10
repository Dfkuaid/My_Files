#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 200010;
const int INF = 0x3fffffff;

int t, r, p, s, a[3][20][N], cnt[3][20][3], lg[N], ans[N], tmp[N];

inline void get_base() {
    for (int i = 1; i <= 100000; ++ i)
      lg[i] = lg[i >> 1] + 1;
    mset(a, -1); a[0][1][1] = 0;
    a[1][1][1] = 1, a[2][1][1] = 2;
    for (int i = 1; i < 16; ++ i)
      for (int j = 1 << (i - 1); j < (1 << i); ++ j)
        for (int k = 0; k <= 2; ++ k) {
            if (a[k][i][j] == 0) {
                a[k][i + 1][j << 1] = 0;
                a[k][i + 1][j << 1 | 1] = 1;
            } else if (a[k][i][j] == 1) {
                a[k][i + 1][j << 1] = 1;
                a[k][i + 1][j << 1 | 1] = 2;
            } else if (a[k][i][j] == 2) {
                a[k][i + 1][j << 1] = 0;
                a[k][i + 1][j << 1 | 1] = 2;
            }
        }
    cnt[0][1][0] = cnt[1][1][1] = cnt[2][1][2] = 1;
    for (int i = 2; i <= 16; ++ i) {
        for (int j = 0; j <= 2; ++ j) {
            cnt[0][i][j] = cnt[0][i - 1][j] + cnt[1][i - 1][j];
            cnt[1][i][j] = cnt[1][i - 1][j] + cnt[2][i - 1][j];
            cnt[2][i][j] = cnt[0][i - 1][j] + cnt[2][i - 1][j];
        }
    }
}

inline int check(int n, int i, int j, int k) {
    for (int o = 0; o <= 2; ++ o)
      if (cnt[o][n][0] == i && cnt[o][n][1] == j && cnt[o][n][2] == k)
        return o;
    return -1;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d", &t); get_base();
    while (t --) {
        scanf("%d%d%d", &r, &p, &s);
        int n = r + p + s;
        int op = check(lg[n], p, r, s);
        if (!(~op)) {printf("-1\n"); continue;}
        for (int i = 1 << (lg[n] - 1); i < 1 << lg[n]; ++ i)
          ans[i - (1 << (lg[n] - 1)) + 1] = a[op][lg[n]][i];
        for (int i = 2; i <= n; i <<= 1) {
            for (int j = 1; j <= n; j += i)
              for (int k = 1; k <= i >> 1; ++ k) {
                  if (ans[j + k - 1] < ans[j + (i >> 1) + k - 1]) break;
                  if (ans[j + k - 1] > ans[j + (i >> 1) + k - 1]) {
                      for (int l = j; l <= j + (i >> 1) - 1; ++ l)
                        swap(ans[l], ans[l + (i >> 1)]);
                      break;
                  }
              }
        }
        for (int i = 1; i <= n; ++ i)
          if (ans[i] == 0) printf("P");
          else if (ans[i] == 1) printf("R");
          else if (ans[i] == 2) printf("S");
        printf("\n");
    }
    return 0;
}