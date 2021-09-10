#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <tr1/unordered_map>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;
using namespace tr1;

const int N = 6000010;
const int INF = 0x3fffffff;
const int L = 1700000;

bool vis[N];
int mu[N],phi[N],sum1[N],n,prim[N],cnt,t;
ll sum2[N];

unordered_map <int,int> w1;
unordered_map <ll,ll> w2;

inline void prework(int x){
    phi[1] = mu[1] = 1;
    for (int i = 2;i <= x;i ++){
        if (!vis[i]){
            prim[++ cnt] = i;
            phi[i] = i - 1;mu[i] = -1;
        }
        for (int j = 1;j <= cnt && prim[j] * i <= x;j ++){
            vis[prim[j] * i] = 1;
            if (i % prim[j] == 0){
                phi[prim[j] * i] = phi[i] * prim[j];
                break;
            }
            else {
                mu[i * prim[j]] = -mu[i];
                phi[i * prim[j]] = phi[i] * (prim[j] - 1);
            }
        }
    }
    for (int i = 1;i <= x;i ++)
      sum1[i] = sum1[i - 1] + mu[i],sum2[i] = sum2[i - 1] + phi[i];
}

inline int djsmu(int x){
    if (x <= L) return sum1[x];
    if (w1[x]) return w1[x];
    int ans = 1;
    for (ll l = 2,r;l <= x;l = r + 1){
        r = x / (x / l);
        ans -= (r - l + 1) * djsmu(x / l);
    }
    return w1[x] = ans;
}

inline ll djsphi(ll x){
    if (x <= L) return sum2[x];
    if (w2[x]) return w2[x];
    ll ans = x * (1 + x) / 2;
    for (ll l = 2,r;l <= x;l = r + 1){
        r = x / (x / l);
        ans -= (r - l + 1) * djsphi(x / l);
    }
    return w2[x] = ans;
}


int main(){
    scanf("%d",&t);
    prework(L);
    while (t --){
        scanf("%d",&n);
        printf("%lld %d\n",djsphi(n),djsmu(n));
    }
    return 0;
}
