# #0.0 序

本月偏重树上问题和图论。

# #1.0 起

> $\mathfrak{2021.6.1}\sim\mathfrak{2021.6.10}$

## #1.1 [P1073 [NOIP2009 提高组] 最优贸易](https://www.luogu.com.cn/problem/P1073)

因为 **相同的城市可以经过多次**，且我们只关注城市之间的差价，所以如果几个城市如果处于同一个强连通分量（$\texttt{SCC}$）中，那么这几个城市可以看作同一座城，可以得到其中的最高价和最低价。

$\texttt{Tarjan}$ 缩点后得到的图是一张 $\texttt{DAG}$，考虑 $\texttt{DAG}$ 上的动态规划，设 $mn_x$ 表示节点 $x$ 的最小价格，$mx_x$ 表示节点 $x$ 的最大价格，$minn_x$ 表示可到达 $x$ 的城市中的最小价格，$maxx_x$ 表示可到达 $x$ 的城市中的最大差价。那么显然有

$$
minn_x=\min\{mn_x,\min\limits_{(y,x)\in E}\{mn_y\}\},\\
maxx_x=\max\{mx_x-minn_x,\max\limits_{(y,x)\in E}\{max_y\}\},
$$

用拓扑解决即可。注意到固定了起始点 $1$，但 $1$ 不一定是入度为 $0$ 的点，入度为 $0$ 的点如果不是 $1$ 便必然不会产生贡献，所以需要标记点 $x$ 是否可以从 $1$ 到达。

``` cpp
#define mset(l,x) memset(l,x,sizeof(l))
#define mp(a,b) make_pair(a,b)

const int N = 100010;
const int M = 500010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[M],ne[M];

int cnt = 1,head[N],ncnt = 1,nhead[N],vis[M << 1],cnt2,in1[N];
int dfn[N],low[N],st[N],inst[N],scc[N],q[1000010],val[N];
int mn[N],mx[N],maxx[N],minn[N],n,m,T,frt,tal,scnt,icnt[N];

map <pair<int,int>,bool> p;

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
    icnt[v] ++;
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
            inst[y] = false;
            scc[y] = scnt;
            mn[scnt] = Min(mn[scnt],val[y]);
            mx[scnt] = Max(mx[scnt],val[y]);
        }while (x != y);
    }
}

inline void tobo(){
    frt = 0;tal = -1;
    for (int i = 1;i <= scnt;i ++)
      if (!icnt[i]) q[++ tal] = i;
    q[++ tal] = scc[1];
    in1[scc[1]] = 1;
    for (int i = 1;i <= scnt;i ++){
        maxx[i] = mx[i] - mn[i];
        minn[i] = mn[i];
    }
    while (frt <= tal){
        int now = q[frt ++];
        for (int i = nhead[now];i;i = ne[i].nxt){
            if (in1[now]){
                minn[ne[i].v] = min(minn[ne[i].v],minn[now]);
                maxx[ne[i].v] = max(max(maxx[now],maxx[ne[i].v]),mx[ne[i].v] - minn[ne[i].v]);
            }
            in1[ne[i].v] |= in1[now];
            icnt[ne[i].v] --;
            if (!icnt[ne[i].v] && in1[ne[i].v]){
                q[++ tal] = ne[i].v;
            }
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&val[i]);
    for (int i = 1;i <= m;i ++){
        int opt,u,v;
        scanf("%d%d%d",&u,&v,&opt);
        if (opt == 2){
            add(u,v);add(v,u);
        }
        else add(u,v);
    }
    mset(mn,0x3f);
    for (int i = 1;i <= n;i ++)
      if (!dfn[i]) tarjan(i);
    for (int i = 1;i < cnt;i ++)
      if (scc[e[i].v] != scc[e[i].u] && !p[mp(scc[e[i].u],scc[e[i].v])]){
          addn(scc[e[i].u],scc[e[i].v]);cnt2 ++;
          p[mp(scc[e[i].u],scc[e[i].v])] = true;
      }
    tobo();
    if (maxx[scc[n]] > 0)
      printf("%d",maxx[scc[n]]);
    else printf("0");
    return 0;
}
```

## #1.2 [P5365 [SNOI2017]英雄联盟](https://www.luogu.com.cn/problem/P5365)

简单的多重背包。设 $f_x$ 表示花费为 $x$ 时的方法数，转移见代码。

``` cpp
const int N = 1000100;
const int INF = 0x3fffffff;

int n,m,f[N],k[N],w[N],sum,ans;

signed main(){
    f[0] = 1;
    scanf("%lld%lld",&n,&m);
    for (int i = 1;i <= n;i ++)
      scanf("%lld",&k[i]);
    for (int i = 1;i <= n;i ++)
      scanf("%lld",&w[i]),sum += k[i] * w[i];
    for (int i = 1;i <= n;i ++)
      for (int j = sum;j >= 0;j --)
        for (int o = 1;o <= k[i];o ++)
          if (j >= o * w[i])
            f[j] = max(f[j],f[j - o * w[i]] * o);
    while (f[ans] <= m && ans <= sum) ans ++;
    cout << ans;
    return 0;
}
```

## #1.3 [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)

~~u1s1，题面的描述真™的不够详细。~~

整体的思想偏向于模拟，先为每个右括号预存一个左括号，每个左括号预存一个右括号。用栈处理括号匹配，如果当前是左括号，压入栈，如果当前是右括号，看栈顶括号能否匹配，若可以，栈顶出栈，标记。

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

int stack[N],frt;
char a[N],b[N];

inline int index(char c){
    if (c == '(' || c== ')')
      return 1;
    else return 2;
}

int main(){
    scanf("%s",a);
    int len = strlen(a);
    for (int i = 0;i < len;i ++){
        if (a[i] == '(' || a[i] == '['){
            stack[++ frt] = i;
            if (a[i] == '(') b[i] = ')';
            else b[i] = ']';
        }
        else if (frt && index(a[i]) == index(a[stack[frt]]))
          b[stack[frt --]] = '*',b[i] = '*';
        else if (a[i] == ']') b[i] = '[';
        else b[i] = '(';
    }
    for (int i = 0;i < len;i ++){
        if (a[i] == ')' || a[i] == ']')
          if (b[i] != '*') putchar(b[i]);
        putchar(a[i]);
        if (a[i] == '(' || a[i] == '[')
          if (b[i] != '*') putchar(b[i]);
    }
    return 0;
}
```

## #1.4 [P2055 [ZJOI2009]假期的宿舍](https://www.luogu.com.cn/problem/P2055)

经典二分图匹配。

将学生看作左点，床看作右点，根据关系连边跑 $\texttt{dinic}$ 即可。

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
    ll val;
};
Edge e[N << 1];

int n,m,s,t,in[N],stay[N],T,opt;
ll maxflow;
int cnt,head[N],d[N],now[N],sum;
queue <int> q;

inline void add(const int &u,const int &v,const ll &w){
    e[cnt].u = u;e[cnt].v = v;e[cnt].val = w;
    e[cnt].nxt = head[u];head[u] = cnt ++;

    e[cnt].u = v;e[cnt].v = u;e[cnt].val = 0;
    e[cnt].nxt = head[v];head[v] = cnt ++;
}

inline bool bfs(){
    mset(d,0);
    while (q.size()) q.pop();
    q.push(s);d[s] = 1;now[s] = head[s];
    while (q.size()){
        int x = q.front();q.pop();
        for (int i = head[x];i != -1;i = e[i].nxt)
          if (e[i].val && !d[e[i].v]){
              q.push(e[i].v);
              now[e[i].v] = head[e[i].v];
              d[e[i].v] = d[x] + 1;
              if (e[i].v == t) return true;
          }
    }
    return false;
}

inline ll dinic(int x,ll flow){
    if (x == t) return flow;
    ll rest = flow,k,i;
    for (i = now[x];(i != -1) && rest;i = e[i].nxt){
        if (e[i].val && d[e[i].v] == d[x] + 1){
            k = dinic(e[i].v,min(rest,e[i].val));
            if (!k) d[e[i].v] = 0;
            e[i].val -= k;
            e[i ^ 1].val += k;
            rest -= k;
        }
        now[x] = i;
    }
    return flow - rest;
}

int main(){
    scanf("%d",&T);
    while (T --){
        mset(head,-1);cnt = 0;
        mset(now,0);sum = 0;maxflow = 0;
        scanf("%d",&n);
        for (int i = 1;i <= n;i ++)
          scanf("%d",&in[i]);
        for (int i = 1;i <= n;i ++)
          scanf("%d",&stay[i]);
        for (int i = 1;i <= n;i ++)
          if (in[i] && !stay[i])
            add(i,i + n,1);
        for (int i = 1;i <= n;i ++)
          if ((in[i] && !stay[i]) || !in[i])
            sum ++;
        for (int i = 1;i <= n;i ++)
          for (int j = 1;j <= n;j ++){
              scanf("%d",&opt);
              if (opt && (in[i] && (!stay[j] || !in[j])))
                add(j,i + n,1);
          }
        for (int i = 1;i <= n;i ++)
          add(0,i,1),add(i + n,2 * n + 1, 1);
        s = 0,t = 2 * n + 1;ll flow = 0;
        while (bfs()) while (flow = dinic(s,INF))
            maxflow += flow;
        if (maxflow >= sum) printf("^_^\n");
        else printf("T_T\n");
    }
    return 0;
}
```

