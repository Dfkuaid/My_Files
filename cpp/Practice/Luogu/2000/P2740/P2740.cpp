#include <iostream>
#include <queue>
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
    int nxt;
    ll val;
};
Edge e[N << 1];

int n,m,s,t;
ll maxflow;
int cnt,head[N],d[N],now[N];
queue <int> q;

inline void add(const int &u,const int &v,const ll &w){
    e[cnt].u = u;e[cnt].v = v;e[cnt].val = w;
    e[cnt].nxt = head[u];head[u] = cnt ++;

    e[cnt].u = v;e[cnt].v = u;e[cnt].val = 0;
    e[cnt].nxt = head[v];head[v] = cnt ++;
}

inline bool bfs(){
    mset(d,0);
    while (q.size()) q.pop();
    q.push(s);d[s] = 1;now[s] = head[s];
    while (q.size()){
        int x = q.front();q.pop();
        for (int i = head[x];i != -1;i = e[i].nxt)
          if (e[i].val && !d[e[i].v]){
              q.push(e[i].v);
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
    for (i = now[x];(i != -1) && rest;i = e[i].nxt){
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
    mset(head,-1);
    scanf("%d%d",&m,&n);
    s = 1;t = n;
    for (int i = 1;i <= m;i ++){
        int u,v;ll w;
        scanf("%d%d%lld",&u,&v,&w);
        add(u,v,w);
    }
    ll flow = 0;
    while (bfs())
      while (flow = dinic(s,INF))
        maxflow += flow;
    printf("%lld",maxflow);
    return 0;
}