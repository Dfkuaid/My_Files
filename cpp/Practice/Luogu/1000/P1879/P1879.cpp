#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define int long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 10010;
const int MOD = 1e8;
const int INF = 0x3fffffff;

int n,m,f[20][N],line[N],ans,check[N];
/*
inline void P(int k){
    for (int i = m - 1;i >= 0;i --)
      cout << ((k >> i) & 1);
    putchar('\n');
}
*/
signed main(){
    scanf("%lld%lld",&n,&m);
    for (int i = 1;i <= n;i ++){
        int t = 0;
        for (int j = 1;j <= m;j ++){
            scanf("%lld",&t);
            line[i] = (line[i] << 1) + (!t);
        }
    }
    for (int i = 0;i < (1 << m);i ++)
      check[i] = (i & (i >> 1)) ? 0 : 1;
    f[0][0] = 1;
    for (int i = 1;i <= n;i ++)
      for (int j = 0;j <= (1 << m) - 1;j ++){
          if (j & line[i] || !check[j]) continue;
          for (int k = 0;k <= (1 << m) - 1;k ++){
              if (k & line[i - 1] || k & j || !check[k]) continue;
              (f[i][j] += f[i - 1][k]) %= MOD;
          }
      }
    for (int i = 0;i <= (1 << m) - 1;i ++)
      (ans += f[n][i]) %= MOD;
    printf("%lld",ans);
    return 0;
}