## #1.5 [P2740 [USACO4.2]草地排水Drainage Ditches](https://www.luogu.com.cn/problem/P2740)

网络流板子题。

## #1.6 [P2341 [USACO03FALL][HAOI2006]受欢迎的牛 G](https://www.luogu.com.cn/problem/P2341)

因为具有传递性，显然先缩点，得到的图中的唯一一个出度为零的点中包含的牛的个数便是答案，如果出度为零的点多于一个，显然答案为 $0.$

``` cpp
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
```

## #1.7 [P3146 [USACO16OPEN]248 G](https://www.luogu.com.cn/problem/P3146)

区间 $\texttt{DP}$，设 $f_{l,r}$ 表示区间 $[l,r]$ 可以**合成出的值**。但题目是问**出现的最大值**，在转移过程中记录即可。

``` cpp
const int N = 510;
const int INF = 0x3fffffff;

int n,a[N],ans,f[N][N];

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++){
        scanf("%d",&a[i]);
        f[i][i] = a[i];
        ans = Max(ans,f[i][i]);
    }
    for (int ln = 2;ln <= n;ln ++)
      for (int l = 1;l + ln - 1<= n;l ++){
          int r = l + ln - 1;
          for (int k = l;k < r;k ++)
            if (f[l][k] == f[k + 1][r]){
                f[l][r] = Max(f[l][k] + 1,f[l][r]);
                ans = Max(ans,f[l][r]);
            }
      }
    printf("%d",ans);
    return 0;
}
```

## #1.8 [CF386B Fly, freebies, fly!](https://www.luogu.com.cn/problem/CF386B)

------

<div style="width=10px;line_height: 1px;">
<a href=https://www.cnblogs.com/Dfkuaid-210/p/CF386B.html style="text-decoration:none;">
      <font face="黑体" size=6>
            <b>[题解]CF386B Fly, freebies, fly!</b>
      </font>
      <font face="黑体" size=2>
            <br>&nbsp;&nbsp;发表于 2021-06-04 09:54&nbsp;Dfkuaid<br>
      </font>
      <font face="黑体" size=6>   </font>
      <font face="FangSong" size=4>
            摘要：&nbsp;CF386B Fly, freebies, fly! 题解&nbsp;<br>
      </font>
    <p align="right">
      <font face="黑体" size=4>
          阅读全文&nbsp;&nbsp;&nbsp;<br>
          <u>&nbsp;&nbsp;&nbsp;>>&nbsp;&nbsp;&nbsp;</u>&nbsp;&nbsp;&nbsp;<br>
      </font>
    </p>
</a>
</div>

------

## #1.9 [CF455A Boredom](https://www.luogu.com.cn/problem/CF455A)

简单的 $\texttt{DP}$，设 $f_{x,0/1}$ 表示 $x$ 这个数选/不选得到的最大值。

如果 $x$ 要选，那么 $x-1$ 必不能选，如果 $x$ 不选，$x-1$ 可以选也可以不选（有点树形 $\texttt{DP}$ 的味道）。

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

ll n,a[N],f[N][2],l;

int main(){
    scanf("%lld",&n);
    for (int i = 1;i <= n;i ++){
        ll x;scanf("%lld",&x);
        l = max(l,x);a[x] ++;
    }
    f[1][1] = a[1];
    for (int i = 2;i <= l;i ++){
        f[i][0] = max(f[i - 1][0],f[i - 1][1]);
        f[i][1] = f[i - 1][0] + i * a[i];
    }
    printf("%lld",max(f[l][0],f[l][1]));
    return 0;
}
```

## #1.10 [P2746 [USACO5.3]校园网Network of Schools](https://www.luogu.com.cn/problem/P2746)

显然先缩点，得到 $\texttt{DAG}$，第一个问题就是缩点后有多少点，第二个问题是缩点后入度为 $0$ 的点数和出度为 $0$ 的点数中的较大值。

``` cpp
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
```

# #2.0 转

> $\mathfrak{2021.6.11}\sim\mathfrak{2021.6.20}$

## #2.1 [P1343 地震逃生](https://www.luogu.com.cn/problem/P1343)

网络流板子题。

## #2.2 [CF1534F1 Falling Sand (Easy Version)](https://www.luogu.com.cn/problem/CF1534F1)

------

<div style="width=10px;line_height: 1px;">
<a href=https://www.cnblogs.com/Dfkuaid-210/p/CF1534F1.html style="text-decoration:none;">
      <font face="黑体" size=6>
            <b>[题解]CF1534F1 Falling Sand (Easy Version)</b>
      </font>
      <font face="黑体" size=2>
            <br>&nbsp;&nbsp;发表于 2021-06-14 19:59&nbsp;Dfkuaid<br>
      </font>
      <font face="黑体" size=6>   </font>
      <font face="FangSong" size=4>
            摘要：&nbsp;CF1534F1 Falling Sand (Easy Version) 题解&nbsp;<br>
      </font>
    <p align="right">
      <font face="黑体" size=4>
          阅读全文&nbsp;&nbsp;&nbsp;<br>
          <u>&nbsp;&nbsp;&nbsp;>>&nbsp;&nbsp;&nbsp;</u>&nbsp;&nbsp;&nbsp;<br>
      </font>
    </p>
</a>
</div>

------

## #2.3 [CF993E Nikita and Order Statistics](https://www.luogu.com.cn/problem/CF993E)

由于 $x$ 是定值，所以可以直接将原序列 $a$ 中小于 $x$ 的数赋值为 $1$，其他赋值为 $0$，这样原题转化为对于 $k=0\sim n$，有多少个区间满足和为 $k$，设 $s$ 为 $a$ 的前缀和，则需要求有多少个数对 $(s_i,s_j)$ 满足 $s_j-s_i=k$，设 $f_{s_i}$ 表示 $s_i$ 的出现次数，则有

$$
\begin{aligned}
\sum\limits_{i=k}^nf_if_{i-k}=&\sum\limits_{i=k}^nf_if_{n-(n+k-i)}=\sum\limits_{i+j=n+k}f_if_{n-j},\\
\end{aligned}
$$

令 $g_j=f_{n-j}$，于是有

$$
\begin{aligned}
\sum\limits_{i+j=n+k}f_if_{n-j}=\sum\limits_{i+j=n+k}f_ig_j,\\
\end{aligned}
$$

也就是 $f*g.$

不过要注意，上面的式子只适用于 $k>0$ 的情况。

那么对于 $k=0$ 的情况，我们注意到，只有前缀和数组中一串相同的数才会对答案造成贡献，但同时注意到，这一串数的第一个数不会造成贡献，因为这是前缀和改变的第一个数，此位置上必定为 $1$，于是一串长度为 $l$ 的相同的数的贡献为 $\sum\limits_{i=1}^{l-1}i=\dfrac{l(l-1)}{2}.$

``` cpp
const int N = 700010;
const double PI = acos(-1);
const int INF = 0x3fffffff;

typedef complex <double> cp;

ll a[N],n,sum[N];
ll r[N],x,ans;
ll t = 1,lt,cnt;
cp f[N],g[N];

inline void fft(cp *A,int opt){
    for (int i = 0;i < t;i ++)
      if (i < r[i]) swap(A[i],A[r[i]]);
    for (int mid = 1;mid < t;mid <<= 1){
        cp OMG(cos(PI / mid),opt * sin(PI / mid));
        for (int R = mid << 1,l = 0;l < t;l += R){
            cp omg(1,0);
            for (int k = 0;k < mid;k ++,omg *= OMG){
                cp tmp1 = A[l + k],tmp2 = omg * A[l + mid + k];
                A[l + k] = tmp1 + tmp2;
                A[l + mid + k] = tmp1 - tmp2;
            }
        }
    }
}

inline ll RS(int x){
    return (ll)(1 + x) * x / 2;
}

