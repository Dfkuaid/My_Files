/*MLE 91pts*/
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100002;
const int M = 320;
const int INF = 0x3fffffff;

int n,len,id[N],sub[M][2],a[N],q,ncnt;
int cnt[M][N],sum[M][N],st[N],vis[N],mxc[M][M];

template <typename T>
inline T Max(const T a,const T b){
    return a > b ? a : b;
}

inline void Disc(int *k){
    for (int i = 1;i <= n;i ++)
      st[i] = k[i];
    sort(st + 1,st + n + 1);
    ncnt = unique(st + 1,st + n + 1) - st - 1;
    for (int i = 1;i <= n;i ++)
      k[i] = lower_bound(st + 1,st + ncnt + 1,k[i]) - st;
}

inline void divide(){
    len = sqrt(n); 
    for (int i = 1;i <= n;i ++)
      id[i] = (i - 1) / len + 1;
    for (int i = 1;i <= id[n];i ++){
        sub[i][0] = (i - 1) * len + 1;
        sub[i][1] = i * len;
    }
    sub[id[n]][1] = min(sub[id[n]][1],n);
}

inline int query(int x,int y){
    int l = id[x],r = id[y],res = 0;
    if (l == r){
        for (int i = x;i <= y;i ++)
          res = Max(res,++ vis[a[i]]);
        for (int i = x;i <= y;i ++)
          vis[a[i]] = 0;
        return res;
    }
    for (int i = x;i <= sub[l][1];i ++)
      res = Max(res,(++ vis[a[i]]) + sum[r - 1][a[i]] - sum[l][a[i]]);
    for (int i = sub[r][0];i <= y;i ++)
      res = Max(res,(++ vis[a[i]]) + sum[r - 1][a[i]] - sum[l][a[i]]);
    res = Max(res,mxc[l + 1][r - 1]);
    for (int i = x;i <= sub[l][1];i ++) vis[a[i]] = 0;
    for (int i = sub[r][0];i <= y;i ++) vis[a[i]] = 0;
    return res;
}

int main(){
    scanf("%d%d",&n,&q);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&a[i]);
    Disc(a);divide();
    for (int i = 1;i <= n;i ++){
        cnt[id[i]][a[i]] ++;
        if (cnt[id[i]][a[i]] > mxc[id[i]][id[i]])
          mxc[id[i]][id[i]] = cnt[id[i]][a[i]];
//          mx[id[i]][id[i]] = a[i];
    }
    for (int i = 1;i <= id[n];i ++)
      for (int j = 1;j <= ncnt;j ++)
        sum[i][j] = sum[i - 1][j] + cnt[i][j];
    for (int len = 2;len <= id[n];len ++)
      for (int l = 1;l + len <= id[n] + 1;l ++){
          int r = l + len - 1;
          for (int i = sub[r][0];i <= sub[r][1];i ++){
               int upd = sum[r - 1][a[i]] - sum[l - 1][a[i]] + (++ vis[a[i]]);
               if (mxc[l][r] < upd) mxc[l][r] = upd;//mx[l][r] = a[i],
          }
          for (int i = sub[r][0];i <= sub[r][1];i ++) vis[a[i]] = 0;
          if (mxc[l][r] < mxc[l][r - 1])
            mxc[l][r] = mxc[l][r - 1];//,mx[l][r] = mx[l][r - 1];
      }
    while (q --){
        int l,r;scanf("%d%d",&l,&r);
        printf("%d\n",query(l,r));
    }
    return 0;
}
