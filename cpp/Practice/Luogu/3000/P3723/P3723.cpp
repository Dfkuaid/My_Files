#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <complex>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 500010;
const double PI = acos(-1);
const int INF = 0x3fffffff;

typedef complex <double> cp;

ll t = 1,lt,r[N];
ll n,m,a[N],b[N],FV1,FV2,c,ans1,ans2;
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

int main(){
    scanf("%lld%lld",&n,&m);
    for (int i = 1;i <= n;i ++){
        scanf("%lld",&a[i]);
        f[n - i + 1].real(a[i]);
        FV1 += a[i] * a[i];
        FV2 += a[i];
    }
    for (int i = 1;i <= n;i ++){
        scanf("%lld",&b[i]);
        g[i].real(b[i]);
        g[i + n].real(b[i]);
        FV1 += b[i] * b[i];
        FV2 -= b[i];
    }
    c = - FV2 / n;
    ans1 = min(min(n * c * c + 2 * c * FV2 + FV1,
        n * (c - 1) * (c - 1) + 2 * (c - 1) * FV2 + FV1),
        n * (c + 1) * (c + 1) + 2 * (c + 1) * FV2 + FV1);
    while (t <= 3 * n) t <<= 1,lt ++;
    for (int i = 0;i < t;i ++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lt - 1));
    fft(f,1),fft(g,1);
    for (int i = 0;i < t;i ++) f[i] *= g[i];
    fft(f,-1);
    for (int i = 1;i <= n;i ++)
      ans2 = max(ans2,(ll)(f[n + i].real() / t + 0.5));
    printf("%lld",ans1 - 2 * ans2);
    return 0;
}
