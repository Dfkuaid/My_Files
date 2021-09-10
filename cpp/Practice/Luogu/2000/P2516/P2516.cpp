/*60pts MLE*/
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
int f[N][N],g[N][N];

int main(){
    scanf("%s%s",a,b);
    for (int i = 0;i < strlen(a);i ++) g[i][0] = 1;
    for (int i = 0;i < strlen(b);i ++) g[0][i] = 1;
    for (int i = 1;i < strlen(a);i ++)
      for (int j = 1;j < strlen(b);j ++){
          if (a[i - 1] == b[j - 1]){
              f[i][j] = f[i - 1][j - 1] + 1;
              g[i][j] = g[i - 1][j - 1];
              if (f[i][j] == f[i - 1][j]) (g[i][j] += g[i - 1][j]) %= MOD;
              if (f[i][j] == f[i][j - 1]) (g[i][j] += g[i][j - 1]) %= MOD;
          }
          else{
              f[i][j] = max(f[i - 1][j],f[i][j - 1]);
              if (f[i - 1][j] > f[i][j - 1])
                g[i][j] = g[i - 1][j];
              else if (f[i - 1][j] < f[i][j - 1])
                g[i][j] = g[i][j - 1];
              else if (f[i][j] != f[i - 1][j - 1])
                g[i][j] = (g[i - 1][j] + g[i][j - 1]) % MOD;
              else g[i][j] = (g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1]) % MOD;
          }
      }
    printf("%d\n%d",f[strlen(a) - 1][strlen(b) - 1],g[strlen(a) - 1][strlen(b) - 1]);
    return 0;
}
