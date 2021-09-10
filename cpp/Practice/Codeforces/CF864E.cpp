#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 110;
const int M = 2010;
const int INF = 0x3fffffff;

struct T{
    int t,d,p;
    int ind;
};T a[N];

int n,f[N][M],g[N][M],maxn = -INF,ans = -INF;
int list[N],cnt,ans1,ans2;

inline int cmp(const T &x,const T &y){
    return x.d < y.d;
}

inline int Max(const int &x,const int &y){
    return x > y ? x : y;
}

inline void Path(int k,int t){
    if (k <= 0) return;
    Path(k - 1,g[k][t]);
    if (f[k][t] != f[k - 1][t])
      list[++ cnt] = k;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++){
        scanf("%d%d%d",&a[i].t,&a[i].d,&a[i].p);
        a[i].ind = i;
    }
    sort(a + 1,a + 1 + n,cmp);
    for (int i = 1;i <= n;i ++){
        for (int j = 1;j <= 2000;j ++)
          f[i][j] = f[i - 1][j],g[i][j] = j;
        for (int j = a[i].d - 1;j >= a[i].t;j --)
          if (f[i][j] < f[i - 1][j - a[i].t] + a[i].p){
              f[i][j] = f[i - 1][j - a[i].t] + a[i].p;
              g[i][j] = j - a[i].t;
          }  
    }
    for (int j = 1;j <= 2000;j ++)
      if (f[n][j] > ans) ans = f[n][j],ans2 = j;
    Path(n,ans2);
    printf("%d\n%d\n",ans,cnt);
    for (int i = 1;i <= cnt;i ++)
      printf("%d ",a[list[i]].ind);
    return 0;
}
