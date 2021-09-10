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
Edge e[N << 1];

int n,m,r,cnt,head[N];
int v[N],match[N],ans;

inline void add(int u,int v){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline bool dfs(int x){
    for (int i = head[x];i != -1;i = e[i].nxt)
      if (!v[e[i].v]){
          v[e[i].v] = 1;
          if (!match[e[i].v] || dfs(match[e[i].v])){
              match[e[i].v] = x;
              return true;
          }
      }
    return false;
}

int main(){
    mset(head,-1);
    scanf("%d%d%d",&n,&m,&r);
    for (int i = 1;i <= r;i ++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v + n);add(v + n,u);
    }
    for (int i = 1;i <= n;i ++){
        mset(v,0);
        if (dfs(i)) ans ++;
    }
    printf("%d",ans);
    return 0;
}
