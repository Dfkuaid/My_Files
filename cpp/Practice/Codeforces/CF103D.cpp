#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 301000;
const int INF = 0x3fffffff;

ll ans[N],sum[N];
ll n,m,size,val[N];
ll t[N],k[N];

vector <ll> v[550];

int main(){
    scanf("%lld",&n);
    size = sqrt(n);
    for (int i = 1;i <= n;i ++)
      scanf("%lld",&val[i]);
    scanf("%lld",&m);
    for (int p = 1;p <= m;p ++){
        scanf("%lld%lld",&t[p],&k[p]);
        if (k[p] >= size)
          for (ll i = t[p];i <= n;i += k[p])
            ans[p] += val[i];
        else
          v[k[p]].push_back(p);
    }
    for (ll i = 1;i < size;i ++){
        if (v[i].empty()) continue;
        mset(sum,0);
        for (ll j = n;j;j --)
          sum[j] = sum[j + i] + val[j];
        while (!v[i].empty()){
            ans[v[i].back()] = sum[t[v[i].back()]];
            v[i].pop_back();
        }
    }
    for (int i = 1;i <= m;i ++)
      cout << ans[i] << endl;
    return 0;
}
