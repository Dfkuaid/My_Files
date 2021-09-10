#include <cmath>
#include <cstdio>
#include <complex>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 3e6 + 10;
const double PI = acos(-1);
const int INF = 0x3fffffff;

typedef complex <double> cp;

string sa,sb;
int lena,lenb,t = 1,lt,r[N],res[N];
cp a[N],b[N];

void fft(cp *A,int opt){
    for (int i = 0;i < t;i ++)
      if (i < r[i]) swap(A[i],A[r[i]]);
    for (int mid = 1;mid < t;mid <<= 1){
        cp OMG(cos(PI / mid),opt * sin(PI / mid));
        for (int R = mid << 1,j = 0;j < t;j += R){
            cp omg(1,0);
            for (int k = 0;k < mid;k ++,omg *= OMG){
                cp tmp1 = A[j + k],tmp2 = omg * A[j + mid + k];
                A[j + k] = tmp1 + tmp2;
                A[j + mid + k] = tmp1 - tmp2;
            }
        }
    }
}

int main(){
    cin >> sa >> sb;
    lena = sa.length();lenb = sb.length();
    while (t <= lena + lenb) t <<= 1,lt ++;
    for (int i = 0;i < lena;i ++)
      a[i].real((double)(sa[lena - i - 1] - '0'));
    for (int i = 0;i < lenb;i ++)
      b[i].real((double)(sb[lenb - i - 1] - '0'));
    for (int i = 0;i < t;i ++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lt - 1));
    fft(a,1);fft(b,1);
    for (int i = 0;i < t;i ++) a[i] *= b[i];
    fft(a,-1);
    for (int i = 0;i < t;i ++){
        res[i] += floor(a[i].real() / t + 0.5);
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }
    while (!res[t] && t >= 1) t --;
    t ++;
    for (int i = t - 1;i >= 0;i --)
      cout << res[i];
    return 0;
}
