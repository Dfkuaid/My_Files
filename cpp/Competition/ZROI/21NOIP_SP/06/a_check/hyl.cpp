#include<bits/stdc++.h>
#define dd double
#define ld long double
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define N 6000100
#define M number
using namespace std;

const int INF=0x3f3f3f3f;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

template<typename T> inline T Max(T a,T b){return a<b?b:a;}

struct Ques{
    int op,val,posi;
    inline Ques(){}
    inline Ques(int op,int val,int posi) : op(op),val(val),posi(posi) {}
    inline bool operator < (const Ques &b)const{return posi<b.posi;}
}ques[N];

int t,n,d,k,tail;
//S存的是当前的前k大值，而 T 里面放的是所有没有加入 S 的可行值。
//注意，S里面的值从小到大，T里面的值，从大到小。
multiset<int> S,T;
ll cnt,sum,ans;

inline void Init(){
    read(d);read(n);read(k);
    for(int i=1;i<=n;i++){
        int val,l,r;read(val);read(l);read(r);
        ques[++tail]=Ques(1,val,l);
        ques[++tail]=Ques(-1,val,r+1);
    }
    sort(ques+1,ques+tail+1);
}

inline void Insert(int val){
    if(cnt!=k){
        S.insert(val);cnt++;
        sum+=val;
    }
    else{
        int Minn=(*S.begin());
        if(Minn>=val) T.insert(-val);
        else{
            T.insert(-Minn);
            S.erase(S.find(Minn));
            S.insert(val);
            sum-=Minn;sum+=val;
        }
    }
}

inline void Delete(int val){
    if(T.find(-val)!=T.end()){
        T.erase(T.find(-val));
    }
    else{
        S.erase(S.find(val));sum-=val;
        if(T.empty()){
            cnt--;return;
        }
        int Maxx=-(*T.begin());
        T.erase(T.find(-Maxx));
        S.insert(Maxx);sum+=Maxx;
    }
}

inline void Solve(){
    for(int i=1;i<=tail;i++){
        if(ques[i].posi!=ques[i-1].posi) ans=Max(ans,sum);
        if(ques[i].op==1) Insert(ques[i].val);
        else Delete(ques[i].val);
    }
    ans=Max(ans,sum);
    assert(S.empty()&&T.empty());
}

inline void Clear(){
    tail=0;cnt=0;sum=0;ans=0;
}

signed main(){
    freopen("in.txt","r",stdin);
    freopen("hyl.txt","w",stdout);
    read(t);
    for(int i=1;i<=t;i++){
        Init();Solve();
        printf("Case #%lld: %lld\n",i,ans);
        Clear();
    }
}
