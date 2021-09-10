#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t,n,a[N],mx,mn;

int main(){
    scanf("%d",&t);
    while (t --){
        scanf("%d",&n);
        mx = mn = 0;
        for (int i = 1;i <= n;i ++){
            scanf("%d",&a[i]);
            mx = max(mx,a[i]);
            mn = min(mn,a[i]);
        }
        if (mn < 0){
            printf("NO\n");
            continue;
        }
        printf("YES\n%d\n",mx + 1);
        for (int i = 0;i <= mx;i ++)
          printf("%d ",i);
        putchar('\n');
    }
    // system("pause");
    return 0;
}