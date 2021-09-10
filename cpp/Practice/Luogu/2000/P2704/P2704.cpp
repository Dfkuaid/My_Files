#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 1050;
const int M = 110;
const int INF = 0x3fffffff;

int n,m,check[N],f[N][N][M],line[M],ans;

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;i ++){
        char c;
        for (int j = 1;j <= m;j ++){
            scanf("%c",&c);
            line[i] = (line[i] << 1) + (c == 'H');
        }
        getchar();
    }
    for (int i = 1;i < (1 << m);i ++){
        check[i] = ((i & (i >> 1)) || (i & (i >> 2))) ? 0 : 1;
        if (!check[i] || i & line[1]) continue;
        f[0][i][1] = Max(f[0][i][1],__builtin_popcount(i));
    }
    for (int i = 2;i <= n;i ++)
      for (int j = 0;j < (1 << m);j ++){
          if (!check[j] || j & line[i]) continue;
          for (int k = 0;k < (1 << m);k ++){
              if (!check[k] || k & line[i - 1] || j & k) continue;
              for (int l = 0;l < (1 << m);l ++){
                  if (!check[l] || l & line[i - 2] || j & l || l & k)
                    continue;
                  f[k][j][i] = Max(f[k][j][i],f[l][k][i - 1] + __builtin_popcount(j));
              }
              ans = Max(ans,f[k][j][i]);
          }
      }
    printf("%d",ans);
    return 0;
}
