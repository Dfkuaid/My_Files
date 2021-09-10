#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define INF 0x3fffffff
#define N 100010
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l));
#define mp(a,b) make_pair(a,b)
using namespace std;

struct Monster{
	ll attack;
	ll life;
	ll need;
	ll tot;
};
Monster m[N];

bool cmp(const Monster a,const Monster b){
	return a.need < b.need;
}

ll t,n,ha,hb;

int main(){
	scanf("%lld",&t);
	while (t --){
		scanf("%lld%lld%lld",&ha,&hb,&n);
		for (int i = 1;i <= n;i ++)
		  scanf("%lld",&m[i].attack);
		for (int i = 1;i <= n;i ++){
			scanf("%lld",&m[i].life);
			int num = m[i].life / ha + ((m[i].life % ha == 0) ? 0 : 1);
			m[i].need = num * m[i].attack;
			m[i].tot = num;
		}
		sort(m + 1,m + n + 1,cmp);
		int cnt = 0,i = 1;
		bool f = true;
		while (hb > 0 && i <= n){
			cnt ++;
			ll need_cnt = hb / m[i].attack + ((hb % m[i].attack == 0) ? 0 : 1);
			hb -= m[i].need;
			if (hb <= 0 && cnt < n){
				f = false;
				break;
			}
			if (need_cnt < m[i].tot){
				f = false;
				break;
			}
			i ++;
		}
		if (!f){
			cout << "NO\n";
		}
		else
		  cout << "YES\n";
	}
    return 0;
}

