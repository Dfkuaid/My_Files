/*SPOJ GSS1 https://www.spoj.com/problems/GSS1/ */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 1000100;
const int INF = 0x3fffffff;

int loc[N],a[N],n,m,len = 2;
int s[25][N],p[25][N],lg[N];

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

inline void build(int k,int l,int r,int d){
    if (l == r) {loc[l] = k;return;}
    int mid = (l + r) >> 1;
    int pre,sm;
    s[d][mid] = a[mid],p[d][mid] = a[mid];
    pre = sm = a[mid];sm = sm > 0 ? sm : 0;
    for (int i = mid - 1;i >= l;i --){
        pre += a[i],sm += a[i];
        s[d][i] = Max(s[d][i + 1],pre),
        p[d][i] = Max(p[d][i + 1],sm);
        sm = sm > 0 ? sm : 0;
    }
    s[d][mid + 1] = a[mid + 1],
    p[d][mid + 1] = a[mid + 1];
    pre = sm = a[mid + 1];  sm = sm > 0 ? sm : 0;
    for (int i = mid + 2;i <= r;i ++){
        pre += a[i],sm += a[i];
        s[d][i] = Max(s[d][i - 1],pre);
        p[d][i] = Max(p[d][i - 1],sm);
        sm = sm > 0 ? sm : 0;
    }
    build(k << 1,l,mid,d + 1);
    build(k << 1 | 1,mid + 1,r,d + 1);
}

inline int query(int l,int r){
    if (l == r) return a[l];
    int d = lg[loc[l]] - lg[loc[l] ^ loc[r]];
    return Max(Max(p[d][l],p[d][r]),s[d][l] + s[d][r]);
}

int main(){
    scanf("%d",&n);
    while (len < n) len <<= 1;
    for (int i = 1;i <= n;i ++)
      scanf("%d",&a[i]);
    for (int i = 2;i <= len << 1;i ++)
      lg[i] = lg[i >> 1] + 1;
    build(1,1,len,1);
    scanf("%d",&m);
    while (m --){
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",query(l,r));
    }
    return 0;
}
