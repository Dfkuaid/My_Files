#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<math.h>
#include<vector>
#include<queue>
#define ll long long
#define ld long double

inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
}

const ll inf=1e18;
const ll maxn=1e5+10;
ll n,sum;
ll a[maxn];
char s[maxn];

int main(void)
{
	freopen("task_a.txt", "r", stdin);
    freopen("out2.txt", "w", stdout);
    scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++) a[i]=s[i]-'0';
	std::sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) sum+=a[i];
	if(a[1]!=0||sum%3!=0)
	{
		printf("-1");
	}
	else
	{
		for(int i=n;i>=1;i--) printf("%lld",a[i]);
		// putchar(10);
	}
	return 0;
}

