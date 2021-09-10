#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t, n, cnt[30];
char s[N];

int main() {
    scanf("%d", &t);
    while (t --) {
        int ans = 0; mset(cnt, 0);
        scanf("%d%s", &n, s);
        for (int i = 0; i < n; ++ i)
          ++ cnt[s[i] - 'a' + 1];
        for (int i = 1; i <= 26; ++ i)
          cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; ++ i)
          if (i + 1 <= cnt[s[i] - 'a'] || i + 1 > cnt[s[i] - 'a' + 1]) 
            ++ ans;
        printf("%d\n", ans);
    }
    return 0;
}