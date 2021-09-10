/*滚动数组优化 100pts*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 5010;
const int MOD = 1e8;
const int INF = 0x3fffffff;

char a[N],b[N];
int f[3][N],g[3][N],lena,lenb;

inline int Max(const int &x,const int &y){
    return x > y ? x : y;
}

int main(){
    scanf("%s%s",a,b);
    lena = strlen(a);lenb = strlen(b);
    for (int i = 0;i < 3;i ++) g[i][0] = 1;
    for (int i = 0;i < lenb;i ++) g[0][i] = 1;
    for (int i = 1;i < lena;i ++)
      for (int j = 1;j < lenb;j ++){
        int now = i & 1,lst = (i - 1) & 1;
          if (a[i - 1] == b[j - 1]){
              f[now][j] = f[lst][j - 1] + 1;g[now][j] = g[lst][j - 1];
              if (f[now][j] == f[lst][j]) (g[now][j] += g[lst][j]) %= MOD;
              if (f[now][j] == f[now][j - 1]) (g[now][j] += g[now][j - 1]) %= MOD;
          }
          else{
              f[now][j] = Max(f[lst][j],f[now][j - 1]);
              if (f[lst][j] > f[now][j - 1]) g[now][j] = g[lst][j];
              else if (f[lst][j] < f[now][j - 1]) g[now][j] = g[now][j - 1];
              else if (f[now][j] != f[lst][j - 1]) g[now][j] = (g[lst][j] + g[now][j - 1]) % MOD;
              else g[now][j] = (g[lst][j] + g[now][j - 1] - g[lst][j - 1]) % MOD;
          }
      }
    printf("%d\n%d",f[(lena - 1) & 1][lenb - 1],g[(lena - 1) & 1][lenb - 1]);
    return 0;
}
