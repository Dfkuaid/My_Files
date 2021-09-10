#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const char bs[9] = {' ', 'c', 'h', 'o', 'k', 'u', 'd', 'a', 'i'};

char s[N]; 
int cnt[9], ans, len;

int main() {
    scanf("%s", s); len = strlen(s);
    for (int i = 0; i < len; ++ i)
      for (int j = 1; j <= 8; ++ j)
        if (bs[j] == s[i]) {
            if (j == 1) ++ cnt[j];
            else (cnt[j] += cnt[j - 1]) %= MOD;
        }
    printf("%d", cnt[8]);
    return 0;
}