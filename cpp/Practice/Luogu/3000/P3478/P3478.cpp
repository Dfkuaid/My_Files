#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define int long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N << 1];

int n,cnt,head[N],size[N],fa[N],h[N],f[N],rt,g[N],ans[2];

inline void add(int u,int v){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline void dfs1(int k,int p){
    size[k] = 1;fa[k] = p;h[k] = h[p] + 1;
    for (int i = head[k];i != -1;i = e[i].nxt){
        if (e[i].v == p) continue;
        dfs1(e[i].v,k);
        size[k] += size[e[i].v];
        f[k] += size[e[i].v] + f[e[i].v];
    }
}

inline void dfs2(int k){
    for (int i = head[k];i != -1;i = e[i].nxt){
        if (e[i].v == fa[k]) continue;
        g[e[i].v] = g[k] + n - 2 * size[e[i].v];
        dfs2(e[i].v);
    }
    if (ans[0] < g[k]) ans[0] = g[k],ans[1] = k;
}

signed main(){
    mset(head,-1);
    scanf("%lld",&n);
    for (int i = 1;i < n;i ++){
        int u,v;
        scanf("%lld%lld",&u,&v);
        add(u,v);add(v,u);
    }
    dfs1(rt = 1,1);
    
    g[rt] = f[rt];
    dfs2(rt);
    printf("%lld",ans[1]);
    return 0;
}
