#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#define mset(l,x) memset(l,x,sizeof(l))
#define mp(a,b) make_pair(a,b)
using namespace std;

int n,w,src[100010];
int l[100010],tot;

int main(){
//	freopen("live.in","r",stdin);
//	freopen("live.out","w",stdout);
	scanf("%d%d",&n,&w);
	for (int i = 1;i <= n;i ++)
	  scanf("%d",&src[i]);
	l[++ tot] = src[1];
	printf("%d ",src[1]);
	int i = 2;
	while (i <= n){
		int num = max(1,i * w / 100);
		int last = lower_bound(l + 1,l + tot + 1,src[i]) - l;
//		cout << last << endl;
		for (int j = tot + 1;j > last;j --)
		  l[j] = l[j - 1];
		l[last] = src[i];
		tot ++;
//		for (int j = 1;j <= n;j ++)
//		  cout << l[j] << " ";
//		cout << endl;
		printf("%d ",l[tot - num + 1]); 
		i ++;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

