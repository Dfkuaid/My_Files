#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <complex>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 10000010;
const int INF = 0x3fffffff;
const double PI = acos(-1);

typedef complex <double> cp;

int n,m,t = 1,res[N],ta[N],tb[N],lim,r[N];
cp ca[N],cb[N];

inline void fft(cp *a,int type){
    for (int i = 0;i < t;i ++)
      if (i < r[i]) swap(a[i],a[r[i]]);
    for (int mid = 1;mid < t;mid <<= 1){
        cp OMG(cos(PI / mid),type *sin(PI / mid));
        for (int R = mid << 1,j = 0;j < t;j += R){
            cp omg(1,0);
            for (int k = 0;k < mid;k ++,omg = omg * OMG){
                cp tmp1 = a[j + k],tmp2 = omg * a[j + mid + k];
                a[j + k] = tmp1 + tmp2;
                a[j + mid + k] = tmp1 - tmp2;
            }
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    while (t <= n + m) t <<= 1,lim ++;
    for (int i = 0;i <= n;i ++){
        scanf("%d",&ta[i]);
        ca[i].real(ta[i]);
    }
    for (int i = 0;i <= m;i ++){
        scanf("%d",&tb[i]);
        cb[i].real(tb[i]);
    }
    for (int i = 0;i < t;i ++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lim - 1));
    fft(ca,1);fft(cb,1);
    
    
    for (int i = 0;i < t;i ++)
      cout << ca[i].real() << " ";
    cout << endl;
    for (int i = 0;i < t;i ++)
      cout << cb[i].real() << " ";
    cout << endl;
    
    
    for (int i = 0;i < t;i ++) ca[i] *= cb[i];
    fft(ca,-1);
    for (int i = 0;i < t;i ++)
      res[i] = floor(ca[i].real() / t + 0.5);
    for (int i = 0;i <= n + m;i ++)
      cout << res[i] << " ";
    return 0;
}
