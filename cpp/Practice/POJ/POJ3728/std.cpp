#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct Node
{
  int next,to;
}edge[300001];
int head[100001],num,ans,dep[100001],val[100001],flag,n,Q;
int fa[100001][19],Min[100001][19],Max[100001][19],Up[100001][19],Down[100001][19];
void add(int u,int v)
{
  num++;
  edge[num].next=head[u];
  head[u]=num;
  edge[num].to=v;
}
void dfs(int x,int pa)
{int i;
  if (dep[x]) return;
  dep[x]=dep[pa]+1;
  for (i=1;i<=18;i++)
    {
      fa[x][i]=fa[fa[x][i-1]][i-1];
      Max[x][i]=max(Max[x][i-1],Max[fa[x][i-1]][i-1]);
      Min[x][i]=min(Min[x][i-1],Min[fa[x][i-1]][i-1]);
      Up[x][i]=max(Up[x][i-1],Up[fa[x][i-1]][i-1]);
      Up[x][i]=max(Up[x][i],Max[fa[x][i-1]][i-1]-Min[x][i-1]);
      Down[x][i]=max(Down[x][i-1],Down[fa[x][i-1]][i-1]);
      Down[x][i]=max(Down[x][i],Max[x][i-1]-Min[fa[x][i-1]][i-1]);
    }
  for (i=head[x];i;i=edge[i].next)
    {
      int v=edge[i].to;
      if (v!=pa)
    {
      Max[v][0]=max(val[v],val[x]);
      Min[v][0]=min(val[v],val[x]);
      Up[v][0]=max(0,val[x]-val[v]);
      Down[v][0]=max(0,val[v]-val[x]);
      fa[v][0]=x;
      dfs(v,x);
    }
    }
}
int LCA(int x,int y)
{
  int i;
  if (dep[x]<dep[y]) swap(x,y);
  for (i=18;i>=0;i--)
    if ((1<<i)<=dep[x]-dep[y])
      {
    x=fa[x][i];
      }
  if (x==y)
    {
      //cout<<"LCA:"<<' '<<x<<endl;
      return x;
    }
  for (i=18;i>=0;i--)
    if (fa[x][i]!=fa[y][i])
      {
    x=fa[x][i];
    y=fa[y][i];
      }
    x=fa[x][0];
    y=fa[y][0];
    //cout<<"LCA:"<<' '<<x<<endl;
    return x;
}
void get_ans(int x,int y,int lca)
{int i;
  int a=0,b=0,minv=2e9,maxv=0;
  int small=2e9,large=0;
  for (i=18;i>=0;i--)
    if ((1<<i)<=dep[x]-dep[lca])
      {
    b=max(b,Up[x][i]);
    b=max(b,Max[x][i]-small);
    small=min(small,Min[x][i]);
    minv=min(minv,Min[x][i]);
    x=fa[x][i];
      }
  for (i=18;i>=0;i--)
    if ((1<<i)<=dep[y]-dep[lca])
      {
    a=max(a,Down[y][i]);
    a=max(a,large-Min[y][i]);
    large=max(large,Max[y][i]);
    maxv=max(maxv,Max[y][i]);
    y=fa[y][i];
      }
  ans=max(a,max(b,maxv-minv));
  return;
}
int main()
{int i,u,v,x,y;
  freopen("in.txt","r",stdin);
  freopen("std.txt","w",stdout);
  cin>>n;
  memset(Min,127,sizeof(Min));
  for (i=1;i<=n;i++)
    scanf("%d",&val[i]);
  for (i=1;i<n;i++)
    {
      scanf("%d%d",&u,&v);
      add(u,v);add(v,u);
    }
  dfs(1,0);
  cin>>Q;
  while (Q--)
    {
      scanf("%d%d",&x,&y);
      if (x==y) printf("0\n");
      else
      {
      int lca=LCA(x,y);
      get_ans(x,y,lca);
      printf("%d\n",ans);
      }
    }
}