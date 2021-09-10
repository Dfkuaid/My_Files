#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 2000010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    ll w;
    int nxt;
};
Edge e[N],ne[N];

int cnt = 1,head[N],n,m,ncnt = 1,nhead[N];
int son[N],dfn[N],T,st[N],stp,f[N];
int fa[N],size[N],d[N],top[N],fl[N];
ll mn[N];

inline ll Min(const ll &a,const ll &b){
    return a < b ? a : b;
}

inline void ADD(const int &u,const int &v,const ll &w){
    e[cnt].u = u;e[cnt].v = v;e[cnt].w = w;
    e[cnt].nxt = head[u];head[u] = cnt ++;
}

inline void add(const int &u,const int &v){
    ne[ncnt].u = u;ne[ncnt].v = v;
    ne[ncnt].nxt = nhead[u];nhead[u] = ncnt ++;
}

inline int cmp(const int &a,const int &b){
    return dfn[a] < dfn[b];
}

inline void dfs1(int x,int _fa){
    size[x] = 1,d[x] = d[_fa] + 1,fa[x] = _fa;
    for (int i = head[x];i;i = e[i].nxt){
        if (e[i].v == fa[x]) continue;
        mn[e[i].v] = Min(mn[x],e[i].w);
        dfs1(e[i].v,x);
        size[x] += size[e[i].v];
        if (size[e[i].v] > size[son[x]])
          son[x] = e[i].v;
    }
}

inline void dfs2(int x,int t){
    top[x] = t;dfn[x] = ++ T;
    if (!son[x]) return;
    dfs2(son[x],t);
    for (int i = head[x];i;i = e[i].nxt){
        if (e[i].v == fa[x] || e[i].v == son[x])
          continue;
        dfs2(e[i].v,e[i].v);
    }
}

inline int LCA(int a,int b){
    while (top[a] != top[b]){
        if(d[top[a]] < d[top[b]])
          swap(a,b);
        a = fa[top[a]];
    }
    if (d[a] < d[b]) swap(a,b);
    return b;
}

inline void ins(int x){
    if (stp == 1) {st[++ stp] = x;return;}
    int ance = LCA(x,st[stp]);
    if (ance == st[stp]) return;
    while (stp > 1 && d[ance] < d[st[stp - 1]])
      add(st[stp - 1],st[stp]),stp --;
    if (d[ance] < d[st[stp]]) add(ance,st[stp --]);
    if (!stp || st[stp] != ance) st[++ stp] = ance;
    st[++ stp] = x;
}

inline ll DP(int x){
    if (!nhead[x]) return mn[x];
    ll res = 0;
    for (int i = nhead[x];i;i = ne[i].nxt)
      res += DP(ne[i].v);
    nhead[x] = 0;
    return Min(mn[x],res);
}

int main(){
    mset(mn,0x3f);scanf("%d",&n);
    for (int i = 1;i < n;i ++){
        int u,v;ll w;
        scanf("%d%d%lld",&u,&v,&w);
        ADD(u,v,w);ADD(v,u,w);
    }
    dfs1(1,0);dfs2(1,1);
    scanf("%d",&m);
    while (m --){
        int k,a[N];ncnt = 1;
        scanf("%d",&k);st[stp = 1] = 1;
        for (int i = 1;i <= k;i ++)
          scanf("%d",&a[i]);
        sort(a + 1,a + k + 1,cmp);
        for (int i = 1;i <= k;i ++) ins(a[i]);
        while (stp) add(st[stp - 1],st[stp]),stp --;
        printf("%lld\n",DP(1));
    }
    return 0;
}
