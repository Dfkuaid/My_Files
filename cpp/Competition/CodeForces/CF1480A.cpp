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

int t;
char c[101];

int main(){
	scanf("%d",&t);
	while (t --){
		char tmp[101];
		scanf("%s",c);
		for (int i = 0;i < strlen(c);i ++)
		  if ((i + 1) % 2)
		    tmp[i] = (c[i] == 'a') ? 'b' : 'a';
		  else
		    tmp[i] = (c[i] == 'z') ? 'y' : 'z';
		for (int i = 0;i < strlen(c);i ++)
		  cout << tmp[i];
		cout << endl;
	}
    return 0;
}

