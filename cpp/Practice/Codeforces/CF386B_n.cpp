/*O(n)*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int n,a[N],b[N],sum[N],T,mx,ans;

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++){
        scanf("%d",&a[i]);
        b[a[i]] ++;
        mx = Max(mx,a[i]);
    }
    scanf("%d",&T);
    for (int i = 1;i <= mx + T + 1;i ++)
      sum[i] = sum[i - 1] + b[i];
    for (int i = 1;i <= n;i ++)
      ans = Max(ans,sum[a[i] + T] - sum[a[i] - 1]);
    printf("%d",ans);
    return 0;
}
