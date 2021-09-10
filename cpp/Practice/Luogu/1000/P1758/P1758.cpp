/*40pts MLE*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 510;
const int INF = 0x3fffffff;
const int MOD = 1024523;

int n,m,f[N][N][N];
string u,d;

int main(){
    scanf("%d%d",&n,&m);
    cin >> u >> d;
    f[0][0][0] = 1;
    for (int k = 1;k <= n + m;k ++)
      for (int i = 0;i <= k;i ++)
        for (int j = 0;j <= k;j ++){
            if (i && j && u[i - 1] == u[j - 1])
              (f[k][i][j] += f[k - 1][i - 1][j - 1]) %= MOD;
            if (i && (k - j) && u[i - 1] == d[k - j - 1])
              (f[k][i][j] += f[k - 1][i - 1][j]) %= MOD;
            if ((k - i) && j && d[k - i - 1] == u[j - 1])
              (f[k][i][j] += f[k - 1][i][j - 1]) %= MOD;
            if ((k - i) && (k - j) && d[k - i - 1] == d[k - j - 1])
              (f[k][i][j] += f[k - 1][i][j]) %= MOD;
        }
    printf("%d",f[n + m][n][n] % MOD);
    return 0;
}
