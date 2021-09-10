#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 5000010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N];

int n,m,cnt = 1,head[N],scc[N],frt;
int dfn[N],low[N],T,st[N],inst[N],cnt2;

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
      else if (inst[e[i].v])
        low[x] = Min(low[x],dfn[e[i].v]);
    if (dfn[x] == low[x]){
        int y;cnt2 ++;
        do{
            y = st[frt --];
            scc[y] = cnt2;
            inst[y] = false;
        }while (x != y);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= m;i ++){
        int a,b,x,y;
        scanf("%d%d%d%d",&a,&x,&b,&y);
        add(a + (x ^ 1) * n,b + y * n);
        add(b + (y ^ 1) * n,a + x * n);
    }
    for (int i = 1;i <= 2 * n;i ++)
      if (!dfn[i]) tarjan(i);
    for (int i = 1;i <= n;i ++)
      if (scc[i] == scc[i + n]){
          printf("IMPOSSIBLE");
          return 0;
      }
    printf("POSSIBLE\n");
    for (int i = 1;i <= n;i ++)
      printf("%d ",scc[i] > scc[i + n]);
    return 0;
}
