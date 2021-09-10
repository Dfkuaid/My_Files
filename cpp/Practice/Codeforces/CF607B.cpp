#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 510;
const int INF = 0x3fffffff;

int n,a[N],f[N][N],check[N][N];

inline int Min(const int &a,const int &b){
    return a < b ? a : b;
}

int main(){
    mset(f,0x3f);
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&a[i]);
    for (int l = 1;l <= n;l ++)
      for (int r = l + 1;r <= n;r ++)
        for (int i = 0;i <= (r - l + 1) / 2;i ++)
          if (a[l + i] != a[r - i]){check[l][r] = 1;break;}
    for (int len = 1;len <= n;len ++)
      for (int l = 1;l + len - 1 <= n;l ++){
          int r = l + len - 1;
          if (!check[l][r]){f[l][r] = 1;continue;}
          if (a[l] == a[r] && r - l > 1) f[l][r] = f[l + 1][r - 1];
          for (int k = l;k < r;k ++)
            f[l][r] = Min(f[l][r],f[l][k] + f[k + 1][r]);
      }
    printf("%d",f[1][n]);
    return 0;
}
