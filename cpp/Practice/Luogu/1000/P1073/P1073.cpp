#include <iostream>
#include <map>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
#define mp(a,b) make_pair(a,b)
using namespace std;

const int N = 100010;
const int M = 500010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[M],ne[M];

int cnt = 1,head[N],ncnt = 1,nhead[N],cnt2,in1[N];
int dfn[N],low[N],st[N],inst[N],scc[N],q[M],val[N];
int mn[N],mx[N],maxx[N],minn[N],n,m,T,frt,tal,scnt,icnt[N];

map <pair<int,int>,bool> p;

inline int Min(const int &a,const int &b){
    return a < b ? a : b;
}

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

inline void add(const int &u,const int &v){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline void addn(const int &u,const int &v){
    ne[ncnt].u = u;
    ne[ncnt].v = v;
    ne[ncnt].nxt = nhead[u];
    nhead[u] = ncnt ++;
    icnt[v] ++;
}

inline void tarjan(int x){
    dfn[x] = low[x] = ++ T;
    st[++ frt] = x;inst[x] = true;
    for (int i = head[x];i;i = e[i].nxt)
      if (!dfn[e[i].v]){
          tarjan(e[i].v);
          low[x] = Min(low[x],low[e[i].v]);
      }
      else if (inst[e[i].v])
        low[x] = Min(low[x],dfn[e[i].v]);
    if (dfn[x] == low[x]){
        int y;scnt ++;
        do{
            y = st[frt --];
            inst[y] = false;
            scc[y] = scnt;
            mn[scnt] = Min(mn[scnt],val[y]);
            mx[scnt] = Max(mx[scnt],val[y]);
        }while (x != y);
    }
}

inline void tobo(){
    frt = 0;tal = -1;
    for (int i = 1;i <= scnt;i ++)
      if (!icnt[i]) q[++ tal] = i;
    q[++ tal] = scc[1];
    in1[scc[1]] = 1;
    for (int i = 1;i <= scnt;i ++){
        maxx[i] = mx[i] - mn[i];
        minn[i] = mn[i];
    }
    while (frt <= tal){
        int now = q[frt ++];
        for (int i = nhead[now];i;i = ne[i].nxt){
            if (in1[now]){
                minn[ne[i].v] = Min(minn[ne[i].v],minn[now]);
                maxx[ne[i].v] = Max(max(maxx[now],maxx[ne[i].v]),mx[ne[i].v] - minn[ne[i].v]);
            }
            in1[ne[i].v] |= in1[now];
            icnt[ne[i].v] --;
            if (!icnt[ne[i].v] && in1[ne[i].v]){
                q[++ tal] = ne[i].v;
            }
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&val[i]);
    for (int i = 1;i <= m;i ++){
        int opt,u,v;
        scanf("%d%d%d",&u,&v,&opt);
        if (opt == 2){
            add(u,v);add(v,u);
        }
        else add(u,v);
    }
    mset(mn,0x3f);
    for (int i = 1;i <= n;i ++)
      if (!dfn[i]) tarjan(i);
    for (int i = 1;i < cnt;i ++)
      if (scc[e[i].v] != scc[e[i].u] && !p[mp(scc[e[i].u],scc[e[i].v])]){
          addn(scc[e[i].u],scc[e[i].v]);cnt2 ++;
          p[mp(scc[e[i].u],scc[e[i].v])] = true;
      }
    tobo();
    if (maxx[scc[n]] > 0)
      printf("%d",maxx[scc[n]]);
    else printf("0");
    return 0;
}