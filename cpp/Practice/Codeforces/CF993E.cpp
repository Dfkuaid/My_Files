#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <complex>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 700010;
const double PI = acos(-1);
const int INF = 0x3fffffff;

typedef complex <double> cp;

ll a[N],n,sum[N];
ll r[N],x,ans;
ll t = 1,lt,cnt;
cp f[N],g[N];

inline void fft(cp *A,int opt){
    for (int i = 0;i < t;i ++)
      if (i < r[i]) swap(A[i],A[r[i]]);
    for (int mid = 1;mid < t;mid <<= 1){
        cp OMG(cos(PI / mid),opt * sin(PI / mid));
        for (int R = mid << 1,l = 0;l < t;l += R){
            cp omg(1,0);
            for (int k = 0;k < mid;k ++,omg *= OMG){
                cp tmp1 = A[l + k],tmp2 = omg * A[l + mid + k];
                A[l + k] = tmp1 + tmp2;
                A[l + mid + k] = tmp1 - tmp2;
            }
        }
    }
}

inline ll RS(int x){
    return (ll)(1 + x) * x / 2;
}

int main(){
    scanf("%lld%lld",&n,&x);
    for (int i = 1;i <= n;i ++){
        scanf("%lld",&a[i]);
        if (a[i] < x) a[i] = 1;
        else a[i] = 0;
    }
    f[0].real(1);g[n].real(1);
    for (int i = 1;i <= n;i ++){
        sum[i] = sum[i - 1] + a[i];
        f[sum[i]].real(f[sum[i]].real() + 1);
        g[n - sum[i]].real(g[n - sum[i]].real() + 1);
    }
    while (t <= 2 * n + 2) t <<= 1,lt ++;
    for (int i = 0;i < t;i ++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lt - 1));
    fft(f,1);fft(g,1);
    for (int i = 0;i < t;i ++) f[i] *= g[i];
    fft(f,-1);
    for (int i = 1;i <= n;i ++)
      if (sum[i] != sum[i - 1])
        ans += RS(cnt),cnt = 0;
      else cnt ++;
    ans += RS(cnt);
    printf("%lld ",ans);
    for (int i = n + 1;i <  2 * n + 1;i ++)
     printf("%lld ",(ll)(f[i].real() / t + 0.5));
    return 0;
}
