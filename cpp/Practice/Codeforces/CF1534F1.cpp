#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N << 2];

char mp[N];
int n,m,a[N],head[N],cnt = 1,ck[N];
int T,dfn[N],low[N],inst[N],st[N],frt;
int scc[N],scnt,icnt[N],ans;

inline int get_ind(const int &i,const int &j){
    return (i - 1) * m + j;
}

inline void add(const int &u,const int &v){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline void tarjan(int x){
    dfn[x] = low[x] = ++ T;
    inst[x] = true;st[++ frt] = x;
    for (int i = head[x];i;i = e[i].nxt)
      if (!dfn[e[i].v]){
          tarjan(e[i].v);
          low[x] = min(low[x],low[e[i].v]);
      }
      else if (inst[e[i].v])
        low[x] = min(low[x],dfn[e[i].v]);
    if (dfn[x] == low[x]){
        int y = 0;++ scnt;
        do{
            y = st[frt --];
            scc[y] = scnt;
            inst[y] = false;
        }while (y != x);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;i ++)
      for (int j = 1;j <= m;j ++)
        cin >> mp[get_ind(i,j)];
    for (int i = 1;i <= n;i ++)
      scanf("%d",&a[i]);
    for (int i = 1;i <= n;i ++)
      for (int j = 1;j <= m;j ++){
          if (mp[get_ind(i,j)] == '#'){
              ck[get_ind(i,j)] = true;
              if (i > 1 && mp[get_ind(i - 1,j)] == '#')
                add(get_ind(i,j),get_ind(i - 1,j));
              for (int k = i + 1;k <= n;k ++)
                if (mp[get_ind(k,j)] == '#'){
                    add(get_ind(i,j),get_ind(k,j));
                    break;
                }
              if (j > 1) for (int k = i;k <= n && (mp[get_ind(k,j)] != '#' || k ==  i);k ++)
                if (mp[get_ind(k,j - 1)] == '#'){
                    add(get_ind(i,j),get_ind(k,j - 1));
                    break;
                }
              if (j < m) for (int k = i;k <= n && (mp[get_ind(k,j)] != '#' || k ==  i);k ++)
                if (mp[get_ind(k,j + 1)] == '#'){
                    add(get_ind(i,j),get_ind(k,j + 1));
                    break;
                }
          }
      }
    for (int i = 1;i <= n * m;i ++)
      if (ck[i] && !dfn[i]) tarjan(i);
    for (int i = 1;i < cnt;i ++)
      if (scc[e[i].u] != scc[e[i].v])
        icnt[scc[e[i].v]] ++;
    for (int i = 1;i <= scnt;i ++)
      if (!icnt[i]) ans ++;
    printf("%d",ans);
    return 0;
}
