#include<bits/stdc++.h>
#define Ad(tx,tv) ((tx+=tv)>=mod?tx-=mod:0)
#define ci const int&
#define vl vector<long long>
#define Clr(ve) (vl().swap(ve))
using namespace std;
const int N=5e5+10,mod=998244353;
struct FastMod{
	typedef unsigned long long ULL;
	typedef __uint128_t LLL;
	ULL b,m;
	void init(ULL b){this->b=b,m=ULL((LLL(1)<<64)/b);}
	ULL operator()(ULL a){
		ULL q=(ULL)((LLL(m)*a)>>64);
		ULL r=a-q*b;
		return r>=b?r-b:r;
	}
}M;
struct edge{
	int t,nxt;
}e[N<<1];
int n,p,q,u,v,cnt,be[N],md[N];
long long ans,np[N],nq[N],sp,sq,tp[N],tq[N];

/*np[x] 为以 x 为 LCA 的长度为 p 的路径的数量*/
/*nq[x] 为以 x 为 LCA 的长度为 q 的路径的数量*/

char tc;
vl s[N],ps[N],qs[N];
void scan(int&x){
	x=0;
	while(!isdigit(tc=getchar()));
	while(isdigit(tc))x=(x<<3)+(x<<1)+tc-'0',tc=getchar();
}
void add(ci x,ci y){
	e[++cnt]=(edge){y,be[x]},be[x]=cnt;
}
void dfs(ci x,ci f){
	for(int i=be[x];i;i=e[i].nxt)if(e[i].t!=f)dfs(e[i].t,x),md[x]=max(md[x],md[e[i].t]+1);
}
void Merge(vl&x,vl&y){
	int sx=x.size(),sy=y.size();
	for(int i=0;i<sy;++i)x[sx-sy+i]+=y[i];
}
int Getw(vl&x,vl&y,ci tl){
	int sx=x.size(),sy=y.size();
	long long ret=0;
	for(int i=0,ds=sy-1;i<sy;++i,--ds)if(ds<=tl&&tl-ds<sx)ret+=M(1ll*x[sx-1-tl+ds]*y[i]);
	return M(ret);
}
void Calc(ci x,ci f,ci id){
	if(!md[x]){
		s[id].push_back(1);
		return;
	}
	int mi=0;
	for(int i=be[x];i&&!mi;i=e[i].nxt)if(e[i].t!=f&&md[x]==md[e[i].t]+1)mi=e[i].t;
	Calc(mi,x,id),s[id].push_back(1);
	if(s[id].size()>p)np[x]=s[id][s[id].size()-1-p];
	if(s[id].size()>q)nq[x]=s[id][s[id].size()-1-q];
	for(int i=be[x];i;i=e[i].nxt)if(e[i].t!=f&&e[i].t!=mi){
		Clr(s[id+1]),Calc(e[i].t,x,id+1),s[id+1].push_back(0);
		np[x]+=Getw(s[id],s[id+1],p),nq[x]+=Getw(s[id],s[id+1],q);
		Merge(s[id],s[id+1]);
	}
	np[x]=M(np[x]),nq[x]=M(nq[x]),sp+=np[x],sq+=nq[x];
	ans=M(ans+1ll*np[x]*nq[x]);
}
void Solve(ci x,ci f,ci id){
	tp[x]=tp[f],tq[x]=tq[f];
	Ad(tp[x],np[x]),Ad(tq[x],nq[x]);
	if(!md[x]){
		s[id].push_back(1),ps[id].push_back(tp[x]),qs[id].push_back(tq[x]);
		return;
	}
	int mi=0;
	for(int i=be[x];i&&!mi;i=e[i].nxt)if(e[i].t!=f&&md[x]==md[e[i].t]+1)mi=e[i].t;
	Solve(mi,x,id),s[id].push_back(1),ps[id].push_back(tp[x]),qs[id].push_back(tq[x]);
	if(s[id].size()>p)ans=M(ans+1ll*s[id][s[id].size()-1-p]*tq[x]+qs[id][s[id].size()-1-p]);
	if(s[id].size()>q)ans=M(ans+1ll*s[id][s[id].size()-1-q]*tp[x]+ps[id][s[id].size()-1-q]);
	for(int i=be[x];i;i=e[i].nxt)if(e[i].t!=f&&e[i].t!=mi){
		Clr(s[id+1]),Clr(ps[id+1]),Clr(qs[id+1]),Solve(e[i].t,x,id+1);
		s[id+1].push_back(0),ps[id+1].push_back(0),qs[id+1].push_back(0);
		ans+=Getw(s[id],ps[id+1],q)+Getw(ps[id],s[id+1],q);
		ans+=Getw(s[id],qs[id+1],p)+Getw(qs[id],s[id+1],p);
		Merge(s[id],s[id+1]),Merge(ps[id],ps[id+1]),Merge(qs[id],qs[id+1]);
	}
	ans=M(ans+0ll-M(2ll*np[x]*tq[x])+mod-M(2ll*nq[x]*tp[x])+mod);
}
int main(){
	scan(n),scan(p),scan(q),M.init(mod);
	for(int i=1;i<n;++i)scan(u),scan(v),add(u,v),add(v,u);
	dfs(1,0),Calc(1,0,1),Clr(s[1]),Clr(ps[1]),Clr(qs[1]),Solve(1,0,1);
	ans=M(1ll*sp*sq-ans+mod);
	printf("%lld",4*ans%mod);
	return 0;
}
