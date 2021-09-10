#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 2050;
const int M = 110;
const int INF = 0x3fffffff;

int n,m,check[N],f[N][N][2],line[M],ans,T,S[N],cnt,cnt1,cnt2;

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

int main(){
    cin >> n >> m;T = (1 << m);
    for (int i = 1;i <= n;i ++){
        char c;
        for (int j = 1;j <= m;j ++){
            cin >> c;
            line[i] = (line[i] << 1) + (c == 'H');
        }
    }
    for (int i = 0;i < (1 << m);i ++)
      S[i] = __builtin_popcount(i);
    for (int i = 0;i < (1 << m);i ++){
        check[i] = ((i & (i << 1)) || (i & (i << 2))) ? 0 : 1;
        if (!check[i] || i & line[1]) continue;
        f[0][i][1] = S[i];
    }
    for (int i = 0;i < (1 << m);i ++)
      for (int j = 0;j < (1 << m);j ++)
        if(!(!check[i] || !check[j] || i & j || i & line[1] || j & line[2]))
          f[i][j][0] = f[0][i][1] + S[j];
    for (int i = 3;i <= n;i ++)
      for (int j = 0;j < (1 << m);j ++){
          if (!check[j] || j & line[i - 1]) continue;
          for (int k = 0;k < (1 << m);k ++){
              if (!check[k] || k & line[i] || j & k) continue;
              for (int l = 0;l < (1 << m);l ++){
                  if (!check[l] || l & line[i - 2] || j & l || l & k) continue;
                  f[j][k][i % 2] = Max(f[j][k][i % 2],f[l][j][(i - 1) % 2] + S[k]);
              }
          }
      }
    for (int i = 0;i < (1 << m);i ++)
      for (int j = 0;j < (1 << m);j ++)
        ans = Max(ans,f[j][i][n % 2]);
    cout << ans;
    return 0;
}