int main(){
    scanf("%lld%lld",&n,&x);
    for (int i = 1;i <= n;i ++){
        scanf("%lld",&a[i]);
        if (a[i] < x) a[i] = 1;
        else a[i] = 0;
    }
    f[0].real(1);g[n].real(1);
    for (int i = 1;i <= n;i ++){
        sum[i] = sum[i - 1] + a[i];
        f[sum[i]].real(f[sum[i]].real() + 1);
        g[n - sum[i]].real(g[n - sum[i]].real() + 1);
    }
    while (t <= 2 * n + 2) t <<= 1,lt ++;
    for (int i = 0;i < t;i ++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lt - 1));
    fft(f,1);fft(g,1);
    for (int i = 0;i < t;i ++) f[i] *= g[i];
    fft(f,-1);
    for (int i = 1;i <= n;i ++)
      if (sum[i] != sum[i - 1]){
          ans += RS(cnt);cnt = 0;
      }else cnt ++;
    ans += RS(cnt); cout << ans << " ";
    for (int i = n + 1;i <  2 * n + 1;i ++)
      cout << (ll)(f[i].real() / t + 0.5) << " ";
    return 0;
}
```

## #2.4 [P3723 [AH2017/HNOI2017]礼物](https://www.luogu.com.cn/problem/P3723)

简化题意，$a,b$ 是两个循环节长度为 $n$ 的数组，让我们求

$$
\min\limits_{c,k}\left\{\sum\limits_{i=1}^n(c+a_{i+k}-b_i)^2\right\},
$$

将上式展开得

$$
\begin{aligned}
&\sum\limits_{i=1}^n(c+a_{i+b}-b_i)^2\\
=&\sum\limits_{i=1}^n(c^2+a_{i+k}^2+b_i^2+2ca_{i+k}-2cb_i-2a_{i+k}b_i)\\
=&\sum\limits_{i=1}^n(c^2+a_i^2+b_i^2+2ca_i-2cb_i-2a_{i+k}b_i)\\
=&nc^2+\sum\limits_{i=1}^n(a_i^2+b_i^2)+2c\sum\limits_{i=1}^n(a_i-b_i)-2\sum\limits_{i=1}^na_{i+k}b_i.
\end{aligned}
$$

注意到 $\sum\limits_{i=1}^n(a_i^2+b_i^2)$ 和 $\sum\limits_{i=1}^n(a_i-b_i)$ 是对于给定数据的两个定值，所以式

$$
nc^2+2c\sum\limits_{i=1}^n(a_i-b_i)+\sum\limits_{i=1}^n(a_i^2+b_i^2)\tag1
$$

可看做关于 $c$ 的二次函数。由于 $n>0$，所以 $(1)$ 在

$$
c=-\dfrac{2\sum\limits_{i=1}^n(a_i-b_i)}{2n}=-\dfrac{\sum\limits_{i=1}^n(a_i-b_i)}{n}
$$

时取最小值（要考虑不能整除的情况）。我们还需要求 $\sum\limits_{i=1}^na_{i+k}b_i$ 的最大值，令 $t_i=b_{n-i}$，有

$$
\sum\limits_{i=1}^na_{i+k}b_i=\sum\limits_{i=1}^na_{i+k}t_{n-i}=d_{n+k}.
$$

于是 $k$ 对应的值便是 $a*t$ 中第 $n+k$ 项，取最大值即可。

这里要注意，因为要处理环的问题，所以需要将 $a$ 复制一遍。

``` cpp
const int N = 500010;
const double PI = acos(-1);
const int INF = 0x3fffffff;

typedef complex <double> cp;

ll t = 1,lt,r[N];
ll n,m,a[N],b[N],FV1,FV2,c,ans1,ans2;
cp f[N],g[N];

inline void fft(cp *A,int opt){
    /*...总之就是 FFT...*/
}

int main(){
    scanf("%lld%lld",&n,&m);
    for (int i = 1;i <= n;i ++){
        scanf("%lld",&a[i]);
        f[n - i + 1].real(a[i]);
        FV1 += a[i] * a[i];
        FV2 += a[i];
    }
    for (int i = 1;i <= n;i ++){
        scanf("%lld",&b[i]);
        g[i].real(b[i]);
        g[i + n].real(b[i]);
        FV1 += b[i] * b[i];
        FV2 -= b[i];
    }
    c = - FV2 / n;
    ans1 = min(min(n * c * c + 2 * c * FV2 + FV1,
        n * (c - 1) * (c - 1) + 2 * (c - 1) * FV2 + FV1),
        n * (c + 1) * (c + 1) + 2 * (c + 1) * FV2 + FV1);
    while (t <= 3 * n) t <<= 1,lt ++;
    for (int i = 0;i < t;i ++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lt - 1));
    fft(f,1),fft(g,1);
    for (int i = 0;i < t;i ++) f[i] *= g[i];
    fft(f,-1);
    for (int i = 1;i <= n;i ++)
      ans2 = max(ans2,(ll)(f[n + i].real() / t + 0.5));
    printf("%lld",ans1 - 2 * ans2);
    return 0;
}
```

## #2.5 [P1345 [USACO5.4]奶牛的电信Telecowmunication](https://www.luogu.com.cn/problem/P1345)

这题是让我们求将两点分开需删掉的最少点数，联想到最小割问题，但是注意到网络流是在边上进行操作，所以不能直接采用最大流求最小割。

将点转化为边的经典操作便是拆点，即将一个点拆成两个点：入点和分点，中间由一条有向边连接，所有终点为该点的边连向该点拆出的入点，所有起点为该点的边由该点拆出的出点连出。要注意，需要将无向边转化为两条有向边，图中的源点和汇点不需要拆点。

我们的策略是这样：原图中的边容量设为 $\infty$，拆点造成的边容量设为 $1$，在这张新图上求最小割。

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    ll w;
    int nxt;
};
Edge e[N << 2];

int n,m,s,t,cnt = 2,head[N];
int q[N << 2],frt,tal,d[N],now[N];
ll maxflow;

inline void add(const int &u,const int &v,const ll &w){
    e[cnt].u = u;e[cnt].v = v;e[cnt].w = w;
    e[cnt].nxt = head[u];head[u] = cnt ++;

    e[cnt].u = v;e[cnt].v = u;e[cnt].w = 0;
    e[cnt].nxt = head[v];head[v] = cnt ++;
}

inline bool bfs(){
    mset(d,0);
    frt = 0,tal = -1;
    q[++ tal] = s;d[s] = 1,now[s] = head[s];
    while (frt <= tal){
        int x = q[frt ++];
        for (int i = now[x];i;i = e[i].nxt){
            if (e[i].w && !d[e[i].v]){
              q[++ tal] = e[i].v;
              now[e[i].v] = head[e[i].v];
              d[e[i].v] = d[x] + 1;
              if (e[i].v == t) return true;
          }
        }
          
    }
    return false;
}

inline ll dinic(int x,ll flow){
    if (x == t) return flow;
    ll rest = flow,k,i;
    for (i = now[x];i && rest;i = e[i].nxt){
        if (e[i].w && d[e[i].v] == d[x] + 1){
            k = dinic(e[i].v,rest < e[i].w ? rest : e[i].w);
            if (!k) d[e[i].v] = 0;
            e[i].w -= k,e[i ^ 1].w += k,rest -= k;
        }
        now[x] = i;
    }
    return flow - rest;
}

int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i = 1;i <= n;i ++)
      if (i != s && i != t) add(i,i + n,1);
    for (int i = 1;i <= m;i ++){
        int x,y;scanf("%d%d",&x,&y);
        add((x == s || x == t) ? x : x + n,y,INF);
        add((y == s || y == t) ? y : y + n,x,INF);
    }
    ll flow = 0;
    while (bfs()) while (flow = dinic(s,INF))
      maxflow += flow;
    printf("%lld",maxflow);
    return 0;
}
```

<div id='king-of-hotel'></div>

## #2.6 [P1402 酒店之王](https://www.luogu.com.cn/problem/P1402)

第一眼的印象是二分图匹配，但发现实际是三个物品进行匹配（三分图最大匹配（bushi）？），我们发现房间和菜之间没有直接联系，只能靠客人联系起来，所以考虑将房间和菜分别看做点放在两边，客人看做点放在中间。

客人 $a$ 如果喜欢房间 $b$，就连边 $b\to a$，如果喜欢菜品 $c$，就连边 $a\to c$，最后左边加源点连向房间，菜品连向右边汇点，所有边的容量都设为 $1.$

然后就结束了。。。吗？

我们发现，现在只限制了房间和菜品仅能被选一次，但是客人可能会造成重复贡献，如：

![](https://pic.imgdb.cn/item/60cd8a4a844ef46bb2fc905b.png)

正确的答案应当是 $1$，但该网络的最大流为 $2$，原因是同一个客人被算了两次，那么我们就需要对客人这个点增加限制，这个点的容量只能为 $1$，但是网络流只能处理边权，所以再次考虑拆点，将一个客人变成一条容量为 $1$ 的边，再在这张图上跑最大流，就没有问题了。

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    ll val;
    int nxt;
};
Edge e[N << 1];

int n,p,q,cnt = 2,head[N],s,t;
int qx[N],frt,tal,d[N],now[N];
ll maxflow;

inline void add(const int &u,const int &v,const int &w){
    e[cnt].u = u,e[cnt].v = v,e[cnt].val = w;
    e[cnt].nxt = head[u],head[u] = cnt ++;

    e[cnt].u = v,e[cnt].v = u,e[cnt].val = 0;
    e[cnt].nxt = head[v],head[v] = cnt ++;
}

inline bool bfs(){
    mset(d,0);frt = 0,tal = -1;
    qx[++ tal] = s;d[s] = 1;now[s] = head[s];
    while (frt <= tal){
        int x = qx[frt ++];
        for (int i = head[x];i;i = e[i].nxt)
          if (e[i].val && !d[e[i].v]){
              qx[++ tal] = e[i].v;
              now[e[i].v] = head[e[i].v];
              d[e[i].v] = d[x] + 1;
              if (e[i].v == t) return true;
          }
    }
    return false;
}

inline ll dinic(int x,ll flow){
    if (x == t) return flow;
    ll rest = flow,k,i;
    for (i = now[x];i && rest;i = e[i].nxt){
        if (e[i].val && d[e[i].v] == d[x] + 1){
            k = dinic(e[i].v,min(rest,e[i].val));
            if (!k) d[e[i].v] = 0;
            e[i].val -= k;
            e[i ^ 1].val += k;
            rest -= k;
        }
        now[x] = i;
    }
    return flow - rest;
}

