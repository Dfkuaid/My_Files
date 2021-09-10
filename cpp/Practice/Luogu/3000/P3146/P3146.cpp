#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 510;
const int INF = 0x3fffffff;

int n,a[N],ans,f[N][N];

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++){
        scanf("%d",&a[i]);
        f[i][i] = a[i];
        ans = Max(ans,f[i][i]);
    }
    for (int ln = 2;ln <= n;ln ++)
      for (int l = 1;l + ln - 1<= n;l ++){
          int r = l + ln - 1;
          for (int k = l;k < r;k ++)
            if (f[l][k] == f[k + 1][r]){
                f[l][r] = Max(f[l][k] + 1,f[l][r]);
                ans = Max(ans,f[l][r]);
            }
      }
    printf("%d",ans);
    return 0;
}
