#include<cstdio>
#include<string>
#include<cstring>
#define R_ register
inline int read() {
	int ret=0,f=1,ch=getchar();
	for (; !isdigit(ch); ch=getchar()) if (ch=='-') f=-f;
	for (; isdigit(ch); ch=getchar()) ret=ret*10+ch-48;
	return ret*f;
}
const int maxn=2e5+5;
struct edge {int son,nxt,id,s;} E[maxn],T[maxn];
int top,tar,cnt,sta[maxn],dfn[maxn],low[maxn],bel[maxn];
int N,M,P,tot=1,lnk[maxn],hed[maxn],Ans[maxn],vis[maxn],a[maxn];
inline void add_edge(int y,int x,int id) {
	E[++tot].son=y,E[tot].nxt=lnk[x],lnk[x]=tot,E[tot].id=id,E[tot].s=+1;
	E[++tot].son=x,E[tot].nxt=lnk[y],lnk[y]=tot,E[tot].id=id,E[tot].s=-1;
}
inline void Add_edge(int x,int y,int id,int s) {
	T[++tot].son=y,T[tot].nxt=hed[x],hed[x]=tot,T[tot].id=id,T[tot].s=s;
}
void tarjan(int x,int pre=0) {
	dfn[x]=low[x]=++cnt,sta[++top]=x;
	for (R_ int k=lnk[x],v; v=E[k].son,k; k=E[k].nxt) if (k^pre)
		if (!dfn[v]) {
			tarjan(v,k^1),low[x]=std::min(low[x],low[v]);
			if (low[v]>dfn[x]) {
				for (++tar; sta[top]^v; ) bel[sta[top]]=tar,--top;
				bel[sta[top]]=tar,--top;
			}
		} else low[x]=std::min(low[x],dfn[v]);
}
void dfs(int x,int fa,int id,int s) {
	for (R_ int k=hed[x],v; v=T[k].son,k; k=T[k].nxt) if (!vis[v])
		vis[v]=1,dfs(v,x,T[k].id,T[k].s),a[x]+=a[v];
	if (a[x]) Ans[id]=(a[x]*s<0?1:2);
}
int main() {
    freopen("in.txt", "r", stdin);
    freopen("std.txt", "w", stdout);
	R_ int i,k,x,y;
	for (N=read(),M=read(),i=1; i<=M; ++i) add_edge(read(),read(),i);
	for (i=1; i<=N; ++i) if (!dfn[i]) tarjan(i);
	if (top) for (++tar; top; --top) bel[sta[top]]=tar;
	for (tot=i=1; x=bel[i],i<=N; ++i)
		for (k=lnk[i]; y=bel[E[k].son],k; k=E[k].nxt)
			if (x^y) Add_edge(x,y,E[k].id,E[k].s);
	for (P=read(),i=1; i<=P; ++i) ++a[bel[read()]],--a[bel[read()]];
	for (i=1; i<=tar; ++i) if (!vis[i]) vis[i]=1,dfs(i,0,0,0);
	for (i=1; i<=M; ++i) putchar(!Ans[i]?'B':(Ans[i]==1?'R':'L'));
	return 0;
}
