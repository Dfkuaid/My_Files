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
string s; 

int main(){
	scanf("%d",&t);
	while (t --){
		cin >> s;
		if (s.length() <= 10){
			cout << s << endl;
			continue;
		}
		cout << s[0] << s.length() - 2 << s[s.length() - 1] << endl;
	} 
    return 0;
}

