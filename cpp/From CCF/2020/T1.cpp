#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#define mset(l,x) memset(l,x,sizeof(l))
#define mp(a,b) make_pair(a,b)
using namespace std;

int n; 

int main(){
	scanf("%d",&n);
	if (n % 2 == 1){
		cout << "-1";
		return 0;
	}
	while (n > 0){
		int i = 0;
		while ((1 << i) <= n)
		  i ++;
		i -= 1;
		printf("%d ",1 << i);
		n -= (1 << i);
	}
	return 0;
}

