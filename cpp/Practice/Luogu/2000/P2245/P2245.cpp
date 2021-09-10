#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 10010;
const int M = 50010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int w,nxt;
};
Edge e[M << 2],es[M];

int tot,n,m,head[N],fa[N],vis[N],rt[N];
int f[N][50],t,d[N],g[N][50],qe;

queue <int> q;

inline int cmp(const Edge a,const Edge b){
    return a.w < b.w;
}

inline void add(int u,int v,int w){
    e[++ tot].u = u;
    e[tot].v = v;
    e[tot].w = w;
    e[tot].nxt = head[u];
    head[u] = tot;
}

inline int getf(int x){
    while (x != fa[x])
      x = fa[x] = fa[fa[x]];
    return x;
}

inline void maxest(){
    for (int i = 1;i <= n;i ++)
      fa[i] = i;
    sort(es + 1,es + m + 1,cmp);
    for (int i = 1;i <= m;i ++){
        int fx = getf(es[i].u);
        int fy = getf(es[i].v);
        if (fx == fy) continue;
        add(es[i].u,es[i].v,es[i].w);
        add(es[i].v,es[i].u,es[i].w);
        fa[fx] = fy;
    }
}

inline void prework(){
    tot = 0;mset(g,0);
    for (int i = 1;i <= n;i ++){
        if (vis[i]) continue;
        rt[++ tot] = i;vis[i] = true;
        q.push(i);
        while (q.size()){
            int now = q.front();q.pop();
            for (int j = head[now];j;j = e[j].nxt){
                int y = e[j].v;
                if (vis[y]) continue;
                f[y][0] = now;d[y] = d[now] + 1;
                g[y][0] = e[j].w;vis[y] = true;
                for (int k = 1;k <= t;k ++){
                    f[y][k] = f[f[y][k - 1]][k - 1];
                    g[y][k] = max(g[y][k - 1],g[f[y][k - 1]][k - 1]);
                }
                q.push(y);
            }
        }
    }
}

inline int ExLCA(int x,int y){
    int res = 0;
    if (d[x] < d[y]) swap(x,y);
    for (int i = t;i >= 0;i --)
      if (d[f[x][i]] >= d[y]){
          res = max(res,g[x][i]);
          x = f[x][i];
      }
    if (x == y) return res;
    for (int i = t;i >= 0;i --)
      if (f[x][i] != f[y][i]){
          res = max(res,g[y][i]);
          y = f[y][i];
          res = max(res,g[x][i]);
          x = f[x][i];
      }
    res = max(res,g[x][0]);
    res = max(res,g[y][0]);
    return res;
}

int main(){
    scanf("%d%d",&n,&m);
    t = (int)(log(n) / log(2)) + 1;
    for (int i = 1;i <= m;i ++)
      scanf("%d%d%d",&es[i].u,&es[i].v,&es[i].w);
    maxest();prework();
    scanf("%d",&qe);
    while (qe --){
        int x,y;
        scanf("%d%d",&x,&y);
        if (getf(x) != getf(y)){puts("-1");continue;}
        printf("%d\n",ExLCA(x,y));
    }
    return 0;
}