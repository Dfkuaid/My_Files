#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define int long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 110;
const int INF = 0x3fffffff;
const int MOD = 9999973;

int n,m,f[N][N][N],ans;

signed main(){
    scanf("%d%d",&n,&m);
    f[1][m][0] = 1,f[1][m - 2][2] = m * (m - 1) / 2,f[1][m - 1][1] = m;
    for (int i = 1;i < n;i ++)
      for (int j = 0;j <= m;j ++)
        for (int k = 0;k <= m;k ++){
            if (!f[i][j][k]) continue;
            f[i + 1][j][k] += f[i][j][k];
            if (j >= 1) (f[i + 1][j - 1][k + 1] += f[i][j][k] * j % MOD) %= MOD;
            if (k >= 1) (f[i + 1][j][k - 1] += f[i][j][k] * k % MOD) %= MOD;
            if (j >= 1) (f[i + 1][j - 1][k] += f[i][j][k] * j * k % MOD) %= MOD;
            if (j >= 2) (f[i + 1][j - 2][k + 2] += f[i][j][k] * j * (j - 1) / 2 % MOD) %= MOD;
            if (k >= 2) (f[i + 1][j][k - 2] += f[i][j][k] * k * (k - 1) / 2 % MOD) %= MOD;
        }
    for (int i = 0;i <= m;i ++)
      for (int j = 0;j <= m;j ++)
        (ans += f[n][i][j]) %= MOD;
    printf("%d",ans % MOD);
    return 0;
}
