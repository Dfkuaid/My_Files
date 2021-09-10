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
    int nxt;
};
Edge e[N],ne[N];

int n,ans1,ans2;
int cnt = 1,ncnt = 1,head[N],nhead[N],icnt[N],ocnt[N];
int T,dfn[N],low[N],scc[N],scnt,st[N],inst[N],frt;

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
    ocnt[u] ++;icnt[v] ++;
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
            scc[y] = scnt;
            inst[y] = false;
        }while (x != y);
    }
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++){
        int x;
        scanf("%d",&x);
        while (x){
            add(i,x);
            scanf("%d",&x);
        }
    }
    for (int i = 1;i <= n;i ++)
      if (!dfn[i]) tarjan(i);
    for (int i = 1;i < cnt;i ++)
      if (scc[e[i].u] != scc[e[i].v])
        addn(scc[e[i].u],scc[e[i].v]);
    for (int i = 1;i <= scnt;i ++){
        if (!icnt[i]) ans1 ++;
        if (!ocnt[i]) ans2 ++;
    }
    if (scnt == 1){printf("1\n0");return 0;} 
    printf("%d\n%d",ans1,Max(ans1,ans2));
    return 0;
}