#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define int long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int f[N],w[5],n,ms = -INF;
int Q[N][5],A[N];

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

signed main(){
    scanf("%lld%lld%lld%lld%lld",&w[1],&w[2],&w[3],&w[4],&n);
    for (int i = 1;i <= n;i ++){
        scanf("%lld%lld%lld%lld%lld",&Q[i][1],&Q[i][2],&Q[i][3],&Q[i][4],&Q[i][0]);
        ms = Max(ms,Q[i][0]);
    }
    f[0] = 1;
    for (int i = 1;i <= 4;i ++)
      for (int j = w[i];j <= ms;j ++)
        f[j] += f[j - w[i]];
    for (int i = 1;i <= n;i ++)
      for (int k = 0;k < 16;k ++){
          int opt = __builtin_parity(k) ? -1 : 1,x = 0;
          for (int j = 1;j <= 4;j ++)
            x += ((k >> (j - 1)) & 1) * w[j] * (Q[i][j] + 1);
          if (x > Q[i][0]) continue;
          A[i] += opt * f[Q[i][0] - x];
      }
    for (int i = 1;i <= n;i ++)
      printf("%lld\n",A[i]);
    return 0;
}
