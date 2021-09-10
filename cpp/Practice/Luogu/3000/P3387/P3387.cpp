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
};
Edge e[N],ne[N];

int n,m,cnt = 1,ncnt = 1,head[N],T,cnt2,belong[N];
int dfn[N],low[N],st[N],inst[N],frt,fl[N],ans;
int icnt[N],ocnt[N],data[N],nhead[N],f[N];

queue <int> q;

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
    icnt[v] ++;ocnt[u] ++;
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
        int y;
        do{
            y = st[frt --];
            inst[y] = false;
            belong[y] = x;
            if (x != y) data[x] += data[y];
        } while (y != x);
        fl[x] = true;
    }
}

inline void tobo(){
    for (int i = 1;i <= n;i ++)
      if (!icnt[i] && fl[i]){
          q.push(i);
          f[i] = data[i];
      }
    while (q.size()){
        int now = q.front();q.pop();
        for (int i = nhead[now];i;i = ne[i].nxt){
            icnt[ne[i].v] --;
            f[ne[i].v] = Max(f[ne[i].v],data[ne[i].v] + f[now]);
            if (!icnt[ne[i].v])
              q.push(ne[i].v);
        }
    }
    for (int i = 1;i <= n;i ++)
      ans = Max(ans,f[i]);
}

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&data[i]);
    for (int i = 1;i <= m;i ++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    for (int i = 1;i <= n;i ++)
      if (!dfn[i]) tarjan(i);
    for (int i = 1;i <= m;i ++)
      if (belong[e[i].u] != belong[e[i].v])
        addn(belong[e[i].u],belong[e[i].v]);
    tobo();
    printf("%d",ans);
    return 0;
}
