#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define int long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 400;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;

int n,m,list[N][N],limit[N][3],f[N][N][N],ans;

inline bool check(int a,int b,int c){
    int R = a;
    int num = 1;
    for (int i = 1;i <= list[R][0];i ++){
        num = 1;
        if (limit[list[R][i]][0] <= b) num ++;
        if (limit[list[R][i]][0] <= c) num ++;
        if (num != limit[list[R][i]][2]) return false;
    }
    return true;
}

inline int Max(ll a,ll b){
    return a > b ? a : b;
}

signed main(){
    scanf("%lld%lld",&n,&m);
    for (int i = 1;i <= m;i ++){
        scanf("%lld%lld%lld",&limit[i][0],&limit[i][1],&limit[i][2]);
        list[limit[i][1]][++ list[limit[i][1]][0]] = i;
    }
    f[1][0][0] = 1;
    for (int i = 1;i <= n;i ++)
      for (int j = 0;j < i;j ++)
        for (int k = 0;k <= Max(0,j - 1);k ++){
            if (!check(i,j,k)) continue;
            (f[i + 1][j][k] += f[i][j][k]) %= MOD;
            (f[i + 1][i][j] += f[i][j][k]) %= MOD;
            (f[i + 1][i][k] += f[i][j][k]) %= MOD;
            if (i == n) (ans += f[i][j][k]) %= MOD;
        }
    printf("%lld",(ans * 3) % MOD);
    return 0;
}