int main(){
    scanf("%d%d%d",&n,&p,&q);
    for (int i = 1;i <= n;i ++)
      add(p + i,n + p + q + i,1);
    for (int i = 1;i <= n;i ++)
      for (int j = 1;j <= p;j ++){
          int x;scanf("%d",&x);
          if (x) add(j,p + i,1);
      }
    for (int i = 1;i <= n;i ++)
      for (int j = 1;j <= p;j ++){
          int x;scanf("%d",&x);
          if (x) add(n + p + q + i,n + p + j,1);
      }
    s = 0,t = 2 * n + p + q + 1;
    for (int i = 1;i <= p;i ++) add(s,i,1);
    for (int i = 1;i <= q;i ++) add(n + p + i,t,1);
    ll flow = 0;
    while (bfs()) while (flow = dinic(s,INF))
      maxflow += flow;
    printf("%lld",maxflow);
    return 0;
}
```

## #2.7 [SP1043 GSS1 - Can you answer these queries I](https://www.luogu.com.cn/problem/SP1043)

猫树（分治树）的经典运用，详见

------

<div style="width=10px;line_height: 1px;">
<a href=https://www.cnblogs.com/Dfkuaid-210/p/cat_tree.html style="text-decoration:none;">
      <font face="黑体" size=6>
            <b>[数据结构入门]分治树（猫树）</b>
      </font>
      <font face="黑体" size=2>
            <br>&nbsp;&nbsp;发表于 2021-06-19 16:43&nbsp;Dfkuaid<br>
      </font>
      <font face="黑体" size=6>   </font>
      <font face="FangSong" size=4>
            摘要：&nbsp;分治树（猫树）的简单介绍&nbsp;<br>
      </font>
    <p align="right">
      <font face="黑体" size=4>
          阅读全文&nbsp;&nbsp;&nbsp;<br>
          <u>&nbsp;&nbsp;&nbsp;>>&nbsp;&nbsp;&nbsp;</u>&nbsp;&nbsp;&nbsp;<br>
      </font>
    </p>
</a>
</div>

------

``` cpp
const int N = 1000100;
const int INF = 0x3fffffff;

int loc[N],a[N],n,m,len = 2;
int s[25][N],p[25][N],lg[N];

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

inline void build(int k,int l,int r,int d){
    if (l == r) {loc[l] = k;return;}
    int mid = (l + r) >> 1;
    int pre,sm;
    s[d][mid] = a[mid],p[d][mid] = a[mid];
    pre = sm = a[mid];sm = sm > 0 ? sm : 0;
    for (int i = mid - 1;i >= l;i --){
        pre += a[i],sm += a[i];
        s[d][i] = Max(s[d][i + 1],pre),
        p[d][i] = Max(p[d][i + 1],sm);
        sm = sm > 0 ? sm : 0;
    }
    s[d][mid + 1] = a[mid + 1],
    p[d][mid + 1] = a[mid + 1];
    pre = sm = a[mid + 1];  sm = sm > 0 ? sm : 0;
    for (int i = mid + 2;i <= r;i ++){
        pre += a[i],sm += a[i];
        s[d][i] = Max(s[d][i - 1],pre);
        p[d][i] = Max(p[d][i - 1],sm);
        sm = sm > 0 ? sm : 0;
    }
    build(k << 1,l,mid,d + 1);
    build(k << 1 | 1,mid + 1,r,d + 1);
}

inline int query(int l,int r){
    if (l == r) return a[l];
    int d = lg[loc[l]] - lg[loc[l] ^ loc[r]];
    return Max(Max(p[d][l],p[d][r]),s[d][l] + s[d][r]);
}

int main(){
    scanf("%d",&n);
    while (len < n) len <<= 1;
    for (int i = 1;i <= n;i ++)
      scanf("%d",&a[i]);
    for (int i = 2;i <= len;i ++)
      lg[i] = lg[i >> 1] + 1;
    build(1,1,len,1);
    scanf("%d",&m);
    while (m --){
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",query(l,r));
    }
    return 0;
}

```

## #2.8 [P2495 [SDOI2011]消耗战](https://www.luogu.com.cn/problem/P2495)

普通的树形 $\texttt{DP}$ 并不难想，对于一个树上的非关键点 $x$，只有断掉它连向父亲的边和断掉连向子孙的边两种情况。断上面的情况可以在其父节点处理，所以只用考虑断连向子孙的边。如果 $x$ 的一个儿子是关键点，那么这条边必断，如果一个儿子不是关键点，考虑是断这个儿子上面还是下面，取最小值。

但是直接做时间复杂度爆炸，注意到 $\sum k_i\leq5\times10^5$，再发现有许多点没有用处，考虑建虚树处理。

建完虚树后，原来的 $\texttt{DP}$ 策略似乎不太可行了，注意到在虚树上的点除了关键点就是他们的 $\texttt{LCA}$，且叶节点均为关键点。

发现，如果一个点是关键点，那么，在它下面的关键点可以不加入虚树，因为在该点之上必然存在删除的边，从而导致下面的点也不联通。

按上面的想法建出虚树，不妨设 $f(x)$ 表示在虚树上以 $x$ 为根的子树（不包含 $x$）中的所有关键点与 $1$ 号节点断开需要的最小代价，显然有

$$
f(x)=\begin{cases}\min\left\{mn(x),\sum\limits_{y\in son_x}f(y)\right\},&|son_x|>0\\mn(x),&|son_x|=0\end{cases}
$$

其中 $mn(x)$ 表示从 $x$ 到 $1$ 号节点路径上的最小边权。现在能有子节点的只有 $\texttt{LCA}$ 了。考虑为什么可以取 $mn(x)$，对于 $x$ 的父节点 $fa_x$，如果连向 $x$ 的边 $(fa_x,x)$ 的边权大于 $mn(x)$，那么由于和式其余项相加大于等于 $0$；所以必然仍取 $mn(fa_x)$，如果 $(fa_x,x)=mn(x)$，正确性显然。

``` cpp
const int N = 2000010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    ll w;
    int nxt;
};
Edge e[N],ne[N];

int cnt = 1,head[N],n,m,ncnt = 1,nhead[N];
int son[N],dfn[N],T,st[N],stp,f[N];
int fa[N],size[N],d[N],top[N],fl[N];
ll mn[N];

inline ll Min(const ll &a,const ll &b){
    return a < b ? a : b;
}

inline void ADD(const int &u,const int &v,const ll &w){
    e[cnt].u = u;e[cnt].v = v;e[cnt].w = w;
    e[cnt].nxt = head[u];head[u] = cnt ++;
}

inline void add(const int &u,const int &v){
    ne[ncnt].u = u;ne[ncnt].v = v;
    ne[ncnt].nxt = nhead[u];nhead[u] = ncnt ++;
}

inline int cmp(const int &a,const int &b){
    return dfn[a] < dfn[b];
}

inline void dfs1(int x,int _fa){
    size[x] = 1,d[x] = d[_fa] + 1,fa[x] = _fa;
    for (int i = head[x];i;i = e[i].nxt){
        if (e[i].v == fa[x]) continue;
        mn[e[i].v] = Min(mn[x],e[i].w);
        dfs1(e[i].v,x);
        size[x] += size[e[i].v];
        if (size[e[i].v] > size[son[x]])
          son[x] = e[i].v;
    }
}

inline void dfs2(int x,int t){
    top[x] = t;dfn[x] = ++ T;
    if (!son[x]) return;
    dfs2(son[x],t);
    for (int i = head[x];i;i = e[i].nxt){
        if (e[i].v == fa[x] || e[i].v == son[x])
          continue;
        dfs2(e[i].v,e[i].v);
    }
}

inline int LCA(int a,int b){
    while (top[a] != top[b]){
        if(d[top[a]] < d[top[b]])
          swap(a,b);
        a = fa[top[a]];
    }
    if (d[a] < d[b]) swap(a,b);
    return b;
}

inline void ins(int x){
    if (stp == 1) {st[++ stp] = x;return;}
    int ance = LCA(x,st[stp]);
    if (ance == st[stp]) return;
    while (stp > 1 && d[ance] < d[st[stp - 1]])
      add(st[stp - 1],st[stp]),stp --;
    if (d[ance] < d[st[stp]]) add(ance,st[stp --]);
    if (!stp || st[stp] != ance) st[++ stp] = ance;
    st[++ stp] = x;
}

inline ll DP(int x){
    if (!nhead[x]) return mn[x];
    ll res = 0;
    for (int i = nhead[x];i;i = ne[i].nxt)
      res += DP(ne[i].v);
    nhead[x] = 0;
    return Min(mn[x],res);
}

int main(){
    mset(mn,0x3f);scanf("%d",&n);
    for (int i = 1;i < n;i ++){
        int u,v;ll w;
        scanf("%d%d%lld",&u,&v,&w);
        ADD(u,v,w);ADD(v,u,w);
    }
    dfs1(1,0);dfs2(1,1);
    scanf("%d",&m);
    while (m --){
        int k,a[N];ncnt = 1;
        scanf("%d",&k);st[stp = 1] = 1;
        for (int i = 1;i <= k;i ++)
          scanf("%d",&a[i]);
        sort(a + 1,a + k + 1,cmp);
        for (int i = 1;i <= k;i ++) ins(a[i]);
        while (stp) add(st[stp - 1],st[stp]),stp --;
        printf("%lld\n",DP(1));
    }
    return 0;
}
```

## #2.9 [P1231 教辅的组成](https://www.luogu.com.cn/problem/P2495)

[P1402 酒店之王](#king-of-hotel) 的双倍经验。

# #3.0 合

## #3.1 [CF613D Kingdom and its Cities](https://www.luogu.com.cn/problem/CF613D)

同样是虚树，建虚树的部分不多说，直接看树形 $\texttt{DP}.$

``` cpp
const int N = 1000010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N],ne[N];

