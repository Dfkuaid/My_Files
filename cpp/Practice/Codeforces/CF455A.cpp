#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

ll n,a[N],f[N][2],l;

int main(){
    scanf("%lld",&n);
    for (int i = 1;i <= n;i ++){
        ll x;
        scanf("%lld",&x);
        l = max(l,x);
        a[x] ++;
    }
    f[1][1] = a[1];
    for (int i = 2;i <= l;i ++){
        f[i][0] = max(f[i - 1][0],f[i - 1][1]);
        f[i][1] = f[i - 1][0] + i * a[i];
    }
    printf("%lld",max(f[l][0],f[l][1]));
    return 0;
}
