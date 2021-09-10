/*O(nlogn)*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int MAX = 5000;
const int INF = 0x3fffffff;

struct Node{
    int l,r;
    int ls,rs;
    int sum;
};
Node p[N];

int cnt,n,T,root,a[N],mx,ans;

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

inline int create(const int &l,const int &r){
    p[++ cnt].l = l,p[cnt].r = r;
    p[cnt].ls = p[cnt].rs = p[cnt].sum = 0;
    return cnt;
}

inline void insert(int k,int x){
    p[k].sum ++;
    if (p[k].l == p[k].r)
      return;
    int mid = (p[k].l + p[k].r) >> 1;
    if (x <= mid){
        if (!p[k].ls) p[k].ls = create(p[k].l,mid);
        insert(p[k].ls,x);
    }
    else{
        if (!p[k].rs) p[k].rs = create(mid + 1,p[k].r);
        insert(p[k].rs,x);
    }
}

inline int query(int k,int x,int y){
    if (x <= p[k].l && p[k].r <= y)
      return p[k].sum;
    int mid = (p[k].l + p[k].r) >> 1,res = 0;
    if (x <= mid) if (p[k].ls)
      res += query(p[k].ls,x,y);
    if (y > mid) if (p[k].rs)
      res += query(p[k].rs,x,y);
    return res;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++){
        scanf("%d",&a[i]);
        mx = Max(mx,a[i]);
    }
    scanf("%d",&T);
    root = create(1,mx + T + 10);
    for (int i = 1;i <= n;i ++)
      insert(root,a[i]);
    for (int i = 1;i <= n;i ++)
      ans = Max(ans,query(root,a[i],a[i] + T));
    printf("%d",ans);
    return 0;
}
