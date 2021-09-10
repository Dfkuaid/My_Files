/*O(n^2)*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int n,t,a[N],cnt,ans;

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&a[i]);
    scanf("%d",&t);
    for (int i = 1;i <= n;i ++){
        int r = a[i] + t;cnt = 0;
        for (int j = 1;j <= n;j ++)
          if (a[i] <= a[j] && a[j] <= r)
            cnt ++;
        ans = max(ans,cnt);
    }
    cout << ans;
    return 0;
}