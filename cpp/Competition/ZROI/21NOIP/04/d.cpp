#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int MOD = 998244353;

int n, a[N], f[N], sum[N], mx[20][N], st[N], stp;

inline int GS(int l, int r) {return (sum[r] - sum[l - 1] + MOD) % MOD;}

int main() {
    scanf("%d", &n); f[0] = sum[0] = 1;
    for (int i = 1; i <= n; ++ i)
      scanf("%d", &a[i]), mx[0][i] = a[i];
    /*Get st-table.*/
    for (int i = 1; i <= 18; ++ i)
      for (int j = (1 << i); j <= n; ++ j)
        mx[i][j] = max(mx[i - 1][j], mx[i - 1][j - (1 << i - 1)]);
    /*st[] is a monotone stack which a[st[]] is monotonic increasing.*/
    for (int i = 1; i <= n; ++ i) {
        while (stp && a[st[stp]] >= a[i]) -- stp;
        int j = st[stp];
        for (int o = 18; ~o; -- o)
          if (j >= (1 << o) && mx[o][j] < a[i])
            j -= (1 << o);
        /*When j = 0, there are two cases:*/
        /*  1. stp = 0, it means that a[i] is the minnest one of a[1...i];*/
        /*  2. stp > 0, it means that a[i] is bigger than each of a[1...st[stp]],*/
        /*     and a[i] is the lower than each of a[st[stp] + 1...i - 1];*/
        /*At this time, all the status from st[stp] to i - 1 are legal.*/
        /*Else j > 0, it means that a[i] is lower than each of a[st[stp] + 1...i - 1],*/
        /*and a[i] is bigger than each of a[j + 1...st[stp]], but lower than a[j];*/
        if (j) {
            int k = *lower_bound(st + 1, st + stp + 1, j);
            /*j must not be in st[], so a[k] < a[i] < a[j].*/
            /*And a[k] is the minnest one which is lower than a[j] in a[j + 1...].*/
            f[i] = (f[k] - GS(j, k - 1) + MOD) % MOD;
            /*Find the pos that cannot be divided, and delete the lllegal status.*/
        }
        (f[i] += GS(st[stp], i - 1)) %= MOD;
        sum[i] = (sum[i - 1] + f[i]) % MOD, st[++ stp] = i;
    }
    printf("%d\n", f[n]); return 0;
}
