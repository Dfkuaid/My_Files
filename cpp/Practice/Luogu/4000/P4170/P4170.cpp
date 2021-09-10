#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 110;
const int INF = 0x3fffffff;

string s;
int f[N][N];

int main(){
    mset(f,0x3f);
    cin >> s;
    for (int i = 0;i < s.length();i ++)
      f[i][i] = 1;
    for (int i = 2;i <= s.length();i ++)
      for (int l = 0;l + i - 1 < s.length();l ++){
          int r = l + i - 1;
          for (int k = l;k < r;k ++)
            f[l][r] = min(f[l][r],f[l][k] + f[k + 1][r]);
          if (s[l] == s[r])
            f[l][r] = min(f[l][r],min(f[l + 1][r],f[l][r - 1]));
      }
    printf("%d",f[0][s.length() - 1]);
    return 0;
}
