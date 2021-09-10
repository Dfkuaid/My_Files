#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int n,m,len;
ll a[N],sum[N];
int id[N],sub[N][2];
int tag[N];

inline void check(int k){
    bool flag = true;
    for (int i = sub[k][0];i <= sub[k][1];i ++)
      if (a[i] > 1){
          flag = false;
          break;
      }
    if (flag)
      tag[k] = true;
}

inline void change(int l,int r){
    int lp = id[l],rp = id[r];
    if (lp == rp){
        if (tag[lp]) return;
        for (int i = l;i <= r;i ++){
            sum[lp] -= a[i];
            a[i] = sqrt(a[i]);
            sum[lp] += a[i];
        }
        check(lp);
        return;
    }
    if (!tag[lp]){
        for (int i = l;i <= sub[lp][1];i ++){
            sum[lp] -= a[i];
            a[i] = sqrt(a[i]);
            sum[lp] += a[i];
        }
        check(lp);
    }
    if (!tag[rp]){
        for (int i = sub[rp][0];i <= r;i ++){
            sum[rp] -= a[i];
            a[i] = sqrt(a[i]);
            sum[rp] += a[i];
        }
        check(rp);
    }
    for (int i = lp + 1;i < rp;i ++)
      if (!tag[i]){
          sum[i] = 0;
          bool flag = true;
          for (int j = sub[i][0];j <= sub[i][1];j ++){
              a[j] = sqrt(a[j]);
              sum[i] += a[j];
              if (a[j] > 1) flag = false;
          }
          if (flag)
            tag[i] = true;
      }
}

inline ll ask(int l,int r){
    int lp = id[l],rp = id[r];
    ll res = 0;
    if (lp == rp){
        for (int i = l;i <= r;i ++)
          res += a[i];
        return res;
    }
    if (!tag[lp])
      for (int i = l;i <= sub[lp][1];i ++)
        res += a[i];
    else 
      res += (sub[lp][1] - l + 1);
    if (!tag[rp])
      for (int i = sub[rp][0];i <= r;i ++)
        res += a[i];
    else 
      res += (r - sub[rp][0] + 1);
    for (int i = lp + 1;i <= rp - 1;i ++)
      res += sum[i];
    return res;
}

inline void print(){
    for (int i = 1;i <= n;i ++)
      printf("%lld ",a[i]);
    printf("\n");
}

int main(){
//    freopen("P4145_2.in","r",stdin);
//    freopen("out.txt","w",stdout);
    
    scanf("%d",&n);
    
    len = sqrt(n);
    for (int i = 1;i <= n;i ++){
        scanf("%lld",&a[i]);
        id[i] = (i - 1) / len + 1;
        sum[id[i]] += a[i];
    }
    for (int i = 1;i <= id[n];i ++){
        sub[i][0] = (i - 1) * len + 1;
        sub[i][1] = i * len;
    }
    sub[id[n]][1] = min(sub[id[n]][1],n);
    
//    print();
    scanf("%d",&m);
    while (m --){
        int k,l,r;
        scanf("%d%d%d",&k,&l,&r);
        if (l > r) swap(l,r);
        if (!k) change(l,r);
        else printf("%lld\n",ask(l,r));
//        print();
    }
    return 0;
}
