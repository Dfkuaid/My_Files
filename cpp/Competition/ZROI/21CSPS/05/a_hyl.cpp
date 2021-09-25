#include<bits/stdc++.h>
#define dd double
#define ld long double
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define N 100010
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

char s[N];
int len,all=0,a[N];

inline bool cmp(int a,int b){return a>b;}

int main(){
    freopen("task_a.txt", "r", stdin);
    freopen("out2.txt", "w", stdout);
    scanf("%s",s+1);len=strlen(s+1);
    for(int i=1;i<=len;i++){
        all+=s[i]-'0';a[i]=s[i]-'0';
    }
    sort(a+1,a+len+1,cmp);
    if(all%3!=0||a[len]!=0){printf("-1"); return 0;}
    for(int i=1;i<=len;i++) printf("%d",a[i]);
    return 0;
}
