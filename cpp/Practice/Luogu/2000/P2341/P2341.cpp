#include <iostream>
#include <map>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mp(a,b) make_pair(a,b)
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N],ne[N];

int n,m,head[N],cnt = 1,scnt,scc[N];
int dfn[N],low[N],st[N],inst[N],frt;
int icnt[N],ocnt[N],scc_cnt[N],had,T;

inline int Min(const int &a,const int &b){
    return a < b ? a : b;
}

inline void add(const int &u,const int &v){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline void tarjan(int x){
    dfn[x] = low[x] = ++ T;
    st[++ frt] = x;inst[x] = true;
    for (int i = head[x];i;i = e[i].nxt)
      if (!dfn[e[i].v]){
          tarjan(e[i].v);
          low[x] = Min(low[x],low[e[i].v]);
      }
      else if (inst[x])
        low[x] = Min(low[x],dfn[e[i].v]);
    if (dfn[x] == low[x]){
        int y;scnt ++;
        do{
            y = st[frt --];
            scc[y] = scnt;
            inst[y] = false;
            ++ scc_cnt[scnt];
        }while (y != x);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= m;i ++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    for (int i = 1;i <= n;i ++)
      if (!dfn[i]) tarjan(i);
    for (int i = 1;i < cnt;i ++)
      if (scc[e[i].u] != scc[e[i].v]){
          ++ icnt[scc[e[i].v]];
          ++ ocnt[scc[e[i].u]];
      }
    for (int i = 1;i <= scnt;i ++)
      if (!ocnt[i])
        if (!had) had = i;
        else {
            printf("0");
            return 0;
        }
    printf("%d",scc_cnt[had]);
    return 0;
}
