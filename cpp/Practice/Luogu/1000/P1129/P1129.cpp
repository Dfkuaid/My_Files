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

int cnt,head[N],match[N],v[N],n,T,ans;

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
              return true;
          }
      }
    return false;
}

inline void sweap(){
    mset(match,0);
    mset(head,-1);
    cnt = 0,ans = 0;
}

int main(){
    scanf("%d",&T);
    while (T --){
        sweap();
        scanf("%d",&n);
        for (int i = 1;i <= n;i ++)
          for (int j = 1;j <= n;j ++){
              int x;
              scanf("%d",&x);
              if (x) add(i,j + n);
          }
        for (int i = 1;i <= n;i ++){
            mset(v,0);
            if (dfs(i)) ans ++;
        }
        if (ans >= n) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}