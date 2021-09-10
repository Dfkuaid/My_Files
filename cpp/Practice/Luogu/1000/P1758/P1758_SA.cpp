/*O2->100pts NO_O2->70pts TLE*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 1010;
const int INF = 0x3fffffff;
const int MOD = 1024523;

int n,m,f[N][N];
string u,d;

int main(){
    scanf("%d%d",&n,&m);
    cin >> u >> d;
    f[0][0] = 1;
    for (int k = 1;k <= n + m;k ++)
      for (int i = k;i >= 0;i --)
        for (int j = k;j >= 0;j --){
            if (!(k - i) || !(k - j) || d[k - i - 1] != d[k - j - 1])
              f[i][j] = 0;
            if (i && j && u[i - 1] == u[j - 1])
              (f[i][j] += f[i - 1][j - 1]) %= MOD;
            if (i && (k - j) && u[i - 1] == d[k - j - 1])
              (f[i][j] += f[i - 1][j]) %= MOD;
            if ((k - i) && j && d[k - i - 1] == u[j - 1])
              (f[i][j] += f[i][j - 1]) %= MOD;
        }
    printf("%d",f[n][n] % MOD);
    return 0;
}
