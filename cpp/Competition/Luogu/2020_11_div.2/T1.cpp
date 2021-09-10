#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int q,a[4],ans;

int main(){
	scanf("%d",&q);
	while (q --){
		scanf("%d%d%d%d",&a[0],&a[1],&a[2],&a[3]);
		sort(a,a + 4);
		if (a[0] + a[3] == a[1] + a[2]){
			if (a[0] == a[1] && a[2] == a[3])
		      ans = 4;
		    else
		      ans = 8;
		}
		else
		  ans = 0;
		printf("%d\n",ans);
	}
	return 0;
} 
