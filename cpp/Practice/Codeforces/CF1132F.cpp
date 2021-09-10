#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 510;
const int INF = 0x3fffffff;

string s;
int n,f[N][N];

int main(){
    mset(f,0x3f);
    cin >> n >> s;
    for (int i = 0;i < n;i ++)
      f[i][i] = 1;
    for (int i = 2;i <= n;i ++)
      for (int l = 0;l + i - 1 < n;l ++){
          int r = l + i - 1;
          for (int k = l;k < r;k ++)
            f[l][r] = min(f[l][r],f[l][k] + f[k + 1][r]);
          if (s[l] == s[r]) f[l][r] --;
      }
    printf("%d",f[0][n - 1]);
    return 0;
}