int cnt = 1,ncnt = 1,head[N],nhead[N],T;
int fa[N],d[N],son[N],size[N],dfn[N],top[N];
int tag[N],n,q,k,st[N],stp,a[N];

inline int cmp(const int &a,const int &b){
    return dfn[a] < dfn[b];
}

inline void ADD(const int &u,const int &v){
    e[cnt].u = u,e[cnt].v = v;
    e[cnt].nxt = head[u];head[u] = cnt ++;
}

inline void add(const int &u,const int &v){
    ne[ncnt].u = u,ne[ncnt].v = v;
    ne[ncnt].nxt = nhead[u];nhead[u] = ncnt ++;
}

void dfs1(int x,int _fa){
    fa[x] = _fa,d[x] = d[_fa] + 1,size[x] = 1;
    for (int i = head[x];i;i = e[i].nxt){
        if (e[i].v == fa[x]) continue;
        dfs1(e[i].v,x);
        size[x] += size[e[i].v];
        if (size[e[i].v] > size[son[x]])
          son[x] = e[i].v;
    }
}

void dfs2(int x,int t){
    dfn[x] = ++ T,top[x] = t;
    if (!son[x]) return;
    dfs2(son[x],t);
    for (int i = head[x];i;i = e[i].nxt)
      if (e[i].v != fa[x] && e[i].v != son[x])
        dfs2(e[i].v,e[i].v);
}

inline int LCA(int a,int b){
    while (top[a] != top[b]){
        if (d[top[a]] < d[top[b]])
          swap(a,b);
        a = fa[top[a]];
    }
    return d[a] > d[b] ? b : a;
}

inline void insert(int x){
    if (!stp){st[++ stp] = x;return;}
    int ance = LCA(x,st[stp]);
    while (stp > 1 && d[st[stp - 1]] > d[ance])
      add(st[stp - 1],st[stp]),stp --;
    if (d[ance] < d[st[stp]])
      add(ance,st[stp]),stp --;
    if (!stp || ance != st[stp])
      st[++ stp] = ance;
    st[++ stp] = x;
}

int DP(int x){
    if (!nhead[x]) return 0;
    int scnt = 0,res = 0;
    for (int i = nhead[x];i;i = ne[i].nxt){
        res += DP(ne[i].v);
        if (tag[ne[i].v]) scnt ++;
        tag[ne[i].v] = false;
    }
    if (scnt == 1 && !tag[x]) tag[x] = true;
    else if (scnt == 1 && tag[x]) res ++;
    else if (scnt > 1) if (tag[x]) res += scnt;
    else res ++; 
    nhead[x] = 0;if (x == 1) tag[x] = false;
    return res;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i < n;i ++){
        int u,v;scanf("%d%d",&u,&v);
        ADD(u,v);ADD(v,u);
    }
    dfs1(1,0);dfs2(1,1);
    scanf("%d",&q);
    while (q --){
        scanf("%d",&k);
        int ck = 0;stp = 0;
        for (int i = 1;i <= k;i ++){
            scanf("%d",&a[i]);
            tag[a[i]] = true;
        }
        for (int i = 1;i <= k;i ++)
          if (tag[fa[a[i]]]){ck = 1;break;}
        if (ck){
            printf("-1\n");
            for (int i = 1;i <= k;i ++)
              tag[a[i]] = false;
            continue;
        }
        sort(a + 1,a + k + 1,cmp);
        if (a[1] != 1) insert(1);
        for (int i = 1;i <= k;i ++) insert(a[i]);
        while (stp) add(st[stp - 1],st[stp]),stp --;
        printf("%d\n",DP(1));
    }
    return 0;
}
```

## #3.2 [P2891 [USACO07OPEN]Dining G](https://www.luogu.com.cn/problem/P2891)

[酒店之王](#king-of-hotel) 三倍经验。

## #3.3 [P4103 [HEOI2014]大工程](https://www.luogu.com.cn/problem/P4103)

同样是虚树，还是直接看树形 $\texttt{DP}$，

``` cpp
const int N = 2e6;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N],ne[N];

int n,q,k,cnt = 1,ncnt = 1,head[N],nhead[N];
int fa[N],d[N],son[N],size[N],slch[N],ssch[N];
int top[N],dfn[N],T,st[N],stp,lch[N],sch[N],nson[N];
int tot[N],sum_d[N],mn[N],mx[N],sum[N],a[N],tag[N];

template <typename T>
inline T Max(T a,T b){
    return a > b ? a : b;
}

template <typename T>
inline T Min(T a,T b){
    return a < b ? a : b;
}

inline int cmp(const int &a,const int &b){
    return dfn[a] < dfn[b];
}

inline void ADD(const int &u,const int &v){
    e[cnt].u = u,e[cnt].v = v;
    e[cnt].nxt = head[u];head[u] = cnt ++;
}

inline void add(const int &u,const int &v){
    ne[ncnt].u = u,ne[ncnt].v = v;
    ne[ncnt].nxt = nhead[u];nhead[u] = ncnt ++;
}

void dfs1(int x,int _fa){
    fa[x] = _fa,d[x] = d[_fa] + 1,size[x] = 1;
    for (int i = head[x];i;i = e[i].nxt){
        if (e[i].v == fa[x]) continue;
        dfs1(e[i].v,x);size[x] += size[e[i].v];
        if (size[son[x]] < size[e[i].v])
          son[x] = e[i].v;
    }
}

void dfs2(int x,int t){
    dfn[x] = ++ T,top[x] = t;
    if (!son[x]) return;
    dfs2(son[x],t);
    for (int i = head[x];i;i = e[i].nxt)
      if (e[i].v != fa[x] && e[i].v != son[x])
        dfs2(e[i].v,e[i].v);
}

inline int LCA(int a,int b){
    while (top[a] != top[b]){
        if (d[top[a]] < d[top[b]])
          swap(a,b);
        a = fa[top[a]];
    }
    return d[a] < d[b] ? a : b;
}

inline void insert(int x){
    nson[x] = 0;
    if (!stp){st[++ stp] = x;return;}
    int ance = LCA(st[stp],x);nson[ance] = 0;
    while (stp > 1 && d[st[stp - 1]] > d[ance])
      add(st[stp - 1],st[stp]),stp --;
    if (d[ance] < d[st[stp]])
      add(ance,st[stp]),stp --;
    if (!stp || st[stp] != ance)
      st[++ stp] = ance;
    st[++ stp] = x;
}

void solve(int x){
    mn[x] = INF;mx[x] = 0;tot[x] = sum[x] = sum_d[x] = 0;
    lch[x] = slch[x] = 0;sch[x] = ssch[x] = INF;
    for (int i = nhead[x];i;i = ne[i].nxt){
        solve(ne[i].v);nson[x] ++;

        if (lch[ne[i].v] > lch[x]){
            slch[x] = lch[x];
            lch[x] = lch[ne[i].v];
        }else slch[x] = Max(slch[x],lch[ne[i].v]);
        if (nson[x] > 1) mx[x] = Max(Max(mx[x],mx[ne[i].v]),lch[x] + slch[x] - 2 * d[x]);
        else mx[x] = mx[ne[i].v];
        
        if (sch[ne[i].v] < sch[x]){
            ssch[x] = Min(sch[x],ssch[ne[i].v]);
            sch[x] = sch[ne[i].v];
        }else ssch[x] = Min(ssch[x],sch[ne[i].v]);
        if (nson[x] > 1) mn[x] = Min(Min(mn[x],mn[ne[i].v]),sch[x] + ssch[x] - 2 * d[x]);
        else mn[x] = mn[ne[i].v];
        
        sum[x] += tot[x] * sum_d[ne[i].v] + tot[ne[i].v] * sum_d[x]
                  - 2 * tot[x] * tot[ne[i].v] * d[x];
        sum[x] += sum[ne[i].v];
        tot[x] += tot[ne[i].v];sum_d[x] += sum_d[ne[i].v];
    }
    if (tag[x]){
        ssch[x] = sch[x];sch[x] = d[x];
        mn[x] = Min(mn[x],ssch[x] - sch[x]);

        if (!nhead[x]) lch[x] = d[x];
        else if (!slch[x]) slch[x] = d[x];
        mx[x] = Max(mx[x],lch[x] - sch[x]);
        
        sum[x] += sum_d[x] - d[x] * tot[x];
        sum_d[x] += d[x];tot[x] ++;
    }
    nhead[x] = 0;tag[x] = false;
}

inline int st_print(){
    printf("STACK: ");
    for (int i = 1;i <= stp;i ++)
      printf("%d ",st[i]);
    cout << endl;
}

