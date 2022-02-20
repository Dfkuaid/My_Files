#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define Rep(i,x) for(int i=head[x];i+1;i=nxt[i])
#define rep2(i,a,b) for(int i=(a);i<(b);i++)
#define ff first
#define ss second
using namespace std;
const int N=100005;
const int inf=1e9+7;
typedef long long ll;
//------------------------------------------head---------------------------------------------------//
inline int r(){return rand()*rand()^rand();}
int dlt;
int head[N],nxt[N],to[N],e,dfn[N],top[N],fa[N][20],dep[N],sz[N],son[N];
inline void init(){memset(head,-1,sizeof(head));e=0;}
inline void add_edge(int x,int y){to[e]=y;nxt[e]=head[x];head[x]=e++;}
void dfs(int x,int f)
{
    fa[x][0]=f;sz[x]=1;int ma=0;Rep(i,x)if(to[i]!=f)
    {
        dep[to[i]]=dep[x]+1;
        dfs(to[i],x);sz[x]+=sz[to[i]];
        if(sz[to[i]]>=sz[ma])ma=to[i];
    }son[x]=ma;
}
void dfs2(int x)
{
    if(!top[x])top[x]=x;dfn[x]=++dlt;
    if(son[x]){top[son[x]]=top[x];dfs2(son[x]);}
    Rep(i,x)if(to[i]!=son[x] && to[i]!=fa[x][0])dfs2(to[i]);
}
inline int lca(int x,int y)
{
    if(dep[x]<dep[y])swap(x,y);int dif=dep[x]-dep[y];
    rep(i,0,16)if((1<<i)&dif)x=fa[x][i];
    per(i,16,0)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return x==y ? x : fa[x][0];
}
inline int kth(int x,int k){if(k<=0)return x;rep(i,0,16)if(k&(1<<i))x=fa[x][i];return x;}
char s[15];
int q[N];
vector<pair<int,int> >f1;
namespace fhq
{
    int rot,cnt,tot;
    int son[N][2],sz[N],rev[N],ma[N],mi[N],tag[N],c[N],val[N],rnd[N],pos[N];
    ll sum[N];
    inline int New_node()
    {
        ++cnt;son[cnt][0]=son[cnt][1]=0;sz[cnt]=1;rev[cnt]=0;ma[cnt]=0;mi[cnt]=c[cnt]=0;
        sum[cnt]=0;val[cnt]=cnt;rnd[cnt]=r();return cnt;
    }
    void push_up(int x)
    {
        sz[x]=sz[son[x][0]]+sz[son[x][1]]+1;
        ma[x]=mi[x]=c[x];
        if(son[x][0])ma[x]=max(ma[x],ma[son[x][0]]),mi[x]=min(mi[x],mi[son[x][0]]);
        if(son[x][1])ma[x]=max(ma[x],ma[son[x][1]]),mi[x]=min(mi[x],mi[son[x][1]]);
        sum[x]=sum[son[x][0]]+sum[son[x][1]]+c[x];
    }
    inline void push_down(int x)
    {
        if(tag[x])
        {
            c[son[x][0]]+=tag[x];c[son[x][1]]+=tag[x];
            ma[son[x][0]]+=tag[x];mi[son[x][0]]+=tag[x];ma[son[x][1]]+=tag[x];mi[son[x][1]]+=tag[x];
            sum[son[x][0]]+=1ll*tag[x]*sz[son[x][0]];sum[son[x][1]]+=1ll*tag[x]*sz[son[x][1]];
            tag[son[x][0]]+=tag[x];tag[son[x][1]]+=tag[x];
            tag[x]=0;
        }
        if(rev[x])
        {
            rev[son[x][0]]^=1;rev[son[x][1]]^=1;
            swap(son[son[x][0]][0],son[son[x][0]][1]);
            swap(son[son[x][1]][0],son[son[x][1]][1]);
            rev[x]=0;
        }
    }
    inline pair<int,int> split(int rt,int k)
    {
        if(!rt)return make_pair(0,0);push_down(rt);
        if(sz[son[rt][0]]>=k){pair<int,int>xjt=split(son[rt][0],k);son[rt][0]=xjt.ss;push_up(rt);return make_pair(xjt.ff,rt);}
        else{pair<int,int>xjt=split(son[rt][1],k-sz[son[rt][0]]-1);son[rt][1]=xjt.ff;push_up(rt);return make_pair(rt,xjt.ss);}
    }
    inline int merge(int x,int y)
    {
        if(!x || !y)return x+y;push_down(x);push_down(y);
        if(rnd[x]>rnd[y]){son[x][1]=merge(son[x][1],y);push_up(x);return x;}
        else{son[y][0]=merge(x,son[y][0]);push_up(y);return y;}
    }
    void Ins(){rot=merge(rot,New_node());}
    void Cut(int x,int y)
    {
        int l=lca(x,y);f1.clear();if(x==l)swap(x,y);
        while(x!=fa[l][0])
        {
            if(dep[top[x]]<dep[l]){f1.push_back(make_pair(dfn[l],dfn[x]));break;}
            else f1.push_back(make_pair(dfn[top[x]],dfn[x]));
            x=fa[top[x]][0];
        }
        //ttt=max(ttt,(int)f1.size());
        //for(int i=0;i<f1.size();i++)printf("Case 0: %d %d\n",f1[i].ff,f1[i].ss);puts("");
    }
    void Cut2(int x,int y)
    {
        int l=lca(x,y);f1.clear();
        while(x!=fa[l][0])
        {
            if(dep[top[x]]<dep[l]){f1.push_back(make_pair(dfn[l],dfn[x]));break;}
            else f1.push_back(make_pair(dfn[top[x]],dfn[x]));
            x=fa[top[x]][0];
        }int p=kth(y,dep[y]-dep[l]-1);
        while(y!=l)
        {
            if(dep[top[y]]<=dep[l]){f1.push_back(make_pair(dfn[p],dfn[y]));break;}
            else f1.push_back(make_pair(dfn[top[y]],dfn[y]));
            y=fa[top[y]][0];
        }
    }
    inline void mf(int x,int y,int v)
    {
        pair<int,int>xjt=split(rot,x-1);
        pair<int,int>xjt2=split(xjt.ss,y-x+1);
        c[xjt2.ff]+=v;mi[xjt2.ff]+=v;ma[xjt2.ff]+=v;sum[xjt2.ff]+=1ll*v*sz[xjt2.ff];tag[xjt2.ff]+=v;
        rot=merge(xjt2.ff,xjt2.ss);
        rot=merge(xjt.ff,rot);
    }
    inline int mf2(int x,int y)
    {
        pair<int,int>xjt=split(rot,x-1);
        pair<int,int>xjt2=split(xjt.ss,y-x+1);
        q[++tot]=xjt.ff;rot=xjt2.ss;
        return xjt2.ff;
    }
    inline ll qf(int x,int y,int type)
    {
        pair<int,int>xjt=split(rot,x-1);
        pair<int,int>xjt2=split(xjt.ss,y-x+1);
        ll res=sum[xjt2.ff];if(type==1)res=ma[xjt2.ff];if(type==2)res=mi[xjt2.ff];
        rot=merge(xjt2.ff,xjt2.ss);
        rot=merge(xjt.ff,rot);
        return res;
    }
    void modify(int x,int y,int v)
    {
        Cut(x,y);
        for(int i=0;i<f1.size();i++)mf(f1[i].ff,f1[i].ss,v);
    }
    void modify2(int x,int y)
    {
        Cut(x,y);tot=0;int rt=0,prev=0;
        reverse(f1.begin(),f1.end());
        for(int i=0;i<f1.size();i++)
        {
            rt=merge(rt,mf2(f1[i].ff-prev,f1[i].ss-prev));
            prev=f1[i].ss;
        }q[++tot]=rot;
        rev[rt]^=1;swap(son[rt][0],son[rt][1]);
        rot=q[1];
        for(int i=0;i<f1.size();i++)
        {
            pair<int,int>xjt=split(rt,f1[i].ss-f1[i].ff+1);
            rt=xjt.ss;rot=merge(rot,xjt.ff);
            rot=merge(rot,q[i+2]);
        }
    }
    void query(int x,int y,int type)
    {
        Cut2(x,y);ll ans=0;if(type==2)ans=1e18;
        for(int i=0;i<f1.size();i++)
        {
            if(type==0)ans+=qf(f1[i].ff,f1[i].ss,0);
            else if(type==1) ans=max(ans,qf(f1[i].ff,f1[i].ss,1));
            else ans=min(ans,qf(f1[i].ff,f1[i].ss,2));
        }
        printf("%lld\n",ans);
    }
};
inline void judge()
{
    freopen("3159.in","r",stdin);
    freopen("3159.out","w",stdout);
}
int main()
{
    //judge();
    int n,q,R;scanf("%d%d%d",&n,&q,&R);init();
    rep(i,1,n)fhq::Ins();
    rep(i,1,n-1){int x,y;scanf("%d%d",&x,&y);add_edge(x,y);add_edge(y,x);}
    dfs(R,0);dfs2(R);rep(i,1,16)rep(j,1,n)fa[j][i]=fa[fa[j][i-1]][i-1];
    while(q--)
    {
        scanf("%s",s+1);
        if(s[1]=='I' && s[3]=='c')
        {
            int x,y,c;scanf("%d%d%d",&x,&y,&c);
            fhq::modify(x,y,c);
        }
        else if(s[1]=='S')
        {
            int x,y;scanf("%d%d",&x,&y);
            fhq::query(x,y,0);
        }
        else if(s[1]=='M' && s[2]=='a')
        {
            int x,y;scanf("%d%d",&x,&y);
            fhq::query(x,y,1);
        }
        else if(s[1]=='M' && s[2]=='i')
        {
            int x,y;scanf("%d%d",&x,&y);
            fhq::query(x,y,2);
        }
        else
        {
            int x,y;scanf("%d%d",&x,&y);
            fhq::modify2(x,y);
        }
    }
    //cerr<<ttt<<endl;
    return 0;
}
