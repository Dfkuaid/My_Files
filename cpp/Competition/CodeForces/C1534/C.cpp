#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 500010;
const int MOD = 1e9 + 7;
const int INF = 0x3fffffff;

int t,n,a[2][N],v[N],p[2][N],ans = 1;

inline void get_ring(int k,int f){
    if (v[k]) return;
    v[k] = 1;
    get_ring(p[f][a[f ^ 1][k]],f);
}

int main(){
    scanf("%d",&t);
    while (t --){
        mset(v,0);ans = 1;
        scanf("%d",&n);
        for (int i = 1;i <= n;i ++){
            scanf("%d",&a[0][i]);
            p[0][a[0][i]] = i;
        }
        for (int i = 1;i <= n;i ++){
            scanf("%d",&a[1][i]);
            p[1][a[1][i]] = i;
        }
        for (int i = 1;i <= n;i ++)
          if (!v[i]){
              (ans <<= 1) %= MOD;
              get_ring(i,0);
          }
        cout << ans << endl;
    }
    system("pause");
    return 0;
}