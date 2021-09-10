#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 2010;
const int INF = 0x3fffffff;

int n,m,w[N];
int f[N],g[N];

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&w[i]);
    f[0] = 1,g[0] = 1;
    for (int i = 1;i <= n;i ++)
      for (int j = m;j >= w[i];j --)
        (f[j] += f[j - w[i]]) %= 10;
    for (int i = 1;i <= n;i ++){
        for (int j = 1;j <= m;j ++){
            if (j < w[i]) g[j] = f[j] % 10;
            else g[j] = (f[j] - g[j - w[i]] + 10) % 10;
            printf("%d",g[j]);
        }
        putchar('\n');
    }
    return 0;
}