signed main(){
    scanf("%lld",&n);
    for (int i = 1;i < n;i ++){
        int u,v;scanf("%lld%lld",&u,&v);
        ADD(u,v);ADD(v,u);
    }
    dfs1(1,0);dfs2(1,1);
    scanf("%lld",&q);
    while (q --){
        scanf("%lld",&k);stp = 0;
        for (int i = 1;i <= k;i ++){
            scanf("%lld",&a[i]);
            tag[a[i]] = true;
        }
        sort(a + 1,a + k + 1,cmp);
        if (a[1] != 1) insert(1);
        for (int i = 1;i <= k;i ++) insert(a[i]);
        while (stp) add(st[stp - 1],st[stp]),stp --;
        solve(1);
        printf("%lld %lld %lld\n",sum[1],mn[1],mx[1]);
    }
    return 0;
}
```

## #3.4 [P3806 【模板】点分治1](https://www.luogu.com.cn/problem/P3806)

我们可以先将问题离线下来，一次点分治处理。

考虑一条长为 $k$ 的路径，假设根为 $rt$，那么一共有经过 $rt$ 与不经过两种情况，不经过的情况可以递归处理。

来看经过 $rt$ 的情况，那么如果在某棵子树中出现了距离 $rt$ 为 $l$ 的链，那么如果 $k-l$ 在其他的子树中出现，那么 $k$ 就一定可以出现，注意到 $k-l$ 和 $l$ 的出现顺序并无影响，所以便可以一棵一棵子树地维护，具体方法是：

- $\texttt{DFS}$ 处理当前子树上每个点与 $rt$ 的距离；
- 在 $\texttt{DFS}$ 的过程中，同时统计有哪些长度出现；
- 与之前子树中出现的边结合，更新答案；
- 将当前子树出现的信息并入。

最后要清空记录的之前子树中出现的边的信息，不要直接使用 `memset()`，应用队列保证时间复杂度正确。

之后便递归进入子树进行点分治。

``` cpp
const int N = 100010;
const int INF = 0x7fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N];

int n, m, cnt = 1, head[N], qs[N], ans[N];
int rt, sum, siz[N], mx[N], vis[N], tf[10000010];
int dist[N], dd[N], dcnt, q[N], frt, tal;

/*head[], cnt 是存图的，qs[] 存储每一个询问，
ans[] 存储对应问题的结果，rt 是当前子树选定的根，
sum 是当前子树的总大小，siz[x] 是以 x 为根的子树的大小
mx[x] 记录若选择 x 为根，则他的最大子树的大小
vis[] 表示当前点是否已被处理
tf[x] 存储已处理子树上是否有长度为 x 的链
dist[x] 储存 x 距离 rt 的距离，
dd[x] 记录当前子树拥有的链（长度）
dcnt 记录当前子树到 rt 的链的个数，
q[], frt, tal 是队列，用于清空 tf[]*/

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

void calcsiz(int x, int fa) {
    siz[x] = 1, mx[x] = 0; //初始化
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa || vis[e[i].v]) continue;
        calcsiz(e[i].v,x);
        siz[x] += siz[e[i].v];
        mx[x] = Max(mx[x], siz[e[i].v]);
    }
    mx[x] = Max(mx[x], sum - siz[x]);
    if (mx[x] < mx[rt]) rt = x;
}

void calcdist(int x, int fa) {
    dd[++ dcnt] = dist[x];
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v]) {
          dist[e[i].v] = dist[x] + e[i].w;
          calcdist(e[i].v, x);
      }
}

void dfz(int x, int fa) {
    frt = 0, tal = -1, q[++ tal] = 0;
    tf[0] = true, vis[x] = true; //初始化与进行标记
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa || vis[e[i].v]) continue;
        dist[e[i].v] = e[i].w;calcdist(e[i].v, x);
        for (int k = 1; k <= dcnt;k ++)
          for (int j = 1; j <= m;j ++) //枚举所有的询问
            if (qs[j] >= dd[k]) ans[j] |= tf[qs[j] - dd[k]];
        for (int j = 1; j <= dcnt; j ++)
          if (dd[j] < 10000010)
              q[++ tal] = dd[j],tf[dd[j]] = true;
            //观察数据范围可知，询问不会超过 1e7.
        dcnt = 0;
    }
    while (frt <= tal) tf[q[frt ++]] = false;
    /*递归进入子树*/
    for (int i = head[x]; i; i = e[i].nxt){
        if (e[i].v == fa || vis[e[i].v]) continue;
        sum = siz[e[i].v], mx[rt = 0] = INF;
        calcsiz(e[i].v, x); calcsiz(rt, -1);
        dfz(rt, x);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i ++) {
        int u, v, w;scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);add(v, u, w);
    }
    for (int i = 1; i <= m; i ++) scanf("%d", qs + i);
    mx[rt = 0] = INF, sum = n;
    calcsiz(1, -1); calcsiz(rt, -1); dfz(rt, -1);
    for (int i = 1;i <= m;i ++)
      if (ans[i]) printf("AYE\n");
      else printf("NAY\n");
    return 0;
}
```

## #3.5 [P4178 Tree](https://www.luogu.com.cn/problem/P4178)

点分治不多说，我们主要来看信息怎么维护。

我们当然可以统计出子树中每个点与 $rt$ 距离进行维护，但那样太麻烦了，考虑简便一点的方法。

我们可以计算出每个点所属于 $rt$ 的哪一棵子树 `b[x]`，特别的，令 `b[rt]=rt`。将所有节点（包括 $rt$）按照与 $rt$ 的距离从小到大排序，得到数组 `subt[]`，采用双指针 `l,r` 分别从头尾遍历。如果当前所指的点与 $rt$ 距离和大于 $k$，那么就让 `r --`，因为此时 `l` 右侧的点与 $rt$ 的距离只会更大，直到 `dist[subt[l]] + dist[subt[r]] <= k`，那么此时 `l+1` 到 `r` 这一段的点都是与 `l` 所指的点与 $rt$ 的距离和小于等于 $k$ 的，但是其中可能有与 $l$ 所指的节点在同一子树内的，这种情况不合法，应当舍去，所以我们应当维护 `cnt[x]` 表示在区间 $[l + 1,r]$ 中以 $x$ 为根的点的数量，更新的答案即为 `r - l - cnt[subt[l]]`.

``` cpp
const int N = 100010;
const int INF = 0x7fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N];

int n, m, cnt = 1, head[N], dcnt, res;
int siz[N], mx[N], rt, sum, vis[N], dist[N];
int b[N], subt[N], scnt[N];

/*head[], cnt 是存图的，rt 是当前子树选定的根，
sum 是当前子树的总大小，siz[x] 是以 x 为根的子树的大小
mx[x] 记录若选择 x 为根，则他的最大子树的大小
vis[] 表示当前点是否已被处理，dist[x] 储存 x 距离 rt 的距离，
dcnt 记录当前子树节点个数，b[x] 存储 x 属于 rt 的哪棵子树
subt[] 存储子树节点，scnt[x] 是上文中的 'cnt'*/

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

inline int cmp(const int &a, const int &b) {
    return dist[a] < dist[b];
}

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

void calcsiz(int x, int fa) {
    siz[x] = 1, mx[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v]) {
          calcsiz(e[i].v, x);
          siz[x] += siz[e[i].v];
          mx[x] = Max(mx[x], siz[e[i].v]);
      }
    mx[x] = Max(mx[x], sum - siz[x]);
    if (mx[x] < mx[rt]) rt = x;
}

void calcdist(int x, int fa) {
    if (fa != rt) b[x] = b[fa];
    else b[x] = x;
    subt[++ dcnt] = x, scnt[b[x]] ++;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v])
        dist[e[i].v] = dist[x] + e[i].w,
        calcdist(e[i].v, x);
}

void dfz(int x, int fa) {
    subt[++ dcnt] = x, b[x] = x, dist[x] = scnt[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v]) {
          dist[e[i].v] = e[i].w; scnt[e[i].v] = 0;
          calcdist(e[i].v, x);
      }
    sort(subt + 1, subt + dcnt + 1, cmp);
    int l = 1, r = dcnt; vis[x] = true;
    while (l < r) {
        while (dist[subt[l]] + dist[subt[r]] > m)
          scnt[b[subt[r]]] --, r --;
        res += r - l - scnt[b[subt[l]]];
        l ++, scnt[b[subt[l]]] --;
    }
    dcnt = 0;
    for (int i = head[x]; i;i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v]){
          sum = siz[e[i].v], mx[rt = 0] = INF;
          calcsiz(e[i].v, x); calcsiz(rt, -1);
          dfz(rt, x);
      }
}

