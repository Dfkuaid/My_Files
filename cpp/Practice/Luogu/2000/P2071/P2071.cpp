#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 4010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N << 1];

int n,cnt,head[N],v[N],match[N][2],ans;

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
          if (!match[e[i].v][0] || dfs(match[e[i].v][0])){
              match[e[i].v][0] = x;
              return true;
          }
          if (!match[e[i].v][1] || dfs(match[e[i].v][1])){
              match[e[i].v][1] = x;
              return true;
          }
      }
    return false;
}

int main(){
    mset(head,-1);
    scanf("%d",&n);
    for (int i = 1;i <= 2 * n;i ++){
        int a,b;
        scanf("%d%d",&a,&b);
        add(i,a);add(i,b);
    }
    for (int i = 1;i <= 2 * n;i ++){
        mset(v,0);
        if (dfs(i)) ans ++;
    }
    printf("%d",ans);
    return 0;
}
