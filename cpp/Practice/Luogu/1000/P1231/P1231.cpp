#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    ll val;
    int nxt;
};
Edge e[N << 1];

int n,p,q,cnt = 2,head[N],s,t,m1,m2;
int qx[N],frt,tal,d[N],now[N];
ll maxflow;

inline void add(const int &u,const int &v,const int &w){
    e[cnt].u = u,e[cnt].v = v,e[cnt].val = w;
    e[cnt].nxt = head[u],head[u] = cnt ++;

    e[cnt].u = v,e[cnt].v = u,e[cnt].val = 0;
    e[cnt].nxt = head[v],head[v] = cnt ++;
}

inline bool bfs(){
    mset(d,0);frt = 0,tal = -1;
    qx[++ tal] = s;d[s] = 1;now[s] = head[s];
    while (frt <= tal){
        int x = qx[frt ++];
        for (int i = head[x];i;i = e[i].nxt)
          if (e[i].val && !d[e[i].v]){
              qx[++ tal] = e[i].v;
              now[e[i].v] = head[e[i].v];
              d[e[i].v] = d[x] + 1;
              if (e[i].v == t) return true;
          }
    }
    return false;
}

inline ll dinic(int x,ll flow){
    if (x == t) return flow;
    ll rest = flow,k,i;
    for (i = now[x];i && rest;i = e[i].nxt){
        if (e[i].val && d[e[i].v] == d[x] + 1){
            k = dinic(e[i].v,min(rest,e[i].val));
            if (!k) d[e[i].v] = 0;
            e[i].val -= k;
            e[i ^ 1].val += k;
            rest -= k;
        }
        now[x] = i;
    }
    return flow - rest;
}

int main(){
    scanf("%d%d%d",&n,&p,&q);
    for (int i = 1;i <= n;i ++)
      add(p + i,n + p + q + i,1);
    scanf("%d",&m1);
    for (int i = 1;i <= m1;i ++){
        int x,y;scanf("%d%d",&x,&y);
        add(y,p + x,1);
    }
    scanf("%d",&m2);
    for (int i = 1;i <= m1;i ++){
        int x,y;scanf("%d%d",&x,&y);
        add(n + p + q + x,n + p + y,1);
    }
    s = 0,t = 2 * n + p + q + 1;
    for (int i = 1;i <= p;i ++) add(s,i,1);
    for (int i = 1;i <= q;i ++) add(n + p + i,t,1);
    ll flow = 0;
    while (bfs()) while (flow = dinic(s,INF))
      maxflow += flow;
    printf("%lld",maxflow);
    return 0;
}