int main() {
    nowt = time(0);
    scanf("%d", &n);
    for (int i = 1; i < n; i ++) {
        int u, v, w;scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    mx[rt = 0] = INF, sum = n;
    calcsiz(1, -1); calcsiz(rt, -1);
    scanf("%d", &m); dfz(rt, -1);
    printf("%d", res);
    return 0;
}
```

## #3.6 [P2634 [国家集训队]聪聪可可](https://www.luogu.com.cn/problem/P2634)

题目实际上让求长度是 $3$ 的倍数的有序点对的个数。

看到这题，笔者首先想到的是树形 $\texttt{DP}$ 而非点分治，当然树形 $DP$ 是可做的，与点分治转移的方式接近，且时间复杂度似乎更优一些，但树形 $\texttt{DP}$ 并不是本文所讨论的内容，这里不做说明，来看看本题点分治的做法。

一样的考虑方式，假设根为 $rt$，那么一共有经过 $rt$ 与不经过两种情况，不经过的情况可以递归处理。

来看经过 $rt$ 的情况，能够拼成 $3$ 的倍数的情况只有以下 $2$ 种：

- 两边链长度都是 $3$ 的倍数；
- 一边链长度模 $3$ 余 $1$，另一边模 $3$ 余 $2$；

我们可以统计每棵子树上与 $rt$ 的距离 $3$ 的倍数、长度模 $3$ 余 $1$、模 $3$ 余 $2$ 的点的个数 $b_0,b_1,b_2$，设前面的子树上所有与 $rt$ 的距离 $3$ 的倍数、长度模 $3$ 余 $1$、模 $3$ 余 $2$ 的点的个数分别为 $db_0,db_1,db_2$，那么这棵子树上可贡献的数量为

$$
b_0\times db_0+b_1\times db_2+b_2\times db_1+b_0,
$$

累加入答案，之后将 $b$ 与 $db$ 合并。最后递归进入子树进行点分治。

注意到，$(1,2)$ 与 $(2,1)$ 是两种不同的答案，单个点（即路径长度为 $0$）也是一种答案，故统计出的答案应当乘二再加上总共点的个数。总共有 $n^2$ 种不同的路径，别忘要分子分母化为互质的两个数。

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N];

int n, cnt = 1, head[N], vis[N], db[5], res;
int siz[N], mx[N], rt, sum, b[5], dist[N], dcnt;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

int gcd(int a, int b){
    if (!b) return a;
    return gcd(b, a % b);
}

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

void calcsiz(int x, int fa) {
    siz[x] = 1, mx[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v]) {
          calcsiz(e[i].v, x);
          siz[x] += siz[e[i].v];
          mx[x] = Max(mx[x], siz[e[i].v]);
      }
    mx[x] = Max(mx[x], sum - siz[x]);
    if (mx[x] < mx[rt]) rt = x;
}

void calcdist(int x, int fa) {
    b[dist[x] % 3] ++;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa && !vis[e[i].v])
        dist[e[i].v] = dist[x] + e[i].w,
        calcdist(e[i].v, x);
}

void dfz(int x, int fa) {
    vis[x] = true, db[0] = db[1] = db[2] = 0, dist[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa || vis[e[i].v]) continue;
        b[0] = b[1] = b[2] = 0;
        dist[e[i].v] = e[i].w;
        calcdist(e[i].v, x);
        res += b[0] * db[0] + b[1] * db[2] + b[2] * db[1];
        db[0] += b[0], db[1] += b[1], db[2] += b[2];
    }
    res += db[0];
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa || vis[e[i].v]) continue;
        sum = siz[e[i].v], mx[rt = 0] = INF;
        calcsiz(e[i].v, x); calcsiz(rt, -1);
        dfz(rt, x);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i ++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    sum = n, mx[rt = 0] = INF;
    calcsiz(1, -1); calcsiz(rt, -1);
    dfz(rt, -1); res = res * 2 + n;
    int gd = gcd(res, n * n);
    printf("%d/%d", res / gd, n * n / gd);
    return 0;
}

```

## #3.7 [UVA11374 Airport Express](https://www.luogu.com.cn/problem/UVA11374)

从起点和终点分别做最短路，枚举使用票的路段即可。

``` cpp
#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define pii pair<int, int>
#define mp(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N], bus[N];

int n, s, t, m, k, cnt = 1, head[N], pre[N][3], use1;
int ans, bcnt = 1, dist[N][3], vis[N], use, st, ho;

priority_queue <pii > q;

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

void Dijkstra(int u, bool opt) {
    dist[u][opt] = 0; mset(vis, 0);
    q.push(mp(0, u));
    while (q.size()) {
        int now = q.top().second; q.pop();
        if (vis[now]) continue;
        vis[now] = true;
        for (int i = head[now]; i; i = e[i].nxt)
          if (dist[e[i].v][opt] > dist[now][opt] + e[i].w) {
              dist[e[i].v][opt] = dist[now][opt] + e[i].w;
              pre[e[i].v][opt] = now;
              q.push(mp(-dist[e[i].v][opt], e[i].v));
          }
    }
}

void print_1(int f, int x) {
    if (pre[x][0]) print_1(f + 1, pre[x][0]);
    printf("%d", x);
    if (f) cout << " ";
}

void print_2(int f, int x) {
    if (!f) cout << " ";
    printf("%d", x);
    if (pre[x][1]) {
        printf(" ");
        print_2(f + 1,pre[x][1]);
    }
}

int main() {
//    freopen("out.txt", "w", stdout);
    while (cin >> n >> s >> t) {
        cnt = bcnt = 1, st = use = use1 = 0;
        scanf("%d", &m); mset(head, 0);
        for (int i = 1; i <= m; i ++){
            int x, y, z; scanf("%d%d%d", &x, &y, &z);
            add(x, y, z); add(y, x, z);
        }
//        for (int i = 1; i < cnt; i ++) {
//            printf("%d: %d -> %d : %d, nxt:%d\n", i, e[i].u, e[i].v, e[i].w, e[i].nxt);
//        }
        mset(dist, 0x3f); mset(pre, 0);
        Dijkstra(s, 0); Dijkstra(t, 1);
        ans = dist[t][0];
        scanf("%d", &k);
        for (int i = 1; i <= k; i ++) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            bus[++ bcnt].u = u, bus[bcnt].v = v, bus[bcnt].w = w;
            bus[++ bcnt].u = v, bus[bcnt].v = u, bus[bcnt].w = w;
            if (dist[u][0] + dist[v][1] + w < ans)
              ans = dist[u][0] + dist[v][1] + w,
              use = i, use1 = bcnt - 1, st = u;
            if (dist[v][0] + dist[u][1] + w < ans)
              ans = dist[v][0] + dist[u][1] + w,
              use = i, st = v, use1 = bcnt;
        }
        if (ho) puts("");
        else ho = true;
        if (!use) {
            print_1(0, t);
            printf("\nTicket Not Used\n%d", ans);
        } else {
            print_1(0, bus[use1].u); print_2(0, bus[use1].v);
            printf("\n%d\n%d", st, ans);
        }
        puts("");
    }
    return 0;
}
```

## #3.8 [UVA10917 Walk Through the Forest](https://www.luogu.com.cn/problem/UVA10917)

本题最需要理解的是这句话：

**如果有一条从B到他的家的路线比从A到他的家的任何可能的路线都短,那么他认为从A到B更好。**

设 $d_x$ 表示 $x$ 到 $2$ 号节点的最短路，那么上文的意思就是如果 $A,B$ 间存在道路且 $d_B<d_A$，那么道路 $A\to B$ 便是一种可行的选择。

根据上面那句话，我们便需要先处理出所有点到 $2$ 号点的最短距离。然后按照上面的要求重新建图，这里建出的边是单向边，再注意到得到的图是一张**有向无环图**（$\texttt{DAG}$），因为每条边的边权都是非负数，用反证法不难证明得到的最短路图不存在环。

此时考虑 $\texttt{DAG}$ 上的动态规划，设 $sum_x$ 表示从 $1$ 号节点到 $x$ 号节点可行的路径条数，显然有

$$
sum_x=\sum\limits_{(y,x)\in E}sum_y.
$$

这里 $E$ 表示边集，有序数对 $(u,v)$ 表示一条从 $u$ 的 $v$ 的有向边。边界为 $sum_1=1.$

同时注意到，节点 $1$ 不一定是入度为 $0$ 的点，入度为零的点除 $1$ 外不会对答案造成贡献。

拓扑结束后得到的结果便是本题所求。

``` cpp
#define pii pair<int, int>
#define mp(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))

const int N = 100010;
const int INF = 0x7fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N], ne[N];

int cnt = 1, ncnt = 1, head[N], nhead[N];
int dist[N], vis[N], tot[N], s, t, icnt[N];
int qx[N], frt, tal, tag[N], n, m;

priority_queue <pii > q;

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

inline void addn(const int &u, const int &v) {
    ne[ncnt].u = u, ne[ncnt].v = v, icnt[v] ++;
    ne[ncnt].nxt = nhead[u], nhead[u] = ncnt ++;
}

void Dijkstra() {
    mset(dist, 0x3f);
    q.push(mp(0,2)); dist[2] = 0;
    while (q.size()) {
        int now = q.top().second; q.pop();
        if (vis[now]) continue;
        vis[now] = true;
        for (int i = head[now]; i; i = e[i].nxt)
          if (dist[e[i].v] > dist[now] + e[i].w) {
              dist[e[i].v] = dist[now] + e[i].w;
              q.push(mp(-dist[e[i].v], e[i].v));
          }
    }
}

inline void clear() {
    frt = 0, tal = -1; 
    ncnt = cnt = 1; mset(tot, 0);
    mset(icnt, 0); mset(tag, 0);
    mset(vis, 0); mset(dist, 0x3f);
    mset(head, 0); mset(nhead, 0);
}

void topo() {
    mset(vis, 0);
    for (int i = 1; i <= n; i ++) 
      if (!icnt[i] || i == 1) qx[++ tal] = i;
    tag[1] = tot[1] = vis[1] = 1;
    while (frt <= tal) {
        int now = qx[frt ++];
        for (int i = nhead[now]; i;i = ne[i].nxt) {
            icnt[ne[i].v] --;
            if (tag[now]) {
                tot[ne[i].v] += tot[now], 
                tag[ne[i].v] |= tag[now];
            }
            if (!icnt[ne[i].v] && !vis[ne[i].v]) {
                qx[++ tal] = ne[i].v;
                vis[ne[i].v] == true;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    while (n) {
        scanf("%d", &m); s = 1, t = 2; clear();
        for (int i = 1; i <= m; i ++) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            add(u, v, w); add(v, u, w);
        }
        Dijkstra();
        for (int i = 1; i <= n; i ++)
          for (int j = head[i]; j; j = e[j].nxt)
            if (dist[i] > dist[e[j].v])
              addn(i, e[j].v);
        topo();
        printf("%d\n", tot[t]);
        scanf("%d", &n);
    }
    return 0;
}
```

## #3.9 [P1997 faebdc 的烦恼](https://www.luogu.com.cn/record/list?user=162191&page=1)

区间众数，考虑分块，假设所查询区间包含至少一个块，则有这样的性质：这个区间的众数要么是块的众数，要么是不在块内的数。利用这一点，可以做到 $O(n\sqrt n)$ 的预处理和 $O(\sqrt n)$ 的单次查询。但空间消耗相应的很大，但本题可以卡过去。

整体思路很简单，将序列分为长度 $\sqrt n$ 的块，这样的块可以拼成 $n$ 个大块，预处理出每一个大块中的最大数量，这一步时间复杂度是 $O(n\sqrt n)$。每一次询问按上面的性质查询即可。

``` cpp
const int N = 100010;
const int M = 320;
const int INF = 0x3fffffff;

int n,len,id[N],sub[M][2],a[N],q,ncnt;
int sum[M][N],st[N],vis[N],mxc[M][M];

template <typename T>
inline T Max(const T a,const T b){
    return a > b ? a : b;
}

inline void Disc(int *k){
    for (int i = 1;i <= n;i ++)
      st[i] = k[i];
    sort(st + 1,st + n + 1);
    ncnt = unique(st + 1,st + n + 1) - st - 1;
    for (int i = 1;i <= n;i ++)
      k[i] = lower_bound(st + 1,st + ncnt + 1,k[i]) - st;
}

inline void divide(){
    len = sqrt(n); 
    for (int i = 1;i <= n;i ++)
      id[i] = (i - 1) / len + 1;
    for (int i = 1;i <= id[n];i ++){
        sub[i][0] = (i - 1) * len + 1;
        sub[i][1] = i * len;
    }
    sub[id[n]][1] = min(sub[id[n]][1],n);
}

inline int query(int x,int y){
    int l = id[x],r = id[y],res = 0;
    if (l == r){
        for (int i = x;i <= y;i ++)
          res = Max(res,++ vis[a[i]]);
        for (int i = x;i <= y;i ++)
          vis[a[i]] = 0;
        return res;
    }
    for (int i = x;i <= sub[l][1];i ++)
      res = Max(res,(++ vis[a[i]]) + sum[r - 1][a[i]] - sum[l][a[i]]);
    for (int i = sub[r][0];i <= y;i ++)
      res = Max(res,(++ vis[a[i]]) + sum[r - 1][a[i]] - sum[l][a[i]]);
    res = Max(res,mxc[l + 1][r - 1]);
    for (int i = x;i <= sub[l][1];i ++) vis[a[i]] = 0;
    for (int i = sub[r][0];i <= y;i ++) vis[a[i]] = 0;
    return res;
}

int main(){
    scanf("%d%d",&n,&q);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&a[i]);
    Disc(a);divide();
    for (int i = 1;i <= n;i ++){
        sum[id[i]][a[i]] ++;
        if (sum[id[i]][a[i]] > mxc[id[i]][id[i]])
          mxc[id[i]][id[i]] = sum[id[i]][a[i]];
    }
    for (int i = 1;i <= id[n];i ++)
      for (int j = 1;j <= ncnt;j ++)
        sum[i][j] += sum[i - 1][j];
    for (int len = 2;len <= id[n];len ++)
      for (int l = 1;l + len <= id[n] + 1;l ++){
          int r = l + len - 1;
          for (int i = sub[r][0];i <= sub[r][1];i ++){
               int upd = sum[r - 1][a[i]] - sum[l - 1][a[i]] + (++ vis[a[i]]);
               if (mxc[l][r] < upd) mxc[l][r] = upd;
          }
          for (int i = sub[r][0];i <= sub[r][1];i ++) vis[a[i]] = 0;
          if (mxc[l][r] < mxc[l][r - 1]) mxc[l][r] = mxc[l][r - 1];
      }
    
    while (q --){
        int l,r;scanf("%d%d",&l,&r);
        printf("%d\n",query(l,r));
    }
    return 0;
}
```

## #3.10 [P4168 [Violet]蒲公英](https://www.luogu.com.cn/problem/P4168)

与上一题本质相同，只不过询问的是种类，好在空间很足，可以多维护信息。

``` cpp
const int N = 100010;
const int M = 320;
const int INF = 0x3fffffff;

int n, len, id[N], sub[M][2], a[N], q, ncnt;
int sum[M][N], st[N], vis[N], mxc[M][M], ls;
int mx[M][M];

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

inline void Disc(int *k) {
    for (int i = 1; i <= n; i ++) st[i] = k[i];
    sort(st + 1, st + n + 1);
    ncnt = unique(st + 1, st + n + 1) - st - 1;
    for (int i = 1; i <= n; i ++)
      k[i] = lower_bound(st + 1, st + ncnt + 1, k[i]) - st;
}

inline void divide() {
    len = sqrt(n); 
    for (int i = 1; i <= n; i ++)
      id[i] = (i - 1) / len + 1;
    for (int i = 1; i <= id[n]; i ++) {
        sub[i][0] = (i - 1) * len + 1;
        sub[i][1] = i * len;
    }
    sub[id[n]][1] = min(sub[id[n]][1], n);
}

inline int query(int x,int y) {
    int l = id[x], r = id[y], res = 0, resp = 0;
    if (l == r){
        for (int i = x; i <= y; i ++) {
            if (res <= ++ vis[a[i]]) {
                if (res < vis[a[i]] || resp > a[i])
                  resp = a[i];
                res = vis[a[i]];
            }
        }
        for (int i = x; i <= y; i ++)
          vis[a[i]] = 0;
        return resp;
    }
    for (int i = x; i <= sub[l][1]; i ++) {
        int upd = (++ vis[a[i]]) + sum[r - 1][a[i]] - sum[l][a[i]];
        if (res <= upd) {
            if (res < upd || resp > a[i]) resp = a[i];
            res = upd;
        }
    }
    for (int i = sub[r][0]; i <= y; i ++) {
        int upd = (++ vis[a[i]]) + sum[r - 1][a[i]] - sum[l][a[i]];
        if (res <= upd) {
            if (res < upd || resp > a[i]) resp = a[i];
            res = upd;
        }
    }
    if (res <= mxc[l + 1][r - 1]) {
        if (res < mxc[l + 1][r - 1] || resp > mx[l + 1][r - 1])
          resp = mx[l + 1][r - 1];
        res = mxc[l + 1][r - 1];
    }
    for (int i = x; i <= sub[l][1]; i ++) vis[a[i]] = 0;
    for (int i = sub[r][0]; i <= y; i ++) vis[a[i]] = 0;
    return resp;
}

int main(){
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i ++)
      scanf("%d", &a[i]);
    Disc(a); divide();
    for (int i = 1; i <= n; i ++) {
        sum[id[i]][a[i]] ++;
        if (sum[id[i]][a[i]] >= mxc[id[i]][id[i]]) {
            if (sum[id[i]][a[i]] > mxc[id[i]][id[i]] || mx[id[i]][id[i]] > a[i])
              mx[id[i]][id[i]] = a[i];
            mxc[id[i]][id[i]] = sum[id[i]][a[i]];
        }
    }
    for (int i = 1; i <= id[n]; i ++)
      for (int j = 1; j <= ncnt; j ++)
        sum[i][j] += sum[i - 1][j];
    for (int len = 2; len <= id[n]; len ++)
      for (int l = 1; l + len <= id[n] + 1; l ++) {
          int r = l + len - 1;
          for (int i = sub[r][0]; i <= sub[r][1]; i ++) {
              int upd = sum[r - 1][a[i]] - sum[l - 1][a[i]] + (++ vis[a[i]]);
              if (mxc[l][r] <= upd) {
                  if (mx[l][r] > a[i] || mxc[l][r] < upd)
                    mx[l][r] = a[i];
                  mxc[l][r] = upd;
               }
          }
          for (int i = sub[r][0]; i <= sub[r][1]; i ++) vis[a[i]] = 0;
          if (mxc[l][r] <= mxc[l][r - 1]) {
              if (mx[l][r] > mx[l][r - 1] || mxc[l][r] < mxc[l][r - 1])
                mx[l][r] = mx[l][r - 1];
              mxc[l][r] = mxc[l][r - 1];
          }
      }
    while (q --) {
        int l, r; scanf("%d%d", &l, &r);
        if (l > r) swap(l, r);
        l = ((l + ls - 1) % n) + 1;
        r = ((r + ls - 1) % n) + 1;
        if (l > r) swap(l, r);
        ls = st[query(l, r)];
        printf("%d\n", ls);
    }
    return 0;
}
```