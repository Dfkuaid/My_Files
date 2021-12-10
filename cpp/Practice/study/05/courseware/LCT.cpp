#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define Rep(i,x) for(int i=head[x];i+1;i=nxt[i])
#define rep2(i,a,b) for(int i=(a);i<(b);i++)
#define ff first
#define ss second
using namespace std;
const int N=300005;
const int inf=1e9+7;
typedef long long ll;
inline void read(int &x){x=0; char ch=getchar();while(ch<'0') ch=getchar();while(ch>='0'){x=x*10+ch-48; ch=getchar();}}
//------------------------------------------head---------------------------------------------------//
namespace LCT
{
    int fa[N],son[N][2],tag[N],tot[N],val[N],cnt,q[N];
    inline int is_root(int x){return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;}
    inline void New_Node(int x)
    {
        ++cnt;fa[cnt]=son[cnt][0]=son[cnt][1]=0;
        val[cnt]=tot[cnt]=x;
    }
    inline void push_up(int x){tot[x]=tot[son[x][0]]^tot[son[x][1]]^val[x];}
    inline void push_down(int x)
    {
        if(!tag[x])return;tag[son[x][0]]^=1;tag[son[x][1]]^=1;
        swap(son[x][0],son[x][1]);tag[x]=0;
    }
    inline void rotate(int x)
    {
        int y=fa[x],z=fa[y],tag1=(son[y][1]==x),tag2=(son[z][1]==y);
        if(!is_root(y)) son[z][tag2]=x; fa[x]=z;fa[y]=x;fa[son[x][!tag1]]=y;
        son[y][tag1]=son[x][!tag1]; son[x][!tag1]=y; push_up(y); push_up(x);
    }
    inline void splay(int x)
    {
        q[q[0]=1]=x;push_up(x);for(int i=x;!is_root(i);i=fa[i])push_up(q[++q[0]]=fa[i]);
        per(i,q[0],1) push_down(q[i]);
        for(int y=fa[x],z=fa[y];!is_root(x);y=fa[x],z=fa[y])
        {if(!is_root(y))(son[y][0]==x)^(son[z][0]==y) ? rotate(x) : rotate(y); rotate(x);}
    }
    inline void access(int x){int y=0;while(x){splay(x);son[x][1]=y;y=x;x=fa[x];}}
    inline void make_root(int x){access(x);splay(x);tag[x]^=1;}
    inline void Link(int x,int y){make_root(x);fa[x]=y;splay(y);}
    inline void Cut(int x,int y){make_root(x);access(y);splay(y);fa[x]=son[y][0]=0;}
    inline void modify(int x,int y){access(x);splay(x);tot[x]^=val[x];val[x]=y;tot[x]^=val[x];}
    inline int query(int x,int y){make_root(x);access(y);splay(y);return val[y]^tot[son[y][0]];}
};
int main()
{
    int n,m;read(n);read(m);rep(i,1,n){int x;read(x);LCT::New_Node(x);}
    rep(i,1,m)
    {
        int type,x,y;read(type);read(x);read(y);
        if(!type)printf("%d\n",LCT::query(x,y));
        else if(type==1)LCT::Link(x,y);
        else if(type==2)LCT::Cut(x,y);
        else LCT::modify(x,y);
    }return 0;
}
