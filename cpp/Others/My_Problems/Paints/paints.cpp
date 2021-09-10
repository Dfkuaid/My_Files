#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int n,m,cnt1,l1[N];
map<char,bool> A[N];

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;i ++)
      for (int j = 1;j <= m;j ++){
          char c;cin >> c;
          if (!A[c]) A[c] = 1,cnt1 ++;
          l1[j + i * m - n] = 1;
      }
    for (int i = 1;i <= n;i ++)
      for (int j = 1;j <= m;j ++)
    return 0;
}