#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define INF 0xfffffff
#define Maxl 200010
#define LL long long

int k,la;
char a[Maxl],b[Maxl];
int c[Maxl];
int cl;

int sa[Maxl],rank[Maxl],Rs[Maxl],wr[Maxl],y[Maxl];
//sa -> 排名第几的是谁
//rank -> i的排名
//Rs数值小于等于i的有多少个
//y -> 第二关键字排名第几的是谁（类似sa）
int height[Maxl];

void get_sa(int m)
{
    memcpy(rank,c,sizeof(rank));
    for(int i=0;i<=m;i++) Rs[i]=0;
    for(int i=1;i<=cl;i++) Rs[rank[i]]++;
    for(int i=1;i<=m;i++) Rs[i]+=Rs[i-1];
    for(int i=cl;i>=1;i--) sa[Rs[rank[i]]--]=i;
     
    int ln=1,p=0;
    while(p<cl)
    {
        int k=0;
        for(int i=cl-ln+1;i<=cl;i++) y[++k]=i;
        for(int i=1;i<=cl;i++) if(sa[i]>ln) y[++k]=sa[i]-ln;
        for(int i=1;i<=cl;i++) wr[i]=rank[y[i]];
        
        for(int i=0;i<=m;i++) Rs[i]=0;
        for(int i=1;i<=cl;i++) Rs[wr[i]]++;
        for(int i=1;i<=m;i++) Rs[i]+=Rs[i-1];
        for(int i=cl;i>=1;i--) sa[Rs[wr[i]]--]=y[i];
        
        for(int i=1;i<=cl;i++) wr[i]=rank[i];
        for(int i=cl+1;i<=cl+ln;i++) wr[i]=0;
        p=1;rank[sa[1]]=1;
        for(int i=2;i<=cl;i++)
        {
            if(wr[sa[i]]!=wr[sa[i-1]]||wr[sa[i]+ln]!=wr[sa[i-1]+ln]) p++;
            rank[sa[i]]=p;
        }
        m=p,ln*=2;
    }
    sa[0]=rank[0]=0;
}

void get_he()
{
    int kk=0;
    for(int i=1;i<=cl;i++)
    {
        // if(rank[i]==1) break;
        int j=sa[rank[i]-1];
        if(kk) kk--;
        while(c[i+kk]==c[j+kk]&&i+kk<=cl&&j+kk<=cl) kk++;
        height[rank[i]]=kk;
    }
}

LL h[Maxl],cnt[Maxl],s[Maxl];
int tp;
void ffind()
{
    LL ans=0;tp=0;
    s[0]=INF;
    //******
    for(int i=1;i<=cl-1;i++)
    {
        if(sa[i]>=la+1) //B串
          ans+=h[tp];
        if(height[i+1]-k+1<s[tp])//替换
        {
            LL sum=0;
            while(height[i+1]-k+1<=s[tp]&&tp) sum+=cnt[tp--];
            s[++tp]=(height[i+1]-k+1),cnt[tp]=sum,h[tp]=h[tp-1]+cnt[tp]*s[tp];
        }
        else s[++tp]=height[i+1]-k+1,cnt[tp]=0,h[tp]=h[tp-1];
        if(sa[i]<=la) cnt[tp]++,h[tp]+=s[tp];//A串
        if(height[i+1]<k)
        {
            tp=0;s[0]=INF;
        }
    }tp=0;s[tp]=INF;
    for(int i=1;i<=cl-1;i++)
    {
        if(sa[i]<=la) //A串
          ans+=h[tp];
        if(height[i+1]-k+1<s[tp])//替换
        {
            LL sum=0;
            while(height[i+1]-k+1<=s[tp]&&tp) sum+=cnt[tp--];
            s[++tp]=(height[i+1]-k+1),cnt[tp]=sum,h[tp]=h[tp-1]+cnt[tp]*s[tp];
        }
        else s[++tp]=height[i+1]-k+1,cnt[tp]=0,h[tp]=h[tp-1];
        if(sa[i]>=la+1) cnt[tp]++,h[tp]+=s[tp];//B串
        if(height[i+1]<k)
        {
            tp=0;s[tp]=INF;
        }
     }
    printf("%lld\n",ans);
}

void init()
{
    scanf("%s%s",a,b);
    int l=strlen(a);cl=0;
    la=l;
    for(int i=0;i<l;i++)
    {
        if(a[i]>='a'&&a[i]<='z') c[++cl]=a[i]-'a'+1;
        else c[++cl]=a[i]-'A'+27;
    }
    c[++cl]=55;
    l=strlen(b);
    for(int i=0;i<l;i++)
    {
        if(b[i]>='a'&&b[i]<='z') c[++cl]=b[i]-'a'+1;
        else c[++cl]=b[i]-'A'+27;
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("std.txt", "w", stdout);
    while(1)
    {
        scanf("%d",&k);
        if(k==0) break;
        init();
        get_sa(55);
        get_he();
        ffind();
    }
    return 0;
}
