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

int main(){
	int x;
	scanf("%d",&x);
	if (x % 2 || x == 2)
	  printf("NO");
	else
	  printf("YES"); 
    return 0;
}

