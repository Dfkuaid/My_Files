#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N],ne[N];

int cnt = 1,ncnt = 1,head[N],nhead[N],T;
int fa[N],d[N],son[N],size[N],dfn[N],top[N];
int tag[N],n,q,k,st[N],stp,a[N];

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
        dfs1(e[i].v,x);
        size[x] += size[e[i].v];
        if (size[e[i].v] > size[son[x]])
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
    return d[a] > d[b] ? b : a;
}

inline void insert(int x){
    if (!stp){st[++ stp] = x;return;}
    int ance = LCA(x,st[stp]);
    while (stp > 1 && d[st[stp - 1]] > d[ance])
      add(st[stp - 1],st[stp]),stp --;
    if (d[ance] < d[st[stp]])
      add(ance,st[stp]),stp --;
    if (!stp || ance != st[stp])
      st[++ stp] = ance;
    st[++ stp] = x;
}

int DP(int x){
    if (!nhead[x]) return 0;
    int scnt = 0,res = 0;
    for (int i = nhead[x];i;i = ne[i].nxt){
        res += DP(ne[i].v);
        if (tag[ne[i].v]) scnt ++;
        tag[ne[i].v] = false;
    }
    if (scnt == 1 && !tag[x]) tag[x] = true;
    else if (scnt == 1 && tag[x]) res ++;
    else if (scnt > 1) if (tag[x]) res += scnt;
    else res ++; 
    nhead[x] = 0;if (x == 1) tag[x] = false;
    return res;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i < n;i ++){
        int u,v;scanf("%d%d",&u,&v);
        ADD(u,v);ADD(v,u);
    }
    dfs1(1,0);dfs2(1,1);
    scanf("%d",&q);
    while (q --){
        scanf("%d",&k);
        int ck = 0;stp = 0;
        for (int i = 1;i <= k;i ++){
            scanf("%d",&a[i]);
            tag[a[i]] = true;
        }
        for (int i = 1;i <= k;i ++)
          if (tag[fa[a[i]]]){ck = 1;break;}
        if (ck){
            printf("-1\n");
            for (int i = 1;i <= k;i ++)
              tag[a[i]] = false;
            continue;
        }
        sort(a + 1,a + k + 1,cmp);
        if (a[1] != 1) insert(1);
        for (int i = 1;i <= k;i ++) insert(a[i]);
        while (stp) add(st[stp - 1],st[stp]),stp --;
        printf("%d\n",DP(1));
    }
    return 0;
}
