#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define int long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 2e6;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N],ne[N];

int n,q,k,cnt = 1,ncnt = 1,head[N],nhead[N];
int fa[N],d[N],son[N],size[N],slch[N],ssch[N];
int top[N],dfn[N],T,st[N],stp,lch[N],sch[N],nson[N];
int tot[N],sum_d[N],mn[N],mx[N],sum[N],a[N],tag[N];

template <typename T>
inline T Max(T a,T b){
    return a > b ? a : b;
}

template <typename T>
inline T Min(T a,T b){
    return a < b ? a : b;
}

inline int cmp(const int &a,const int &b){
    return dfn[a] < dfn[b];
}

inline void ADD(const int &u,const int &v){
    e[cnt].u = u,e[cnt].v = v;
    e[cnt].nxt = head[u];head[u] = cnt ++;
}

inline void add(const int &u,const int &v){
    ne[ncnt].u = u,ne[ncnt].v = v;
    ne[ncnt].nxt = nhead[u];nhead[u] = ncnt ++;
}

void dfs1(int x,int _fa){
    fa[x] = _fa,d[x] = d[_fa] + 1,size[x] = 1;
    for (int i = head[x];i;i = e[i].nxt){
        if (e[i].v == fa[x]) continue;
        dfs1(e[i].v,x);size[x] += size[e[i].v];
        if (size[son[x]] < size[e[i].v])
          son[x] = e[i].v;
    }
}

void dfs2(int x,int t){
    dfn[x] = ++ T,top[x] = t;
    if (!son[x]) return;
    dfs2(son[x],t);
    for (int i = head[x];i;i = e[i].nxt)
      if (e[i].v != fa[x] && e[i].v != son[x])
        dfs2(e[i].v,e[i].v);
}

inline int LCA(int a,int b){
    while (top[a] != top[b]){
        if (d[top[a]] < d[top[b]])
          swap(a,b);
        a = fa[top[a]];
    }
    return d[a] < d[b] ? a : b;
}

inline void insert(int x){
    nson[x] = 0;
    if (!stp){st[++ stp] = x;return;}
    int ance = LCA(st[stp],x);nson[ance] = 0;
    while (stp > 1 && d[st[stp - 1]] > d[ance])
      add(st[stp - 1],st[stp]),stp --;
    if (d[ance] < d[st[stp]])
      add(ance,st[stp]),stp --;
    if (!stp || st[stp] != ance)
      st[++ stp] = ance;
    st[++ stp] = x;
}

void solve(int x){
    mn[x] = INF;mx[x] = 0;tot[x] = sum[x] = sum_d[x] = 0;
    lch[x] = slch[x] = 0;sch[x] = ssch[x] = INF;
    for (int i = nhead[x];i;i = ne[i].nxt){
        solve(ne[i].v);nson[x] ++;

        if (lch[ne[i].v] > lch[x]){
            slch[x] = lch[x];
            lch[x] = lch[ne[i].v];
        }else slch[x] = Max(slch[x],lch[ne[i].v]);
        if (nson[x] > 1) mx[x] = Max(Max(mx[x],mx[ne[i].v]),
                                lch[x] + slch[x] - 2 * d[x]);
        else mx[x] = mx[ne[i].v];
        
        if (sch[ne[i].v] < sch[x]){
            ssch[x] = Min(sch[x],ssch[ne[i].v]);
            sch[x] = sch[ne[i].v];
        }else ssch[x] = Min(ssch[x],sch[ne[i].v]);
        if (nson[x] > 1) mn[x] = Min(Min(mn[x],mn[ne[i].v]),
                                sch[x] + ssch[x] - 2 * d[x]);
        else mn[x] = mn[ne[i].v];
        
        sum[x] += tot[x] * sum_d[ne[i].v] + tot[ne[i].v] * sum_d[x]
                  - 2 * tot[x] * tot[ne[i].v] * d[x];
        sum[x] += sum[ne[i].v];
        tot[x] += tot[ne[i].v];sum_d[x] += sum_d[ne[i].v];
    }
    if (tag[x]){
        ssch[x] = sch[x];sch[x] = d[x];
        mn[x] = Min(mn[x],ssch[x] - sch[x]);

        if (!nhead[x]) lch[x] = d[x];
        else if (!slch[x]) slch[x] = d[x];
        mx[x] = Max(mx[x],lch[x] - sch[x]);
        
        sum[x] += sum_d[x] - d[x] * tot[x];
        sum_d[x] += d[x];tot[x] ++;
    }
    nhead[x] = 0;tag[x] = false;
}

signed main(){
    scanf("%lld",&n);
    for (int i = 1;i < n;i ++){
        int u,v;scanf("%lld%lld",&u,&v);
        ADD(u,v);ADD(v,u);
    }
    dfs1(1,0);dfs2(1,1);
    scanf("%lld",&q);
    while (q --){
        scanf("%lld",&k);stp = 0;
        for (int i = 1;i <= k;i ++){
            scanf("%lld",&a[i]);
            tag[a[i]] = true;
        }
        sort(a + 1,a + k + 1,cmp);
        if (a[1] != 1) insert(1);
        for (int i = 1;i <= k;i ++) insert(a[i]);
        while (stp) add(st[stp - 1],st[stp]),stp --;
        solve(1);
        printf("%lld %lld %lld\n",sum[1],mn[1],mx[1]);
    }
    return 0;
}