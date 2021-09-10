#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 1010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N << 1];

int m,n,v[N],match[N];
int cnt,head[N],ans;

inline void add(const int &u,const int &v){
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
              match[x] = e[i].v;
              return true;
          }
      }
    return false;
}

int main(){
    mset(head,-1);
    scanf("%d%d",&m,&n);
    int a = 0,b = 0;
    scanf("%d%d",&a,&b);
    while (a != -1 && b != -1){
        add(a,b);
        scanf("%d%d",&a,&b);
    }
    for (int i = 1;i <= m;i ++){
        mset(v,0);
        if (dfs(i)) ans ++;
    }
    printf("%d\n",ans);
    for (int i = 1;i <= m;i ++)
      if (match[i])
        printf("%d %d\n",i,match[i]);
    return 0;
}
