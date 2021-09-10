#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N << 1];

int head[N],cnt = 1,v[N],match[N],n,ans,MAX,T = 1;

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

inline void add(const int &u,const int &v){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline bool dfs(int x){
    for (int i = head[x];i;i = e[i].nxt)
      if (v[e[i].v] - T){
          v[e[i].v] = T;
          if (!match[e[i].v] || dfs(match[e[i].v])){
              match[e[i].v] = x;
              return true;
          }
      }
    return false;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++){
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,i);add(b,i);
        MAX = Max(MAX,Max(a,b));
    }
    for (int i = 1;i <= MAX;i ++,T ++){
        if (dfs(i)) ans ++;
        else break;
    }
    printf("%d",ans);
    return 0;
}
