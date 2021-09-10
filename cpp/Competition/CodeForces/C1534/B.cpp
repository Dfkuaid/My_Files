#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 1000100;
const int INF = 0x3fffffff;

int t,n,a[N];
ll ans,sum1,sum2;

int main(){
    scanf("%d",&t);
    while (t --){
        mset(a,0);
        ans = 0,sum1 = 0,sum2 = 0;
        scanf("%d",&n);
        for (int i = 1;i <= n;i ++){
          scanf("%d",&a[i]);
          sum1 += a[i];
        }
        for (int i = 1;i <= n;i ++)
          if (a[i] > a[i - 1] && a[i] > a[i + 1])
            a[i] = max(a[i - 1],a[i + 1]);
        for (int i = 1;i <= n;i ++){
            if (a[i] == a[i + 1] && a[i] >= a[i - 1] && a[i + 1] >= a[i + 2])
              a[i] = a[i + 1] = max(a[i - 1],a[i + 2]);
        }
        for (int i = 1;i <= n;i ++){
            sum2 += a[i];
            if (a[i] > a[i - 1])
              ans += a[i] - a[i - 1];
            if (a[i] > a[i + 1])
              ans += a[i] - a[i + 1];
        }
        ans += sum1 - sum2;
        printf("%lld\n",ans);
    }
    // system("pause");
    return 0;
}