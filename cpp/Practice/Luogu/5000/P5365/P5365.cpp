#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define int long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 1000100;
const int INF = 0x3fffffff;

int n,m,f[N],k[N],w[N],sum,ans;

signed main(){
    f[0] = 1;
    scanf("%lld%lld",&n,&m);
    for (int i = 1;i <= n;i ++)
      scanf("%lld",&k[i]);
    for (int i = 1;i <= n;i ++)
      scanf("%lld",&w[i]),sum += k[i] * w[i];
    for (int i = 1;i <= n;i ++)
      for (int j = sum;j >= 0;j --)
        for (int o = 1;o <= k[i];o ++)
          if (j >= o * w[i])
            f[j] = max(f[j],f[j - o * w[i]] * o);
    while (f[ans] <= m && ans <= sum) ans ++;
    cout << ans;
    return 0;
}
