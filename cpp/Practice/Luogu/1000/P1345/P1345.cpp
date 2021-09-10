#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    ll w;
    int nxt;
};
Edge e[N << 2];

int n,m,s,t,cnt = 2,head[N];
int q[N << 2],frt,tal,d[N],now[N];
ll maxflow;

inline void add(const int &u,const int &v,const ll &w){
    e[cnt].u = u;e[cnt].v = v;e[cnt].w = w;
    e[cnt].nxt = head[u];head[u] = cnt ++;

    e[cnt].u = v;e[cnt].v = u;e[cnt].w = 0;
    e[cnt].nxt = head[v];head[v] = cnt ++;
}

inline bool bfs(){
    mset(d,0);
    frt = 0,tal = -1;
    q[++ tal] = s;d[s] = 1,now[s] = head[s];
    while (frt <= tal){
        int x = q[frt ++];
        for (int i = now[x];i;i = e[i].nxt){
            if (e[i].w && !d[e[i].v]){
              q[++ tal] = e[i].v;
              now[e[i].v] = head[e[i].v];
              d[e[i].v] = d[x] + 1;
              if (e[i].v == t) return true;
          }
        }
          
    }
    return false;
}

inline ll dinic(int x,ll flow){
    if (x == t) return flow;
    ll rest = flow,k,i;
    for (i = now[x];i && rest;i = e[i].nxt){
        if (e[i].w && d[e[i].v] == d[x] + 1){
            k = dinic(e[i].v,rest < e[i].w ? rest : e[i].w);
            if (!k) d[e[i].v] = 0;
            e[i].w -= k,e[i ^ 1].w += k,rest -= k;
        }
        now[x] = i;
    }
    return flow - rest;
}

int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i = 1;i <= n;i ++)
      if (i != s && i != t) add(i,i + n,1);
    for (int i = 1;i <= m;i ++){
        int x,y;scanf("%d%d",&x,&y);
        add((x == s || x == t) ? x : x + n,y,INF);
        add((y == s || y == t) ? y : y + n,x,INF);
    }
    ll flow = 0;
    while (bfs()) while (flow = dinic(s,INF))
      maxflow += flow;
    printf("%lld",maxflow);
    return 0;
}